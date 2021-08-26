import json
import glob                                                                                    
import tqdm                                                                                     
import numpy as np                                                                             
import argparse                                                                                
                                                                                                
# Parse args                                                                                   
parser = argparse.ArgumentParser()                                                              
parser.add_argument("metadata_size", help="Input metadata size in bytes", type=int)
parser.add_argument("specdata_size", help="Input specdata size in bytes", type=int)
parser.add_argument("spec_stat", help="spectra stat file with spectrum length and size")
parser.add_argument("channel_par", help="Channel level parallelism", nargs='?', default=4)
parser.add_argument("topk_size", help="Size of k most intensive peaks", nargs='?', default=50)


parser.add_argument("chip_rate", help="IO rate of flash chip in MB/s", nargs='?', default=128)
parser.add_argument("channel_rate", help="IO rate of channel in MB/s", nargs='?', default=800)
parser.add_argument("ssd_rate", help="IO rate of SSD in MB/s", nargs='?', default=3200)

parser.add_argument("ssd_channel", help="Number of SSD channels", nargs='?', default=16)
parser.add_argument("ssd_chip", help="Number of chips per channel", nargs='?', default=4)

args = parser.parse_args()                                                                   
                                                                                                
metadata_size = args.metadata_size
specdata_size = args.specdata_size
spec_stat_file = args.spec_stat
channel_par = int(args.channel_par)
top_k = args.topk_size


ssd_config = {}
ssd_config['bw_chip'] = args.chip_rate
ssd_config['bw_channel'] = args.channel_rate
ssd_config['bw_ssd'] = args.ssd_rate
ssd_config['channel_num'] = args.ssd_channel
ssd_config['chip_num'] = args.ssd_chip
ssd_config['avg_read_power'] = 9.6
ssd_config['avg_write_power'] = 11.0


# Accelerator parms
acc_area = {"chip":137213.04, "channel":543621.36, "ssd":316987.76}

energy_ssd_read = ssd_config['avg_read_power'] / ssd_config['bw_ssd'] * 1000 # nJ/B

energy_fifo = 2.52159e-4 # nJ/B
energy_sram = 7.31351e-4 # nJ/B

energy_filter = 2.5975e-4 # nJ/pt
energy_topk = {'chip': 5.177e-2, "channel": 2.48131e-2, "ssd": 2.48131e-2 }
energy_norm = {'chip': 1.15538e-2, "channel": 1.49088e-2, "ssd": 1.32313e-2 }
                                                                           
FP_bit = 24


# Init. parms
spec_stat_array = np.loadtxt(spec_stat_file)


# Chip-level data mapping
energy_chip = {"acc_move_metadata":metadata_size*(energy_fifo+energy_sram), "acc_move_spectra":specdata_size*energy_fifo, "acc_compute":0.0, "ssd_move_data":(metadata_size*1.1+specdata_size)*energy_ssd_read}

chip_data_mapping = np.zeros((ssd_config['channel_num'], ssd_config['chip_num']))
chip_processed_spectra = np.zeros((ssd_config['channel_num'], ssd_config['chip_num']))

