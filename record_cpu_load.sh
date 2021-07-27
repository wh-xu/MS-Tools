LOG_NAME=cpu_load_history.log

uptime | tee $LOG_NAME

while true
do
    uptime | tee -a $LOG_NAME
    sleep 60
done
