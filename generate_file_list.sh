DATASET_PATH=$(pwd);

#ls -lha $1 | grep mgf | awk -v P="$DATASET_PATH/$1" 'BEGIN{print P $9}' | tee $1/list.dat
ls -lha $1 | grep mgf | awk -v P="$DATASET_PATH/$1" '{print P "/"$9}' | tee $1/list.dat
