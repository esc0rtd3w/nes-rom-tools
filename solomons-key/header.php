<?
echo "<i>Solomon's Web Edit version 1.0 Created by King Killa</i><br><br>";
if($_GET[lev1]) {
$level = $_GET[lev1];
}

if($_POST[lev1]) {
$level = $_POST[lev1];
}

if($level != "1") {
$pre = ("$level" - "1");
$prev = "<a href=\"./?lev={$pre}\">Previous Level</a>";
}
else {
$prev = "Previous Level";
}

if($level != "53") {
$nex = ("$level" + "1");
$next = "<a href=\"./?lev={$nex}\">Next Level</a>";
}
else {
$next = "Next Level";
}

echo "{$prev} | <a href=\"./?lev={$level}\">Refresh</a> | {$next} <br>";
echo "<form method=GET action=index.php name=leveljump>Level jump: <select name=lev1>";
$drop = "1";
while("$drop" < "54") {
echo "<option value=\"{$drop}\">{$drop}</option>";
$drop++;
}
echo "</select><input type=submit value=jump!></form><br>";
?>