<?php
session_start();
/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/useraccount.php
     Course:      	CSC 242 - Fall 2013
*/

//Variable taken from creataccount.html
$fname = $_POST['fname'];
$lname = $_POST['lname'];
$email = $_POST['email'];
$pass = $_POST['pass1'];
$add1 = $_POST['add1'];
$add2 = $_POST['add2'];
$city = $_POST['city'];
$state = $_POST['state'];
$zip = $_POST['zip'];
$phone = $_POST['phone'];

//Connect to database
$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
$username = 'ccarr419';
$password = 'S7treyuB';

$db = new PDO($dsn, $username, $password);

//Insert new customer into database
$query = "INSERT INTO Customers
		(Email, Passwd, FirstName, LastName, Address1, Address2,
		City, State, ZipCode, PhoneNumber)
	VALUES
		('$email', '$pass', '$fname', '$lname', '$add1', '$add2',
		'$city', '$state', '$zip', '$phone')";
		
$insert_count = $db->exec($query);

//Change page to home page
;
header("Location: login.html");

?>