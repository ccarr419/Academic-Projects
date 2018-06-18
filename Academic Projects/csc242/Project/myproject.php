<?php
session_start();
$loggedin = $_SESSION['loggedin'];
$name = $_SESSION['name'];

/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/myproject.php
     Course:      	CSC 242 - Fall 2013
*/

echo "<html xmlns = 'http://www.w3.org/1999/xhtml'>
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
		
		if($loggedin == true) //Checks if the user is logged in
			echo "<a class = 'link' href = 'loggedout.php'>Log Out</a> &nbsp; | &nbsp;";
		else
			echo "<a class = 'link' href = 'login.html'>Log In</a> &nbsp; | &nbsp;";
echo		"<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'viewcart.php'>View Cart</a>
		</p></h3>
		<br/>
		
		<!-- Opening page & disclaimer -->
		<h3><p class = 'one'>";
		if($loggedin == true)
			echo "Welcome, " . $name . "!<br/><br/>"; //Displays user's name if logged in
		else
			echo "Welcome!<br/><br/>";
echo		"This is Chris' Book Store!<br/>
		The ultimate site for purchasing books!<br/><br/>
		<div style = 'color: red'>Note: This site is not a legitimate book store and therefore<br/>
		will not and can not perform any transactions. This is just a class project.</div>
		</p></h3>
		</div>
		
   </body>
</html>";
?>

