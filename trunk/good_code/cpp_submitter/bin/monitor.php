<?php

require_once("monitor_common.php");


#-----------------------

$MAX_INTERVAL = 15 * 60;//seconds

#check step1:
$latest_file = FindLatestFile('../logs/scan.all.log.*');
if ($latest_file != False)
{
    $latest_log_time = GetTimeStampFromLogFile($latest_file);
    if (time() - $latest_log_time > $MAX_INTERVAL)
    {
        SendWarning('Build stop, 15 minutes no log produced!!', 'MID build stop!');
        die;
    }
    else
    {
        //Trace(time().' '.$latest_log_time);
    }
}

#check step2:
$inc_file = '/home/s/apps/statdata/midtag/input/Inc_*';
$latest_file = FindLatestFile($inc_file);
$latest_inc_time = GetTimeStampFromIncFile($latest_file);
if (time() - $latest_inc_time > $MAX_INTERVAL)
{
    SendWarning("Build stop, 15 minutes no $inc_file produced!!", 'MID no command input!'); 
    die;
}


Trace('Monitor OK!');

?>



