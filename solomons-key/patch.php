<?
$fpr = fopen("key1.nes", 'rb');
fseek($fpr, "24636",SEEK_SET);
$hex = bin2hex(fread($fpr, "2544"));
fclose($fpr);
$hex2 = "504154434800603C09F0".$hex."454F46";
$hexbin = pack('H*', $hex2);
$fpp = fopen("patch.ips", 'wb');
fwrite($fpp, "$hexbin");
fclose($fpp);
echo "Patch made successfully, And Key1.nes edited successfully.";
?>