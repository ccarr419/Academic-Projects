<?php
session_start();
$loggedin = $_SESSION['loggedin'];
$id = $_SESSION['custID'];

/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/orders.php
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
			</p></h3><br/>";
		
if($loggedin == false)
	echo "<h3><p class = 'one'>Please log in to view your orders! <a href = 'login.html' class = 'link'>Log in?</a></p></h3>";

else
{	//Connect to the database
	$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	$db = new PDO($dsn, $username, $password);

	//Get info from the Orders table
	$query = "SELECT * FROM Orders";
	$orders = $db->query($query);

	if(!checkEmpty($orders, $id))
	{	echo "<h1 class = 'header'><div style = 'color: red'>You have not made any orders yet!</div></h1>"; }

	else
	{
		$query = "SELECT * FROM Orders";
		$orders = $db->query($query);
		//Create a table containing orders of the user
		echo "<table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
		<thead><tr>
		<th>Order ID</th>
		<th>Customer ID</th>
		<th>Shipping Cost</th>
		<th>Tax</th>
		<th>Total</th>
		<th>Order Date</th>
		<th colspan = '1'></th>
		</tr></thead>";
		$i = 1;
		
		foreach($orders as $order)
		{	if($order['CustomerID'] == $id)
			{	echo "<tr><td><div class = 'special'>";
				echo $order['OrderID'];
				echo "</div></td><td><div class = 'special'>";
				echo $order['CustomerID'];
				echo "</div></td><td><div class = 'special'>$";
				echo round($order['ShippingCost'], 2);
				echo "</div></td><td><div class = 'special'>$";
				echo round($order['Tax'], 2);
				echo "</div></td><td><div class = 'special'>";
				echo $order['Total'];
				echo "</div></td><td><div class = 'special'>";
				echo $order['OrderDate'];
				echo "</div></td><td><div class = 'special'>
				<form name = 'order$i' action = 'orderdetails.php' method = 'post'>
				<input type = 'hidden' id = '" . $order['OrderID'] . "' name = '" . $order['OrderID'] . "' value = '" . $order['OrderID'] . "'/>
				<input type = 'submit' value = 'Order Details'/></form></div></td></tr>";
				$i++;
			}
		}
	}
}
echo "</table></div></body>
</html>";

function checkEmpty($orders, $id)
{	foreach($orders as $order)
	{	if($order['CustomerID'] == $id)
			return true;
	}
	return false;
}
?>