for i in tqdm.tqdm(range(spec_stat_array.size//2), position=0, leave=True):                                                            
    cid = (i//ssd_config['chip_num']) % ssd_config['channel_num']
    wid = i % ssd_config['chip_num']

    # Estimate data size for each chip
    chip_data_mapping[cid, wid] += spec_stat_array[i*2+1]

for i in tqdm.tqdm(range(spec_stat_array.size//2), position=0, leave=True):                                                            
    cid = (i//ssd_config['chip_num']) % ssd_config['channel_num']
    wid = i % ssd_config['chip_num']

    chip_processed_spectra[cid, wid] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2

    # Estimate energy
    energy_chip["acc_compute"] += spec_stat_array[i*2]*(energy_filter + energy_topk['chip'] + energy_norm['chip'])
    energy_chip["acc_move_spectra"] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2  * energy_sram
    energy_chip["ssd_move_data"] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2 * 0.1 * energy_ssd_read


chip_level_transfer_time = np.amax(chip_data_mapping/ssd_config['bw_chip']/1e6)
chip_level_extra_time = (chip_processed_spectra.sum()+metadata_size)/ssd_config['bw_ssd']/1e6


print('====== Chip level =====')
print('energy_chip', energy_chip)
print('chip_level_transfer_time', chip_level_transfer_time)
print('chip_level_extra_time', chip_level_extra_time)
print('Chip area:', acc_area['chip']*ssd_config['chip_num']*ssd_config['channel_num'])



# Channel-level data mapping
energy_channel = {"acc_move_metadata":metadata_size*(energy_fifo+energy_sram), "acc_move_spectra":specdata_size*energy_fifo, "acc_compute":0.0, "ssd_move_data":(metadata_size*1.1+specdata_size)*energy_ssd_read}

channel_data_mapping = np.zeros((ssd_config['channel_num'], ssd_config['chip_num']))
channel_processed_spectra = np.zeros((ssd_config['channel_num'], ssd_config['chip_num']))

for i in tqdm.tqdm(range(spec_stat_array.size//2), position=0, leave=True):                                                            
    wid = (i//ssd_config['channel_num']) % ssd_config['chip_num']
    cid = i % ssd_config['channel_num']

    # Estimate data size for each chip
    channel_data_mapping[cid, wid] += spec_stat_array[i*2+1]

for i in tqdm.tqdm(range(spec_stat_array.size//2), position=0, leave=True):                                                            
    wid = (i//ssd_config['channel_num']) % ssd_config['chip_num']
    cid = i % ssd_config['channel_num']
    channel_processed_spectra[cid, wid] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2

    # Estimate energy
    energy_channel["acc_compute"] += spec_stat_array[i*2]*(energy_filter + energy_topk['channel'] + energy_norm['channel'])
    energy_channel["acc_move_spectra"] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2 * energy_sram
    energy_channel["ssd_move_data"] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2 * 0.1 * energy_ssd_read


channel_level_transfer_time = np.amax(channel_data_mapping.reshape(ssd_config['channel_num']//channel_par, -1).sum(axis=1) / min(ssd_config['bw_channel']*channel_par, 4800) /1e6)
channel_level_extra_time = (channel_processed_spectra.sum() + metadata_size) /ssd_config['bw_ssd']/1e6

print('====== Channel level =====')
print('Channel parallelism:', channel_par)
print('energy', energy_channel)
print('channel_level_transfer_time', channel_level_transfer_time)
print('channel_level_extra_time', channel_level_extra_time)
print('Channel area:', acc_area['channel']*ssd_config['channel_num']/channel_par)


# SSD-level data mapping
energy_ssd =  {"acc_move_metadata":metadata_size*(energy_fifo+energy_sram), "acc_move_spectra":specdata_size*energy_fifo, "acc_compute":0.0, "ssd_move_data":(metadata_size*1.1+specdata_size)*energy_ssd_read}

ssd_data_mapping = np.zeros((ssd_config['channel_num'], ssd_config['chip_num']))
ssd_processed_spectra = np.zeros((ssd_config['channel_num'], ssd_config['chip_num']))

for i in tqdm.tqdm(range(spec_stat_array.size//2), position=0, leave=True):                                                            
    wid = (i//ssd_config['channel_num']) % ssd_config['chip_num']
    cid = i % ssd_config['channel_num']

    # Estimate data size for each chip
    ssd_data_mapping[cid, wid] += spec_stat_array[i*2+1]

for i in tqdm.tqdm(range(spec_stat_array.size//2), position=0, leave=True):                                                            
    wid = (i//ssd_config['channel_num']) % ssd_config['chip_num']
    cid = i % ssd_config['channel_num']
    ssd_processed_spectra[cid, wid] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2

    # Estimate energy
    energy_ssd["acc_compute"] += spec_stat_array[i*2]*(energy_filter + energy_topk['ssd'] + energy_norm['ssd'])
    energy_ssd["acc_move_spectra"] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2 * energy_sram
    energy_ssd["ssd_move_data"] += min(top_k, spec_stat_array[i*2]) * FP_bit / 8 * 2 * 0.1 * energy_ssd_read


ssd_level_transfer_time = ssd_data_mapping.sum() / ssd_config['bw_ssd']/1e6
ssd_level_extra_time = (ssd_processed_spectra.sum() + metadata_size) /ssd_config['bw_ssd']/1e6

print('====== SSD level =====')
print('energy', energy_ssd)
print('ssd_level_transfer_time', ssd_level_transfer_time)
print('ssd_level_extra_time', ssd_level_extra_time)
print('SSD area:', acc_area['ssd'])



#print('raw_data_access', raw_data_access)
#print('opt_data_access', opt_data_access)
#print('PXD_stat', PXD_stat)
#
#
#with open(output_file+'.json', 'w') as f_json:
#    f_json.write(json.dumps(raw_data_access))
#    f_json.write(json.dumps(opt_data_access))
#
#np.savetxt(output_file+'.npy', spec_verbose)

print("Done!")
