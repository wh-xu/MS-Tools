#PXD=PXD001197
#PXD=PXD021328
PXD=PXD001511


RUN=1

OUT_FILE=profiling_${PXD}_${RUN}.log

lscpu > $OUT_FILE
free -h >> $OUTFILE

../MSCluster_bin --model LTQ_TRYP --list /home/user/bio/ms-dataset/${PXD}/list.dat --output-name test_results --min-mz 200 --max-mz 2000 --memory-gb 8 | tee -a $OUT_FILE
