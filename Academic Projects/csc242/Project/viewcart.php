<?php
session_start();
$loggedin = $_SESSION['loggedin'];
$purchases = $_SESSION['order'];

/*
     Name:         	Christian Carreas
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/orders.php
     Course:      	CSC 242 - Fall 2013
*/


//Create page with same style sheet and links as rest of website
echo 	"<html xmlns = 'http://www.w3.org/1999/xhtml'>
		<head>
		<title>      Chris' Book Store      </title>
		<script type = 'text/javascript'>
		<!--
		function removeOrder()
		{
			var answer = confirm('Are you sure you want to remove this from your shopping cart?');
			if(answer == true)
				window.location.href = 'removeOrder.php';
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
	
if($loggedin == false)
	echo "<h3><p class = 'one'>Please log in to add products to your shopping cart. <a href = 'login.html' class = 'link'>Log in?</a></p></h3>";

else
{	$orders = array();

	$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	$db = new PDO($dsn, $username, $password);

	$query = "SELECT * FROM Products";
	$products = $db->query($query);
	
	foreach($products as $product)
	{	$orders[$product['ProductID']] = $_POST[$product['ProductID']];
		$id[] = $product['ProductID'];
		if($orders[$product['ProductID']] <= 0)
			unset($orders[$product['ProductID']]);
	}
	
	if(countArray($purchases) > 0 && countArray($orders) == 0)
		$orders = $purchases;
	
	if(somethingOrdered($orders))
	{	$_SESSION['order'] = $orders;
		$query = "SELECT * FROM Products";
		$products = $db->query($query);
		echo	"<form name = 'order' action = 'checkout.php' method = 'post'><table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
				<thead>
					<tr>
					<th>Title</th>
					<th>Product ID</th>
					<th>Quantity</th>
					<th>Price</th>
					</tr>
				</thead>";
		
		foreach($orders as $id => $qty)
		{	foreach($products as $product)
			{	if($id == $product['ProductID'])
				{	echo	"<tr><td><div class = 'special'>" . $product['Title'] . "</div></td>
						<td><div class = 'special'>$id</div></td>
						<td><div class = 'special'><input type 'text' value = '$qty' size = '3' readOnly/></div></td>";
						$price = $qty * $product['Price'];
					echo	"<input type = 'hidden' name = '" . $product['ProductID'] . "' value = '" . $product['ProductID'] . "'/>
						<td><div class = 'special'>$" . $price . "</div></td></tr>";
				}
			}
		}
		echo	"</table><br/><input type = 'submit' value = 'Check Out'/>&nbsp;<input type = 'button' value = 'Remove Order' onClick = 'removeOrder()'/></form>";
						
	}
	else
	{
		echo "<h1 class = 'special'><div style = 'color: red'>Your Shopping Cart Is Empty!</div></h1>";
	}

}

echo 	"</div></body>
	</html>";

function somethingOrdered($orders)
{	foreach($orders as $order)
	{	if($order > 0 && $order != NULL)
			return true;
	}
	return false;
}

function countArray($arr)
{	$i = 0;
	if($arr == 0 || $arr == NULL)
		return $i;
	else
	{	foreach($arr as $a)
		{	$i++; }
	}
	return $i;
}
	
?>