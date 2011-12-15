<?php

#-----------------------
#check step1:
$expected_count = 16;
if (FALSE == CheckProcessCount(16, $accutual_count))
{
    SendWarningEMail("The midbuilder process count=$accutual_count, but we expected $expected_count!!");
    die;
}
Trace("Monitor OK!");

####################################################################################
### Functions
####################################################################################
function CheckProcessCount($expected_count, &$accutual_count)
{
    $cmd = "ps aux | grep midbuilder | grep -v grep | wc -l";

    $ret = exec($cmd, $output_arr);

    #var_dump($output_arr);

    $accutual_count = (int)trim($output_arr[0]);

    if ($accutual_count != $expected_count)
    {
        return FALSE;
    }

    return TRUE;
}



function SendWarningEMail($message, $subject = 'MID build monitor failed!!!')
{
#$maillist     = 'weizili@360.cn xiangyong@360.cn yuanruifeng@360.cn hemanbin@360.cn'; 
    $maillist     = 'weizili@360.cn';

    $hostname = php_uname('n');

    $ret = mail($maillist, $subject, $message);
    if ($ret == FALSE) {
        echo "send to $maillist mail failed!!!";
    } else {
        echo "send to $maillist mail successfully.";
    }
}

function Trace($log)
{
    echo date('Y-m-d H:i:s').' - '.$log."\n";
}

?>



