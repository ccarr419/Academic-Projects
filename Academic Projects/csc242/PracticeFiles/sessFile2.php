<?php

$_SESSION['num'] = $_SESSION['num'] - 1;
echo "sessTest, num = " . $_SESSION['num'] . "<br/>";
echo "<a href = 'sessFile1.php'>File-1</a> &nbsp; <a href = 'sessFile2.php'>File-2</a> &nbsp;";
echo "<a href = 'sessTest.php'>Home</a>";


?>