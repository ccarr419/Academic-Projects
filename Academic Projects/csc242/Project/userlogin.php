<?php
session_start();
/*
     Name:         	Christian Carreas
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/userlogin.php
     Course:      	CSC 242 - Fall 2013
*/

//Variables taken from login.html or loginfail.html
$user = $_POST['user'];
$pass = $_POST['pass'];

//Correct username and password
if(login($user, $pass))
{	//Take user to home page
	$_SESSION['loggedin'] = true;
	header("Location: myproject.php");
}

//Wrong username or password
else if(!login($user, $pass))
{	//Take user to loginfailed.html
	header("Location: loginfailed.html"); 
}

//Checks if the username and password the user entered
//matches a username and password in the database
function login($user, $pass)
{	//Create PDO object
	$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	//Open database
	$db = new PDO($dsn, $username, $password);

	$query = "SELECT * FROM Customers";
	
	$accounts = $db->query($query);
	
	//Check database for username and password
	foreach($accounts as $account)
	{	if($user == $account['Email'] && $pass == $account['Passwd'])
		{	$_SESSION['name'] = $account['FirstName'];
			$_SESSION['custID'] = $account['CustomerID'];
			return true;
		}
	}
	return false;
}

?>