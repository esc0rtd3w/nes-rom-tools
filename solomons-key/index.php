<?

if(!$_GET[lev1]) {
$_GET[lev1] = "1";
}

include("header.php");
?>
<HEAD>
<SCRIPT language="JavaScript">
<!--
num = 1;
function movepic(img_name, set) {

if(num == "1") {
document[img_name].src='solid.gif';
document.imghex[set].value = "1";
num = 2;
}
else if(num == "2") {
document[img_name].src='block.gif';
document.imghex[set].value = "2";
num = 3;
}
else if(num == "3") {
document[img_name].src='bg.gif';
document.imghex[set].value = "0";
num = 1;
}


}
-->
</SCRIPT>
</HEAD>

<font face=fixedsys>
<?
if($_GET["new"]) {
$overwrite = fopen("key1.nes", "w");
fwrite($overwrite, "");
fclose($overwrite);
}

include("convertjs.php");
$lev[1] = "603C";
$lev[2] = "606C";
$lev[3] = "609C";
$lev[4] = "60CC";
$lev[5] = "60FC";
$lev[6] = "612C";
$lev[7] = "615C";
$lev[8] = "618C";
$lev[9] = "61BC";
$lev[10] = "61EC";
$lev[11] = "621C";
$lev[12] = "624C";
$lev[13] = "627C";
$lev[14] = "62AC";
$lev[15] = "62DC";
$lev[16] = "630C";
$lev[17] = "633C";
$lev[18] = "636C";
$lev[19] = "639C";
$lev[20] = "63CC";
$lev[21] = "63FC";
$lev[22] = "642C";
$lev[23] = "645C";
$lev[24] = "648C";
$lev[25] = "64BC";
$lev[26] = "64EC";
$lev[27] = "651C";
$lev[28] = "654C";
$lev[29] = "657C";
$lev[30] = "65AC";
$lev[31] = "65DC";
$lev[32] = "660C";
$lev[33] = "663C";
$lev[34] = "666C";
$lev[35] = "669C";
$lev[36] = "66CC";
$lev[37] = "66FC";
$lev[38] = "672C";
$lev[39] = "675C";
$lev[40] = "678C";
$lev[41] = "67BC";
$lev[42] = "67EC";
$lev[43] = "681C";
$lev[44] = "684C";
$lev[45] = "687C";
$lev[46] = "68AC";
$lev[47] = "68DC";
$lev[48] = "690C";
$lev[49] = "693C";
$lev[50] = "696C";
$lev[51] = "699C";
$lev[52] = "69CC";
$lev[53] = "69FC";

if($_POST[hex]) {
if(filesize("key1.nes") == filesize("key.nes")) {
$fp = fopen("key1.nes", "rb");
}
else {
$fp = fopen("key.nes", "rb");
}
$beg = fread($fp, hexdec($lev["$_POST[lev1]"]));
$lev2 = ($_POST[lev1] + "1");
$end1 = (filesize("key.nes") - hexdec($lev[$lev2]));
fseek($fp, hexdec($lev[$lev2]),SEEK_SET);
$end = fread($fp, $end1);
fclose($fp);
$fp1 = fopen("key1.nes", "wb");
$new = str_replace(" ", "", $_POST[hex]);
$new = str_replace("\n", "", $new);
$new = str_replace("\r", "", $new);
if(strlen($new) < "96") {
$new = str_pad($new, "0", "96");
}

if(strlen($new) > "96") {
$new = substr($new, "0", "96");
}

$new = pack('H*', $new);
if(fwrite($fp1, "$beg"."$new"."$end")) {
include("patch.php");
}
else {
echo "err.. somethiing went wrong with writing to the file..";
}
exit;
}

if(filesize("key1.nes") == filesize("key.nes")) {
$fp = fopen("key1.nes", "rb");
}
else {
$fp = fopen("key.nes", "rb");
}
fseek($fp, hexdec($lev["$_GET[lev1]"]),SEEK_SET);
$test = strtoupper(bin2hex(fread($fp, "48")));
$num = ("48" * "2");
$i = 0;
?>
<script language="JavaScript"><!--
function copydata() {
    document.hack.lev1.value = document.preview.lev1.value;
    document.hack.hex.value = document.preview.hex.value;

}
//--></script>
<?
echo "<form method=POST name=\"preview\" action=preview.php><table><tr><td><input type=hidden name=lev1 value=\"{$_GET[lev1]}\"><textarea rows=24 cols=5 name=hex>";
while($i < $num) {

	if($i < 48) {
		$type = "block";
		convert($type);
	}
	else {
		$type = "solid";
		convert($type);
	}
	if(strstr(($i / "2"), ".")) {
		echo "$test[$i]";
		$tab[$i."n1"] = ${$test[$i]."n1"};
		$tab[$i."n2"] = ${$test[$i]."n2"};
		$tab[$i."n3"] = ${$test[$i]."n3"};
		$tab[$i."n4"] = ${$test[$i]."n4"};

		$l++;
		if($l == "2") {
			echo "\n";
			$l = 0;
		}
		else {
			echo " ";
		}
		$i++;
	}
	else {
		echo $test[$i];
		$tab[$i."n1"] = ${$test[$i]."n1"};
		$tab[$i."n2"] = ${$test[$i]."n2"};
		$tab[$i."n3"] = ${$test[$i]."n3"};
		$tab[$i."n4"] = ${$test[$i]."n4"};
		$i++;
	}
}
echo "</textarea><br><input type=submit value=Preview></form><br><form name=hack method=POST><input type=hidden name=lev1><input type=hidden name=hex><input type=submit value=Hack! onClick=\"copydata()\"></form></td><td valign=top><font face=fixedsys>KEY:<br>

