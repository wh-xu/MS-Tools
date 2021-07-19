#PXD_PATH=PXD001511
PXD_PATH=PXD001197
RUN=1
out_file=profiling_${PXD_PATH}_${RUN}.log

lscpu > $out_file
free -h >> -a $out_file 
../bin/mscrush_on_general_charge -f ~/bio/ms-dataset/${PXD_PATH}/*.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 -c ../clusters/clusters | tee -a $out_file 
