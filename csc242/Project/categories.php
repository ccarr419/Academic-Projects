<?php
session_start();
$loggedin = $_SESSION['loggedin'];
/*
	Name:         	Christian Carreras
	Project: 		Designing Web Page
	Purpose:	   	Book store website
	URL:         		http://unixweb.kutztown.edu/~ccarr419/categories.php
	Course:      		CSC 242 - Fall 2013
*/

//Create page with same style sheet and links as rest of website
echo "<html xmlns = 'http://www.w3.org/1999/xhtml'>
	<head>
		<title>      Categories      </title>
		
		<script type = 'text/javascript'>
		<!--
		function categorySubmit(& category)
		{	document.forms('category').submit();
		}
		//-->
		</script>
	
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
echo		"<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'viewcart.php'>View Cart</a>
		</p></h3></div><br/>
		";
	
	//Connect to database
	$dsn = 'mysql:host=localhost;dbname=ccarr419_bookstore';
	$username = 'ccarr419';
	$password = 'S7treyuB';

	$db = new PDO($dsn, $username, $password);
	
	//Get info from Categories table
	$query = "SELECT * FROM Categories";
	$categories = $db->query($query);
	$i = 1;
	
	//Place info into a button
	foreach($categories as $category)
	{	echo	"<form name = 'category$i' action = 'category.php' method = 'post'>
			<div class = 'header'>
			<input type = 'hidden' id = '" . $category['CategoryName'] . "' name = '" . $category['CategoryID'] . 
			"' value = '" . $category['CategoryName'] . "'/>
			<input type = 'submit' value = '" . $category['CategoryName'] . "'/>
			</div></form>
			";
		$i++;
	}

echo "
   </body>
</html>";

?>