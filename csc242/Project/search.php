<?php
session_start();
$loggedin = $_SESSION['loggedin'];
/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/search.php
     Course:      	CSC 242 - Fall 2013
*/

//Create page with same style sheet and links as rest of website
echo "<html>
	<head>
	<title>Search Results</title>
	<link rel = 'stylesheet' type = 'text/css' href = 'projectstyle.css'/>
	</head>
	<body>
	<div class = 'header'><h1>Chris' Book Store</h1></div>
	<div class = 'special'>
	<h3><p class = 'one'>
	<a class = 'link' href = 'myproject.php'>Home</a> &nbsp; | &nbsp;";
	if($loggedin == true)
			echo "<a class = 'link' href = 'loggedout.php'>Log Out</a> &nbsp; | &nbsp;";
		else
			echo "<a class = 'link' href = 'login.html'>Log In</a> &nbsp; | &nbsp;";
echo	"<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'viewcart.php'>View Cart</a>
	</p></h3>
	<h3><div class = 'header'>Search again? <a class = 'link2' href = 'searchstart.php'>Click here</a></div></h3>";

//Variables taken from searchstart.php
$isbn = $_POST['isbn'];
$keyword = $_POST['keyword'];

//Create PDO object & connect to database
$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
$username = 'ccarr419';
$password = 'S7treyuB';

$db = new PDO($dsn, $username, $password);

//Get info from the Categories table

//If the user searched by ISBN
if($isbn != NULL)
{	$query = "SELECT * FROM Products";
	$products = $db->query($query);
	echo "<h2 class = 'header'>SEARCH RESULTS FOR: $isbn</h2>";
	
if(!checkEmpty($products, $isbn))
	{	echo "<h1 class = 'header'><div style = 'color: red'>No Results Found</div></h1>"; }
	
else	
{	$query = "SELECT * FROM Products";
	$products = $db->query($query);
	//Create a table containing the search result
	echo "<form name = 'orderisbn' action = 'viewcart.php' method = 'post'><table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
		<thead>
		<tr>
		<th>Title</th>
		<th>Author</th>
		<th>Category</th>
		<th>Product ID</th>
		<th>Price</th>
		<th>Quantity</th>
		</tr></thead>";
	$i = 1;
	foreach($products as $product)
	{	if($product['ProductID'] == $isbn)
		{	echo "<tr><td><div class = 'special'>";
			echo $product['Title'];
			echo "</div></td><td><div class = 'special'>";
			echo $product['Author1'];
			echo "</div></td><td><div class = 'special'>";
			$query = "SELECT * FROM Categories";
			$categories = $db->query($query);
			foreach($categories as $category)
				if($category['CategoryID'] == $product['CategoryID'])
					echo $category['CategoryName'];
			echo "</div></td><td><div class = 'special'>";
			echo $product['ProductID'];
			echo "</div></td><td><div class = 'special'>$";
			echo round($product['Price'],2);
			echo "</div></td><td><div class = 'special'><input type = 'text' name = '" . $product['ProductID'] . "' min = '0' max = '";
			echo $product['Quantity'];
			echo "' value = '0' size = '3'/></div></td></tr>";
			$i++;
		}
	}
	
	echo "</table><br/><input type = 'submit' value = 'Add to Cart'/></form></div>
	</body></html>";
}
}

//If the user searched by keyword
if($keyword != NULL)
{	$query = "SELECT * FROM Products";
	$products = $db->query($query);
	echo "<h1 class = 'header'>SEARCH RESULTS FOR: $keyword</h1>";
	
if(!checkEmpty($products, $keyword))
	{	echo "<h1 class = 'header'><div style = 'color: red'>No Results Found</div></h1>"; }
	
else	
{	$query = "SELECT * FROM Products";
	$products = $db->query($query);
	//Create table containing the search result(s)
	echo "<form name = 'orderkeyword' action = 'viewcart.php' method = 'post'><table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
		<thead>
		<tr>
		<th>Title</th>
		<th>Author</th>
		<th>Category</th>
		<th>Product ID</th>
		<th>Price</th>
		<th>Quantity</th>
		</tr></thead>";
		
	foreach($products as $product)
	{	if(strpos($product['Title'], $keyword) !== false)
		{	echo "<tr><td><div class = 'special'>";
			echo $product['Title'];
			echo "</div></td><td><div class = 'special'>";
			echo $product['Author1'];
			echo "</div></td><td><div class = 'special'>";
			$query = "SELECT * FROM Categories";
			$categories = $db->query($query);
			foreach($categories as $category)
				if($category['CategoryID'] == $product['CategoryID'])
					echo $category['CategoryName'];
			echo "</div></td><td><div class = 'special'>";
			echo $product['ProductID'];
			echo "</div></td><td><div class = 'special'>$";
			echo round($product['Price'],2);
			echo "</div></td><td><div class = 'special'><input type = 'text' name = '" . $product['ProductID'] . "' min = '0' max = '";
			echo $product['Quantity'];
			echo "' value = '0' size = '3'/></div></td></tr>";
		}
	}
	
	echo "</table><br/><input type = 'submit' value = 'Add to Cart'/></form></div>
	</body></html>";
}
}

//Checks if result list is empty
function checkEmpty($products, $searchItem)
{	foreach($products as $product)
	{	if(strpos($product['Title'], $searchItem) !== false || $product['ProductID'] == $searchItem)
			return true;
	}
	return false;
}
	

?>