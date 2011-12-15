<?php

require_once("monitor_common.php");

#-----------------------
#check step1:
$expected_count = 16;
if (FALSE == CheckProcessCount(16, $accutual_count))
{
    SendWarning("The midbuilder process count=$accutual_count, but we expected $expected_count!!");
    die;
}
Trace("Monitor OK!");

####################################################################################
### Functions
####################################################################################
function CheckProcessCount($expected_count, &$accutual_count)
{
    $cmd = "ps aux | grep midbuilder | grep -v grep | grep -v php | wc -l";

    $ret = exec($cmd, $output_arr);

    #var_dump($output_arr);

    $accutual_count = (int)trim($output_arr[0]);

    if ($accutual_count != $expected_count)
    {
        return FALSE;
    }

    return TRUE;
}

?>



