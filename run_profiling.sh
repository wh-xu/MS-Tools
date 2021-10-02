ARGC=$#
if [ $ARGC -ne 1 ]; 
then
    echo "Not enough input args!"
else
    PXD=$1
    HOME_PATH=$(pwd)
    TASK_SET="taskset -c 0-7"
    PW_MEASURE_PATH=/var/lib/kubelet/weihong/cpu-energy-meter

    

    # Copy ms dataset to local
    #rsync -hrP --ignore-existing ${MNT_PATH}/${PXD} $HOME_PATH 

    # Generate file list
    sudo sh generate_file_list.sh ${PXD}

    
    # 1. msCRUSH
    #STAMP=$(date +%Y-%m-%d_%H-%M)
    #out_file=profiling_${PXD}_${STAMP}.log

    #cd ${HOME_PATH}/msCRUSH/profiling; 
    #lscpu | tee $out_file; free -h | tee -a $out_file ; 

    #$PW_MEASURE_PATH/cpu-energy-meter -r > energy_${PXD}_mscrush_${STAMP}.log &
    #$TASK_SET ../bin/mscrush_on_general_charge -f ${HOME_PATH}/${PXD}/*.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 | tee -a $out_file 

    #kill -2 $!
    #echo "Wait 1min for next one"
    #sleep 5

    # 2. MS-Cluster
#    STAMP=$(date +%Y-%m-%d_%H-%M)
#    out_file=profiling_${PXD}_${STAMP}.log
#
#    cd ${HOME_PATH}/MS-Cluster/profiling; 
#    lscpu | tee $out_file; free -h | tee -a $out_file ; 
#
#    $PW_MEASURE_PATH/cpu-energy-meter -r > energy_${PXD}_mscluster_${STAMP}.log &
#    $TASK_SET ../MSCluster_bin --model LTQ_TRYP --list ${HOME_PATH}/${PXD}/list.dat --output-name test_results --min-mz 200 --max-mz 2000 --memory-gb 16 | tee -a $out_file
#
#    kill -2 $!
#    echo "Wait 1min for next one"
#    sleep 5

    # 3. maracluster
    STAMP=$(date +%Y-%m-%d_%H-%M)
    out_file=profiling_${PXD}_${STAMP}.log

    cd ${HOME_PATH}/maracluster; 
    lscpu | tee $out_file; free -h | tee -a $out_file ; rm -rf maracluster_output/;
    
    $PW_MEASURE_PATH/cpu-energy-meter -r > energy_${PXD}_maracluster_${STAMP}.log &
    $TASK_SET maracluster batch -b ${HOME_PATH}/${PXD}/list.dat -t -15.0 -c -45.0,-40.0,-35.0,-30.0,-25.0,-20.0 -v 3 2>&1 | tee -a $out_file

    kill -2 $!
    echo "Wait 1min for next one"
    sleep 5

    
    # 4. spectra cluster
#    STAMP=$(date +%Y-%m-%d_%H-%M)
#    out_file=profiling_${PXD}_${STAMP}.log
#
#    cd ${HOME_PATH}/spectra-cluster/profiling; 
#    lscpu | tee $out_file; free -h | tee -a $out_file ; rm -rf *.clustering
#
#    $PW_MEASURE_PATH/cpu-energy-meter -r > energy_${PXD}_spectra-cluster_${STAMP}.log &
#    $TASK_SET java -jar spectra-cluster-cli-1.1.2.jar -fast_mode -filter mz_200 -output_path my_clustering_result.clustering -fragment_tolerance 0.05 -precursor_tolerance 20 -precursor_tolerance_unit "ppm" -rounds 3 ${HOME_PATH}/${PXD}/*.mgf
#    
#    kill -2 $!
fi
