<?php
session_start();
$_SESSION['num'] = 10;
echo "sessTest, num = " . $_SESSION['num'] . "<br/>";
print "<a href = 'sessFile1.php'>File-1</a> &nbsp; &nbsp;";
print "<a href = 'sessFile2.php'>File-2</a>";
?>