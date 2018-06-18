<?php
session_start();
$loggedin = $_SESSION['loggedin'];

/*
	Name:         	Christian Carreras
	Project: 	Designing Web Page
	Purpose:	Book store website
	URL:         	http://unixweb.kutztown.edu/~ccarr419/contact.php
	Course:      	CSC 242 - Fall 2013
*/


//Create page with same style sheet and links as rest of website
echo "<html xmlns = 'http://www.w3.org/1999/xhtml'>
   <head>
      <title>      Contact Us       </title>
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
echo	"<a class = 'link' href = 'createaccount.php'>Create Account</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'contact.php'>Contact Us</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'categories.php'>Categories</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'searchstart.php'>Search</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'orders.php'>View Orders</a> &nbsp; | &nbsp;
	<a class = 'link' href = 'viewcart.php'>View Cart</a>
	</p></h3>
	<br/>
	
	<h3><p class = 'one'>
	<!-- About Us/Contact Us information -->
	We here at Chris' Book Store try to give you the best price<br/>
	and utmost satisfaction or your money back guarantee!<br/><br/> 
	Any questions?<br/><br/>
	Give us a call at: 1800-555-4795<br/> <!-- Fake phone number -->
	Send us an email at: ccarr419@live.kutztown.edu<br/><br/>
	Or send us a letter at:<br/>
	15200 Kutztown Rd.<br/> <!-- Fake street address -->
	Kutztown, Pa 19530<br/><br/>
	Also check out my official website here: 
	<!-- Link back to home site -->
	<a href = 'http://unixweb.kutztown.edu/~ccarr419/index.html'>Chris' Official Website</a>
	</p></h3>
	</div>
	


   </body>
</html>";

?>