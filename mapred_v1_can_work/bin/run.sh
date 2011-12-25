#!/bin/bash

#~/software/hadoop/bin/hadoop jar ~/software/hadoop/contrib/streaming/hadoop-0.20.1.12-streaming.jar -mapper "php map.php" -reducer "php reduce.php" -input /hadoop_game/data/  -output /hadoop_game/output/weizili  -file map.php -file reduce.php

_datenow=`date +%Y%m%d`
_timenow=`date +%H%M%S`
_time=${_datenow}_${_timenow}

exec 2>> ./run.log
set -x
_phase1_output=/hadoop_game/weizili/phase1_output_${_time}
_phase2_output=/hadoop_game/weizili/phase2_output_${_time}

~/software/hadoop/bin/hadoop jar ~/software/hadoop/contrib/streaming/hadoop-0.20.1_v2-streaming.jar -mapper "./phase1_map" -reducer "./phase1_reduce" -input /hadoop_game/data/  -output ${_phase1_output} -file phase1_map -file phase1_reduce

echo $?

~/software/hadoop/bin/hadoop jar ~/software/hadoop/contrib/streaming/hadoop-0.20.1_v2-streaming.jar -mapper "./phase2_map" -reducer "./phase2_reduce" -input ${_phase1_output}  -output ${_phase2_output} -file phase2_map -file phase2_reduce

