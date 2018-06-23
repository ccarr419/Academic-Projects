<?php
session_start();
$loggedin = $_SESSION['loggedin'];
$purchases = $_SESSION['order'];

$custID = $_SESSION['custID'];
$sNh = $_POST['sNh'];
$tax = $_POST['tax'];
$qty = $_POST['qty'];
$id = $_POST['id'];
$total = $_POST['total'];

/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/purchasemade.php
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

//Thank user for order
echo	"<h1 class = 'header'>Thank you! Your order has been confirmed!</h1></div>
	</body>
	</html>";

$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	$db = new PDO($dsn, $username, $password);

	$query = "SELECT * FROM Orders";
	$orders = $db->query($query);

//Find OrderID for OrderDetails table
$higest = 0;
foreach($orders as $order)
{	if($order['OrderID'] > $higest)
	{	$highest = $order['OrderID'] + 1; }
}

$ordernum = $highest;

//Add info into Orders and OrderDetails table
insertOrder($custID, $sNh, $tax, $qty);
insertDetails($ordernum, $id, $qty, $total);
	
function insertOrder($custID, $sNh, $tax, $qty)
{	$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	$db = new PDO($dsn, $username, $password);

	$query = 	"INSERT INTO Orders
				(CustomerID, ShippingCost, Tax, Total, OrderDate)
			VALUES
				('$custID', '$sNh', '$tax', '$qty', NOW())";

	$insert_count = $db->exec($query);
}

function insertDetails($ordernum, $id, $qty, $total)
{	$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	$db = new PDO($dsn, $username, $password);

	$query = 	"INSERT INTO OrderDetails
				(OrderID, ProductID, Quantity, LineTotal)
			VALUES
				('$ordernum', '$id', '$qty', '$total')";

	$insert_count = $db->exec($query);
}
unset($_SESSION['order']);
?>