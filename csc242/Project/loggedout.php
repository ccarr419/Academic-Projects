<?php
session_start();
unset($_SESSION);
session_destroy();
//Destroys session and logs the user out

/*
	Name:         	Christian Carreras
	Project: 	Designing Web Page
	Purpose:	Book store website
	URL:         	http://unixweb.kutztown.edu/~ccarr419/loggedout.php
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
		<a class = 'link' href = 'myproject.php'>Home</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'login.html'>Log In</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'viewcart.php'>View Cart</a>
		</p></h3><br/>
	<h3><p class = 'one'>You're now logged out! <a href = 'login.html' class = 'link'>Log back in?</a></p></h3>
	</div></body></html>";
	
?>