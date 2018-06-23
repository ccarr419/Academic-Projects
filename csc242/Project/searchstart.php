<?php
session_start();
$loggedin = $_SESSION['loggedin'];
/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/searchstart.php
     Course:      	CSC 242 - Fall 2013
*/

echo "<html xmlns = 'http://www.w3.org/1999/xhtml'>
   <head>
   <title>      Chris' Book Store      </title>
   
   <script type = 'text/javascript'>
   <!--
   
   //Check for empty input and send to search.php
   //Send ISBN to search by
   function sISBN()
   {	var isbn = document.getElementById('isbn').value;
	if(isbn.length < 1)
		window.alert('Please enter a ISBN to search for');
	else
		document.forms['searchISBN'].submit();
   }
   
   //Check for empty input and send to search.php
   //Send keyword to search by
   function sKeyword()
   {	var keyword = document.getElementById('keyword').value;
	if(keyword.length < 1)
		window.alert('Please enter a keyword to search for');
	else
		document.forms['searchKeyword'].submit();
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
echo		"<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
		<a class = 'link' href = 'viewcart.php'>View Cart</a>
		</p></h3></div>
		<br/>
		<!-- Textbox to search by ISBN -->
		<div class = 'header'>
		<form id = 'searchISBN' action = 'search.php' method = 'post'> 
		<h3><p><label>Search by ISBN: </label> &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'isbn' name = 'isbn' type = 'text'/>
		<!-- Click to search by ISBN -->
		<input type = 'button' value = 'Search' onClick = 'sISBN()'/></p></h3></form>
		<form id = 'searchKeyword' action = 'search.php' method = 'post'>
		<!-- Textbox to search by Keyword -->
		<h3><p><label>Search by Keyword: </label> &nbsp;
		<input id = 'keyword' name = 'keyword' type = 'text'/>
		<!-- Button to search by Keyword -->
		<input type = 'button' value = 'Search' onClick = 'sKeyword()'/></p></h3>
		</form>
		</div>		
   </body>
</html>";

?>
