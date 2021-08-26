import json
import glob                                                                                    
import tqdm                                                                                     
import numpy as np                                                                             
import argparse                                                                                
                                                                                                
# Parse args                                                                                   
parser = argparse.ArgumentParser()                                                              
parser.add_argument("PXD", help="PXD directory")                                                
parser.add_argument("output", help="output filename")

args = parser.parse_args()                                                                   
                                                                                                
PXD_dir = args.PXD
output_file = args.output

                                                                           
FP_bit = 24

# Generate MGF file list                                                                        
mgf_file_list = glob.glob(PXD_dir+'*.mgf')                                                      


raw_data_access = {'total': 0.0, 'metadata': 0.0, 'spectradata': 0.0}
opt_data_access = {'total': 0.0, 'metadata': 0.0, 'spectradata': 0.0}
PXD_stat = {'total_spectra_num':0}
spec_verbose = np.array([]) # [ len, size ]

# Open MGF file                                                                                 
for f_i in tqdm.tqdm(mgf_file_list):                                                            
    mgf_file = open(f_i, mode='r')                                                         
    f_i_buffer = mgf_file.read().splitlines()
    mgf_file.close() 
    
    
    for str_i in tqdm.tqdm(f_i_buffer, position=0, leave=True):
        if(str_i == 'BEGIN IONS'):
            spec_i_size = len(str_i)
            spec_i_len = 0
            PXD_stat['total_spectra_num'] += 1 # Count spectra num
        # Calculate data access/compression
        elif (str_i[0].isnumeric()):
            spec_i_size += len(str_i)
            spec_i_len += 1
            raw_data_access['spectradata'] += len(str_i)
            opt_data_access['spectradata'] += 2*FP_bit/8.0
        elif (str_i == 'END IONS'):
            spec_verbose = np.append(spec_verbose, [spec_i_len, spec_i_size])
        else:
            spec_i_size += len(str_i)
            raw_data_access['metadata'] += len(str_i)
            opt_data_access['metadata'] += len(str_i)
            
            
    raw_data_access['total'] = raw_data_access['spectradata'] + raw_data_access['metadata']
    opt_data_access['total'] = opt_data_access['spectradata'] + opt_data_access['metadata']
    

print('raw_data_access', raw_data_access)
print('opt_data_access', opt_data_access)
print('PXD_stat', PXD_stat)


with open(output_file+'.json', 'w') as f_json:
    f_json.write(json.dumps(raw_data_access))
    f_json.write(json.dumps(opt_data_access))

np.savetxt(output_file+'.npy', spec_verbose)

print("Done!")
