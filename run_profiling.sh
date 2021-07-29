ARGC=$#
if [ $ARGC -ne 2 ]; 
then
    echo "Not enough input args!"
else
    MNT_PATH=$1
    PXD=$2

        HOME_PATH=$(pwd)

    # Copy ms dataset to local
    rsync -hrP --ignore-existing ${MNT_PATH}/${PXD} $HOME_PATH 

    # Generate file list
    sudo sh generate_file_list.sh ${PXD}

    
    # 1. msCRUSH
    STAMP=$(date +%Y-%m-%d_%H-%M)
    out_file=profiling_${PXD}_${STAMP}.log

    cd ${HOME_PATH}; sh record_cpu_load.sh ${PXD}_mscrush_load_${STAMP}.log &

    cd ${HOME_PATH}/msCRUSH/profiling; lscpu | tee $out_file; free -h | tee -a $out_file ; ../bin/mscrush_on_general_charge -f ${HOME_PATH}/${PXD}/*.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 | tee -a $out_file 
    cp $out_file ~/bio/workspace/whxu/msCRUSH_${out_file}

    kill %1
    echo "Wait 1min for next one"
    sleep 60

    # 2. MS-Cluster
    STAMP=$(date +%Y-%m-%d_%H-%M)
    out_file=profiling_${PXD}_${STAMP}.log

    cd ${HOME_PATH}; sh record_cpu_load.sh ${PXD}_mscluster_load_${STAMP}.log &

    cd ${HOME_PATH}/MS-Cluster/profiling; lscpu | tee $out_file; free -h | tee -a $out_file ; ../MSCluster_bin --model LTQ_TRYP --list ${HOME_PATH}/${PXD}/list.dat --output-name test_results --min-mz 200 --max-mz 2000 --memory-gb 8 | tee -a $out_file
    cp $out_file ~/bio/workspace/whxu/MSCluster_${out_file}

    kill %1
    echo "Wait 1min for next one"
    sleep 60

    # 3. maracluster
    STAMP=$(date +%Y-%m-%d_%H-%M)
    out_file=profiling_${PXD}_${STAMP}.log

    cd ${HOME_PATH}; sh record_cpu_load.sh ${PXD}_maracluster_load_${STAMP}.log &

    cd ${HOME_PATH}/maracluster; lscpu | tee $out_file; free -h | tee -a $out_file ; rm -rf maracluster_output/; maracluster batch -b ${HOME_PATH}/${PXD}/list.dat -v 3 2>&1 | tee -a $out_file
    cp $out_file ~/bio/workspace/whxu/maracluster_${out_file}

    kill %1
    echo "Wait 1min for next one"
    sleep 60

    
    # 4. spectra cluster
    STAMP=$(date +%Y-%m-%d_%H-%M)
    out_file=profiling_${PXD}_${STAMP}.log

    cd ${HOME_PATH}; sh record_cpu_load.sh ${PXD}_spectra-cluster_load_${STAMP}.log &

    cd ${HOME_PATH}/spectra-cluster; lscpu | tee $out_file; free -h | tee -a $out_file ; java -jar spectra-cluster-cli-1.1.2.jar -fast_mode -filter mz_200 -output_path my_clustering_result.clustering -fragment_tolerance 0.05 -precursor_tolerance 20 -precursor_tolerance_unit "ppm" -rounds 3 ${HOME_PATH}/${PXD}/*.mgf
    cp $out_file ~/bio/workspace/whxu/spectra_cluster_${out_file}
    
    kill %1
fi
