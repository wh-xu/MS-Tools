../cpu-energy-meter/cpu-energy-meter -r >> energy_test.log &
P=$!

TASK_SET="taskset -c 0-7"
out_file=profiling_test.log

$TASK_SET msCRUSH/bin/mscrush_on_general_charge -f $1/b1923_293T_proteinID_03A_QE3_122212.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 | tee -a $out_file

echo $P
kill -2 $!

echo "wait 5s"
sleep 5


../cpu-energy-meter/cpu-energy-meter -r >> energy_test.log &
P=$!

$TASK_SET msCRUSH/bin/mscrush_on_general_charge -f $1/b1923_293T_proteinID_03A_QE3_122212.mgf -t 40 -n 15 -i 100 -s 0.65 -l 200 -r 2000 | tee -a $out_file

echo $P
kill -2 $!


