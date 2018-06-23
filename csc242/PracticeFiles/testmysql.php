<?php

$empID = 92;
$name = 'Smitty';
$sal = 52000;
$dept = 13;

echo "<p>Employee ID: $empID </p>";
echo "<p>Employee Name: $name </p>";
echo "<p>Employee Salary: $sal </p>";
echo "<p>Employee Dept#: $dept </p>";

/*$DB_NAME = "ccarr419_bookstore"; 
$DB_HOST = "localhost"; 
$DB_USER = "ccarr419"; 
$DB_PASS = "S7treyuB"; 
 
global $connection; 
 
$connection = mysql_connect($DB_HOST, $DB_USER, $DB_PASS) 
or die("Cannot connect to $DB_HOST as $DB_USER: " . mysql_error()); 
 
mysql_select_db($DB_NAME) or die ("Cannot open $DB_NAME:" . mysql_error()); */

$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
$username = 'ccarr419';
$password = 'S7treyuB';

$db = new PDO($dsn, $username, $password);


$query = "INSERT INTO emp
		(id, name, sal, dno)
	  VALUES
		('$empID', '$name', '$sal', '$dept')";
		
$insert_count = $db->exec($query);



?>