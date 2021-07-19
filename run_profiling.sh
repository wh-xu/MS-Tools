ARGC=$#
if [ $ARGC -ne 2 ]; 
then
    echo "Not enough input args!"
else
    MNT_PATH=$1
    PXD=$2

    STAMP=$(date +%Y-%m-%d_%H-%M)
    HOME_PATH=$(pwd)

    # Copy ms dataset to local
    rsync -rP ${MNT_PATH}/${PXD} $HOME_PATH 

    # Generate file list
    sudo sh generate_file_list.sh ${PXD}

    out_file=profiling_${PXD}_${STAMP}.log

    # 1. msCRUSH
    cd ${HOME_PATH}/msCRUSH/profiling; lscpu | tee $out_file; free -h | tee -a $out_file ; ../bin/mscrush_on_general_charge -f ${HOME_PATH}/${PXD}/*.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 | tee -a $out_file 

    # 2. MS-Cluster
    cd ${HOME_PATH}/MS-Cluster/profiling; lscpu | tee $out_file; free -h | tee -a $out_file ; ../MSCluster_bin --model LTQ_TRYP --list ${HOME_PATH}/${PXD}/list.dat --output-name test_results --min-mz 200 --max-mz 2000 --memory-gb 8 | tee -a $out_file

fi
