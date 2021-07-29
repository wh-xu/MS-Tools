LOG_NAME=$1

while true
do
    uptime | tee -a $LOG_NAME
    sleep 60
done
