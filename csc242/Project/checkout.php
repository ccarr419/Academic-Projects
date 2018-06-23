<?php

session_start();
$loggedin = $_SESSION['loggedin'];
$purchases = $_SESSION['order'];

/*
	Name:         	Christian Carreras
	Project: 	Designing Web Page
	Purpose:	Book store website
	URL:         	http://unixweb.kutztown.edu/~ccarr419/checkout.php
	Course:      	CSC 242 - Fall 2013
*/


//Create page with same style sheet and links as rest of website
echo 	"<html xmlns = 'http://www.w3.org/1999/xhtml'>
		<head>
		<title>      Chris' Book Store      </title>
		<script type = 'text/javascript'>
		<!--
		function cancelOrder()
		{
			var answer = confirm('Are you sure you want to cancel this order?');
			if(answer == true)
				window.location.href = 'myproject.php';
		}
		//-->
		</script>
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

//Open database
$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
$username = 'ccarr419';
$password = 'S7treyuB';

$db = new PDO($dsn, $username, $password);

//Create table for the order
$query = "SELECT * FROM Products";
$products = $db->query($query);
echo		"<form name = 'order' action = 'purchasemade.php' method = 'post'><table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
			<thead>
			<tr>
			<th>Title</th>
			<th>Product ID</th>
			<th>Quantity</th>
			<th>Price</th>
			<th>S&H</th>
			<th>Tax</th>
			<th>Total</th>
			</tr>
			</thead>";
				
//Display, product title, product id, quantity, price, shipping and handling, tax, and total price
foreach($purchases as $id => $qty)
{	foreach($products as $product)
	{	if($id == $product['ProductID'])
		{	echo	"<tr><td><div class = 'special'>" . $product['Title'] . "</div></td>
				<td><div class = 'special'>$id</div></td><input type = 'hidden' name = 'id' value = '$id'/>
				<td><div class = 'special'><input type 'text' name = 'qty' value = '$qty' size = '3' readOnly/></div></td>";
			$price = $qty * $product['Price'];
			echo	"<td><div class = 'special'>$" . $price . "</div></td>";
			if($price < 25)
				$sNh = 4.50;
			else if($price < 50)
				$sNh = 7.00;
			else
				$sNh = 10.25;
			echo	"<input type = 'hidden' name = 'sNh' value = '$sNh'/><td><div class = 'special'>$" . $sNh . "</div></td>";
			$tax = ($price + $sNh) * 0.06;
			$tax = round($tax, 2);
			echo	"<input type = 'hidden' name = 'tax' value = '$tax'/><td><div class = 'special'>$" . $tax . "</div></td>";
			$total = ($price + $sNh + $tax);
			echo	"<input type = 'hidden' name = 'total' value = '$total'/><td><div class = 'special'>$" . $total . "</div></td></tr>";
		}
	}
}
	
echo 	"</table><br/><input type = 'submit' value = 'Comfirm Purchase'/>&nbsp;<input type = 'button' value = 'Cancel Order' onClick = 'cancelOrder()'</form></div></body>
	</html>";

?>