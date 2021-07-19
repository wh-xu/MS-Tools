MNT_PATH=$1
RUN=$2

PXD=PXD001197

# Copy ms dataset to local
rsync -rP ${MNT_PATH} ~/${PXD}

out_file=profiling_${PXD}_${RUN}.log

# 1. msCRUSH
cd ~/MS-Tools/msCRUSH/profiling; lscpu | tee $out_file; free -h | tee -a $out_file ; ../bin/mscrush_on_general_charge -f ~/${PXD}/*.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 | tee -a $out_file 

# 2. MS-Cluster
cd ~/MS-Tools/MS-Cluster/profiling; lscpu | tee $out_file; free -h | tee -a $out_file ; ../MSCluster_bin --model LTQ_TRYP --list ~/${PXD}/list.dat --output-name test_results --min-mz 200 --max-mz 2000 --memory-gb 8 | tee -a $out_file

