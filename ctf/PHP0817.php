<?php 
    $t = "a";
if($t == 0){
    echo "yes1";
}
if($t === 0){
    echo "yes2";
}

switch($t){
    case 0:
        echo "0";
        break;
    case 1:
        echo "1";
        break;
    case 2:
        echo "2";
        break;
    default:
        echo "default";
        break;
    }
?>
