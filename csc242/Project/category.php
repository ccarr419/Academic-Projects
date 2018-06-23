<?php
session_start();
$loggedin = $_SESSION['loggedin'];

/*
	Name:         	Christian Carreras
	Project: 	Designing Web Page
	Purpose:	Book store website
	URL:         	http://unixweb.kutztown.edu/~ccarr419/category.php
	Course:      	CSC 242 - Fall 2013
*/

echo	"<html>
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
	<h3><div class = 'header'>Choose another category? <a class = 'link2' href = 'categories.php'>Click here</a></div></h3>";
	
//Open database
$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
$username = 'ccarr419';
$password = 'S7treyuB';

$db = new PDO($dsn, $username, $password);

$query = "SELECT * FROM Categories";
$categories = $db->query($query);

$j = 1;

//get post info from categories.php
$selectedCategory = array();
foreach($categories as $category)
{	$selectedCategory[] = $_POST[$category['CategoryID']];
}

//Display products of selected category in a table
$categories = $db->query($query);
foreach($categories as $category)
{	foreach($selectedCategory as $i)
	{	if($i == $category['CategoryName'])
		{	echo	"<form name = 'order' action = 'viewcart.php' method = 'post'><div class = 'special'><table style = 'margin-right: auto; margin-left:auto' border = '1' cellpadding = '5' bgcolor = '#aaaaaa'>
				<caption><h1 class = 'header'>" . $category['CategoryName'] . "</h1></caption><thead>
				<tr>
				<th><div class = 'special'>Title</div></th>
				<th><div class = 'special'>Author</div></th>
				<th><div class = 'special'>Product ID</div></th>
				<th><div class = 'special'>Price</div></th>
				<th><div class = 'special'>Quantity</div></th>
				</tr></thead>";
				$query = "SELECT * FROM Products";
				$products = $db->query($query);
				
				foreach($products as $product)
				{	if($product['CategoryID'] == $category['CategoryID'])
					{	echo "<tr><td><div class = 'special'>";
						echo $product['Title'];
						echo "</div></td><td><div class = 'special'>";
						echo $product['Author1'];
						echo "</div></td><td><div class = 'special'>";
						echo $product['ProductID'];
						echo "</div></td><td><div class = 'special'>$";
						echo round($product['Price'],2);
						echo "</div></td><td><div class = 'special'>
						<input type = 'text' name = '" . $product['ProductID'] . "' min = '0' max = '";
						echo $product['Quantity'];
						echo "' value = '0' size = '3'/></div></td></tr>";
						$j++;
					}
				}
				echo "</table></div><br/><input type = 'submit' value = 'Add to Cart'/></form>";
		}
	}
}

echo "
   </body>
</html>";

?>