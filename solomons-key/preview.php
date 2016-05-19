<?
include("header.php");
?>
<font face=fixedsys>
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
<?
include("convertjs.php");
$i = 0;
$num = ("48" * "2");
?>
<script language="JavaScript"><!--
function copydata() {
    document.hack.lev1.value = document.preview.lev1.value;
    document.hack.hex.value = document.preview.hex.value;

}
//--></script>
<?
echo "<form method=POST name=\"preview\"><table><tr><td><input type=hidden name=lev1 value=\"{$_POST[lev1]}\"><textarea rows=24 cols=5 name=hex>";
$test = str_replace(" ", "", $_POST[hex]);
$test = str_replace("\n", "", $test);
$test = str_replace("\r", "", $test);

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
echo "</textarea><br><input type=submit value=Preview></form><br><form name=hack method=POST action=index.php><input type=hidden name=lev1><input type=hidden name=hex><input type=submit value=Hack! onClick=\"copydata()\"></form></td><td valign=top><font face=fixedsys>KEY:<br>

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
<input type=hidden name=lev1 value="<?=$_POST[lev1]?>">
<input type=submit value="Convert to hex!">
<br>
<input type=reset value="reset">
</form>