0 = 0000<br>
1 = 000X<br>
2 = 00X0<br>
3 = 00XX<br>
4 = 0X00<br>
5 = 0X0X<br>
6 = 0XX0<br>
7 = 0XXX<br>
8 = X000<br>
9 = X00X<br>
A = X0X0<br>
B = X0XX<br>
C = XX00<br>
D = XX0X<br>
E = XXX0<br>
F = XXXX</td></tr></table>";
?>
</font>
<table><tr><td>
<table cellpadding=0 cellspacing=0>
<tr>
<?
$z = "0";
while($z < 48) {
	if($tab[("$z" + "48")."n1"]) {
		$tab[("$z" + "48")."n1"] = str_replace("###", "{$z}d', '{$z}d", $tab[("$z" + "48")."n1"]);
		$tab[("$z" + "48")."n1"] = str_replace("%%%", "{$z}d", $tab[("$z" + "48")."n1"]);
		$value = "1";
		echo "<td>".$tab[("$z" + "48")."n1"]."</td>";
	}
	else {
		$tab["$z"."n1"] = str_replace("###", "{$z}d', '{$z}d", $tab["$z"."n1"]);
		$tab["$z"."n1"] = str_replace("%%%", "{$z}d", $tab["$z"."n1"]);
		if(strstr($tab["$z"."n1"], "bg.gif")) { $value = "0"; } else { $value = "2"; }
		echo "<td>".$tab["$z"."n1"]."</td>";
	}
	$form .= "<input type=text name='{$z}d' size=1 value={$value}>";

	if($tab[("$z" + "48")."n2"]) {
		$tab[("$z" + "48")."n2"] = str_replace("###", "{$z}a', '{$z}a", $tab[("$z" + "48")."n2"]);
		$tab[("$z" + "48")."n2"] = str_replace("%%%", "{$z}a", $tab[("$z" + "48")."n2"]);
		$value = "1";
		echo "<td>".$tab[("$z" + "48")."n2"]."</td>";
	}
	else {
		$tab["$z"."n2"] = str_replace("###", "{$z}a', '{$z}a", $tab["$z"."n2"]);
		$tab["$z"."n2"] = str_replace("%%%", "{$z}a", $tab["$z"."n2"]);
		if(strstr($tab["$z"."n2"], "bg.gif")) { $value = "0"; } else { $value = "2"; }
		echo "<td>".$tab["$z"."n2"]."</td>";
	}
	$form .= "<input type=text name={$z}a size=1 value={$value}>";

	if($tab[("$z" + "48")."n3"]) {
		$tab[("$z" + "48")."n3"] = str_replace("###", "{$z}b', '{$z}b", $tab[("$z" + "48")."n3"]);
		$tab[("$z" + "48")."n3"] = str_replace("%%%", "{$z}b", $tab[("$z" + "48")."n3"]);
		$value = "1";
		echo "<td>".$tab[("$z" + "48")."n3"]."</td>";
	}
	else {
		$tab["$z"."n3"] = str_replace("###", "{$z}b', '{$z}b", $tab["$z"."n3"]);
		$tab["$z"."n3"] = str_replace("%%%", "{$z}b", $tab["$z"."n3"]);
		if(strstr($tab["$z"."n3"], "bg.gif")) { $value = "0"; } else { $value = "2"; }
		echo "<td>".$tab["$z"."n3"]."</td>";
	}
	$form .= "<input type=text name={$z}b size=1 value={$value}>";

	if($tab[("$z" + "48")."n4"]) {
		$tab[("$z" + "48")."n4"] = str_replace("###", "{$z}c', '{$z}c", $tab[("$z" + "48")."n4"]);
		$tab[("$z" + "48")."n4"] = str_replace("%%%", "{$z}c", $tab[("$z" + "48")."n4"]);
		$value = "1";
		echo "<td>".$tab[("$z" + "48")."n4"]."</td>";
	}
	else {
		$tab["$z"."n4"] = str_replace("###", "{$z}c', '{$z}c", $tab["$z"."n4"]);
		$tab["$z"."n4"] = str_replace("%%%", "{$z}c", $tab["$z"."n4"]);
		if(strstr($tab["$z"."n4"], "bg.gif")) { $value = "0"; } else { $value = "2"; }
		echo "<td>".$tab["$z"."n4"]."</td>";
	}
	$form .= "<input type=text name={$z}c size=1 value={$value}>";

	$z++;
	if(!strstr(("$z" / "4"), ".")) {
	echo "</tr><tr>";
	$form .= "</td><tr></tr><td>";
	}
}
?>
</td>
</tr></table>
</td><td>
<table><tr><td>
<form name=imghex method=POST action=imghex.php>
<?=$form?>
</td></tr></table>
</td></tr></table>
<input type=hidden name=lev1 value="<?=$_GET[lev1]?>">
<input type=submit value="Convert to hex!">
<br>
<input type=reset value="reset">
</form>