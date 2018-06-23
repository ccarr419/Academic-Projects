<?php
session_start();
$loggedin = $_SESSION['loggedin'];

/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/orderdetails.php
     Course:      	CSC 242 - Fall 2013
*/


//Create page with same style sheet and links as rest of website
echo 	"<html xmlns = 'http://www.w3.org/1999/xhtml'>
		<head>
			<title>      Chris' Book Store      </title>
   
			<!-- My stylesheet for the project -->
			<link rel = 'stylesheet' type = 'text/css' href = 'projectstyle.css'/>
		</head>
		<body>
			<!-- Links -->
			<div class = 'header'><h1>Chris' Book Store</h1></div>
			<div class = 'special'>
			<h3><p class = 'one'>
			<a class = 'link' href = 'myproject.php'>Home</a> &nbsp; | &nbsp;";
			if($loggedin == true)
				echo "<a class = 'link' href = 'loggedout.php'>Log Out</a> &nbsp; | &nbsp;";
			else
				echo "<a class = 'link' href = 'login.html'>Log In</a> &nbsp; | &nbsp;";
echo			"<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
			<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
			<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
			<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
			<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
			<a class = 'link' href = 'viewcart.php'>View Cart</a>
			</p></h3>";

//Connect to the database
$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
$username = 'ccarr419';
$password = 'S7treyuB';

$db = new PDO($dsn, $username, $password);

//Get info from the OrderDetails table
$query = "SELECT * FROM OrderDetails";
$orders = $db->query($query);

$id = array();
foreach($orders as $order)
{	$id[] = $_POST[$order['OrderID']]; }

echo "<h3><div class = 'header'>View another order? <a class = 'link2' href = 'orders.php'>Click here</a></div></h3>";

//Create a table containing order details of specific order
echo "<table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
		<thead><tr>
		<th>Order ID</th>
		<th>Product ID</th>
		<th>Quantity</th>
		<th>Line Total</th>
		</tr></thead>";

$query = "SELECT * FROM OrderDetails";
$orders = $db->query($query);
foreach($orders as $order)
{	foreach($id as $i)
	{	if($i == $order['OrderID'])
		{
		echo "<tr><td><div class = 'special'>";
		echo $order['OrderID'];
		echo "</div></td><td><div class = 'special'>";
		echo $order['ProductID'];
		echo "</div></td><td><div class = 'special'>";
		echo $order['Quantity'];
		echo "</div></td><td><div class = 'special'>$";
		echo round($order['LineTotal'], 2);
		echo "</div></td></tr>";
		}
	}
}
	
echo "</table></div></body>
</html>";

?>