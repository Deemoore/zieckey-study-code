<?php

function test(&$a)
{
    $a = $a+100;
}
$b=1;
echo $b;//output 1
test($b);  //
echo "\n";
echo $b;//output 101
echo "\n";

?>
