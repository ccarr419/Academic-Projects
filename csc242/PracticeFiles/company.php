<?php
	
function db_connect() 
{	$DB_NAME = "emp"; 
	$DB_HOST = "acad.kutztown.edu"; 
	$DB_USER = "ccarr419"; 
	$DB_PASS = "S7treyuB"; 
 
	global $connection; 
 
	$connection = mysql_connect($DB_HOST, $DB_USER, $DB_PASS) 
	or die("Cannot connect to $DB_HOST as $DB_USER:" . mysql_error()); 
 
	mysql_select_db($DB_NAME) or die ("Cannot open $DB_NAME:" . mysql_error()); 
 
	return $connection; 
} 

function db_close() 
{	global $connection; 
	mysql_close($connection); 
}
	
echo
	"<form action = 'company.php' method = 'post'>
	
		<label>Employee's ID: </label>
		<input type = 'text' name = 'id' id = 'id'/><br/><br/>
		<label>Emplyee's Name: </label>
		<input type = 'text' name = 'name' id = 'name'/><br/><br/>
		<label>Employee's Salary: </label>
		<input type = 'text' name = 'salary' id = 'salary'/><br/><br/>
		<label>Employee's Dept#: </label>
		<input type = 'text' name = 'dept' id = 'dept'/><br/><br/>
		
		<input type = 'submit' value = 'Submit'/>
		<input type = 'reset' value = 'Cancel'/>
		
	</form>";
	
$id = $_POST['id'];
$name = $_POST['name'];
$salary = $_POST['salary'];
$dept = $_POST['dept'];
	
$employee_info = array();
$employee_info['id'] = $id;
$employee_info['name'] = $name;
$employee_info['salary'] = $salary;
$employee_info['dept'] = $dept;

db_connect();
$query = "INSERT INTO products
		(id, name, sal, dno)
	VALUES
		('$id', '$name', '$salary', '$dept')";
$insert_count = $connection->exec($query);
	
	/*foreach($employee_info as $info)
	{	echo "<p>$info</p>"; }*/
	
	/*echo "Employee's ID: " . $id . "<br/>";
	echo "Employee's Name: " . $name . "<br/>";
	echo "Employee's Salary: " . $salary . "<br/>";
	echo "Employee's Dept#: " . $dept . "<br/>";*/
?>