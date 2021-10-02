LOG_NAME=$1
PW_MEASURE_PATH=/var/lib/kubelet/weihong/cpu-energy-meter

$PW_MEASURE_PATH/cpu-energy-meter -r >> $LOG_NAME 
