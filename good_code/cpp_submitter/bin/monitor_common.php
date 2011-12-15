<?php



function SendWarningEMail($message, $subject = 'MID build monitor failed!!!')
{
    $maillist     = 'weizili@360.cn';

    $hostname = php_uname('n');

    $ret = mail($maillist, $subject, $message);
    if ($ret == FALSE) {
        Trace("send to $maillist mail failed!!!");
    } else {
        Trace("send to $maillist mail successfully.");
    }
}


function SendWarning($content, $subject = 'MID build monitor failed!!!')
{
    $url = "http://alarms.ops.qihoo.net:8360/intfs/alarm_intf?group_name=mid_stand_build&subject=$subject&content=$content";

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, urlencode($url));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $resp = curl_exec($ch);
    curl_close($ch);

    if ($resp == 'ok')
    {
        Trace('Send Warning OK!');
    }
    else
    {
        Trace('Send Warning ERROR:'.$resp);
    }
}

//Get the time stamp from log file 
//scan.all.log.2011-12-06-12
function GetTimeStampFromLogFile($file_name)
{
    $cmd = "tail $file_name";
    exec($cmd, $logs_arr);
    $arr_len = count($logs_arr);
var_dump($logs_arr);
    for ($i = $arr_len - 1; $i >= 0; --$i)
    {
        if (strncmp($logs_arr[$i], '201', 3) == 0)
        {
            // log "2011-12-06 15:54:21 "
            Trace("find a log :". $logs_arr[$i]);
            $str = str_replace('-', '', $logs_arr[$i]);
            $str = str_replace(' ', '', $str);
            $str = str_replace('\t', '', $str);
            $str = str_replace(':', '', $str);
            $str = substr($str, 0, 14);
            Trace("log time stamp: $str");
            return MktimeFromString($str);
        }
    }

    SendWarningEMail(__FUNCTION__." ERROR. The monitor script working abnormal, please check it!", __FILE__ . " work abnormal");

    Trace(__FUNCTION__.' Error!!');
    return time();
}

//Get the time stamp from data Inc_*.xml file 
///home/s/apps/statdata/midtag/input/Inc_10000011105_a69c186640c7983a89fa51a0cc3f4858_midd06.safe.dxt.qihoo.net_20111206061603.xml
function GetTimeStampFromIncFile($file_name)
{
    return filemtime($file_name);

/*
    $str = strrchr($file_name, '_');
    //Trace($str);
    $str = substr($str, 1, strlen($str) - strlen('.xml') - 1);
    //Trace($str);
    return MktimeFromString($str);
*/
}

//20111206061603
function MktimeFromString($timestr)
{
    $hour = substr($timestr, 8, 2);
    $minute = substr($timestr, 10, 2);
    $second = substr($timestr, 12, 2);
    $month = substr($timestr, 4, 2);
    $day = substr($timestr, 6, 2);
    $year = substr($timestr, 0, 4);

    //Trace($timestr);
    //Trace(sprintf("%s%s%s%s%s%s", $year, $month, $day, $hour, $minute, $second));
    return mktime($hour, $minute, $second, $month, $day, $year);

}

function FindLatestFile($pattern)
{
    $file_arr = glob($pattern, GLOB_NOSORT);
    sort($file_arr);
    if (count($file_arr) > 0)
    {
        return array_pop($file_arr);
    }

    return False;
}

function Trace($log)
{
    echo date('Y-m-d H:i:s').' - '.$log."\n";
}

?>

