<?php
session_start();
$loggedin = $_SESSION['loggedin'];

/*
     Name:         	Christian Carreras
     Project: 		Designing Web Page
     Purpose:	   	Book store website
     URL:         	http://unixweb.kutztown.edu/~ccarr419/createaccount.php
     Course:      	CSC 242 - Fall 2013
*/

echo "<html xmlns = 'http://www.w3.org/1999/xhtml'>
   <head>
      <title>      Create An Account       </title>
	
	<script type = 'text/javascript'>
	<!--
	//Check if account fields are legitimate
	function account()
	{	//Variables
		var fname = document.getElementById('fname').value; //first name
		var lname = document.getElementById('lname').value; //last name
		var email = document.getElementById('email').value; //email
		var pass1 = document.getElementById('pass1').value; //password
		var pass2 = document.getElementById('pass2').value; //confirm password
		var add1 = document.getElementById('add1').value; //address 1
		var add2 = document.getElementById('add2').value; //address 2
		var city = document.getElementById('city').value; //city
		var state = document.getElementById('state'); //state
		var state = state.options[state.selectedIndex].value;
		var zip = document.getElementById('zip').value; //zip code
		var phone = document.getElementById('phone').value; //phone number
		
		//Check to make sure none of the required fields are empty
		//Also check that a state is selected
		if(fname.length < 1 || lname.length < 1 || email.length < 1 || pass1.length < 1 ||
		pass2.length < 1 || add1.length < 1 || city.length < 1 || zip.length < 1 || state == 'none')
		{	window.alert('Please fill out all required fields'); }
		
		//Check to make sure that the password and confirm password fields match
		else if(pass1 != pass2)
		{	window.alert('Your passwords do not match'); }
		
		//Make user have a legitimate password that is not too long for the database
		else if ((pass1.length < 5) || (pass1.length > 15))
		{	window.alert('Your password must be between 5 and 15 characters long'); }
		
		//Check to make sure the email entered is legitimate
		//Check is @ is present, along with a . and com, net, org etc.
		else if(email.indexOf('@') == -1 || email.indexOf('.') == -1 || email.length > 50 || (email.indexOf('com') == -1 &&
		email.indexOf('gov') == -1 && email.indexOf('org') == -1 && email.indexOf('edu') == -1 &&
		email.indexOf('net') == -1 && email.indexOf('mil') == -1) || email.length < 7)
		{	window.alert('Please enter a valid email address'); }
		
		//Check if name contains a number
		else if(isNaN(fname) == false || isNaN(lname) == false)
		{	window.alert('Your name cannot contain numbers'); }
		
		//Check if first name is too long for database
		else if(fname.length > 20)
		{	window.alert('Your first name is too long'); }
		
		//Check if last name is too long for database
		else if(lname.length > 25)
		{	window.alert('Your last name is too long'); }
		
		//Check if address is too long for database
		else if(add1.length > 50 || add2.length > 50)
		{	window.alert('That address is too long'); }
		
		//Check if city contains a number
		else if(isNaN(city) == false)
		{	window.alert('City name cannot contain numbers'); }
		
		//Check if city name is too long for database
		else if(city.length > 50)
		{	window.alert('City name is too long'); }
		
		//Check to make sure the zip code entered is legitimate
		else if(isNaN(zip) == true || zip.length != 5)
		{ 	window.alert('Please enter a valid zip code'); }
		
		//Check to make sure if a phone number is entered, it is legitimate
		else if(phone.length > 0 && (phone.length < 10 || phone.length > 11)) //Standard 555-555-5555 & 1800-555-5555
		{	window.alert('Please enter a valid phone number with no dashes'); }
		
		//Check to make sure if a phone number is entered, it is legitimate
		else if(phone.length > 0 && (isNaN(phone) == true)) //Make sure letters are not entered
		{	window.alert('Please enter a valid phone number with no dashes'); }
		
		//Everything is filled out and correct
		else
		{
			window.alert('Thank you for creating an account! Now please continue to log in!');
			document.forms['useraccount'].submit();
		}
		
	}
	//-->
	</script><noscript>Cannot Run JavaScript!</noscript>
	
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
	
	<!-- User input fields -->
	<form id = 'useraccount' action = 'useraccount.php' method = 'post'>
	<div style = 'text-align: center' class = 'header'>
		<h3><p><label>*First Name:&nbsp;</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'fname' name = 'fname' type = 'text'/></p></h3> <!-- User's first name -->
		<h3><p><label>*Last Name:</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'lname' name = 'lname' type = 'text'/></p></h3> <!-- User's last name -->
		<h3><p><label>*E-mail Address:&nbsp;</label> &nbsp; &nbsp;
		<input id = 'email' name = 'email' type = 'text'/></p></h3> <!-- User's desired email address to use -->
		<h3><p><label>*Password:</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'pass1' name = 'pass1' type = 'password'/></p></h3> <!-- User's desired password -->
		<h3><p><label>*Confirm Password:<label>
		<input id = 'pass2' name = 'pass2' type = 'password'/></p></h3> <!-- Confirm user's desired password -->
		<h3><p><label>*Address 1:</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'add1' name = 'add1' type = 'text'/></p></h3> <!-- Street address -->
		<h3><p><label>Address 2:</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'add2' name = 'add2' type = 'text'/></p></h3> <!-- Additional address information -->
		<h3><p><label>*City:</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'city' name = 'city' type = 'text'/></p></h3> <!-- City name -->
		<h3><p><label>*State: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;</label>
		<select id = 'state' name = 'state' > <!-- Drop down list with all 50 states -->
		<option value = 'none'>--(select a state)--</option>
		<option value = 'AL'>Alabama</option><option value = 'AK'>Alaska</option><option value = 'AZ'>Arizona</option>
		<option value = 'AR'>Arkansas</option><option value = 'CA'>California</option><option value = 'CO'>Colorado</option>
		<option value = 'CT'>Connecticut</option><option value = 'DE'>Delaware</option><option value = 'FL'>Florida</option>
		<option value = 'GA'>Georgia</option><option value = 'HI'>Hawaii</option><option value = 'ID'>Idaho</option>
		<option value = 'IL'>Illinois</option><option value = 'IN'>Indiana</option><option value = 'IA'>Iowa</option>
		<option value = 'KS'>Kansas</option><option value = 'KY'>Kentucky</option><option value = 'LA'>Louisiana</option>
		<option value = 'ME'>Maine</option><option value = 'MD'>Maryland</option><option value = 'MA'>Massachusetts</option>
		<option value = 'MI'>Michigan</option><option value = 'MN'>Minnesota</option><option value = 'MS'>Mississippi</option>
		<option value = 'MO'>Missouri</option><option value = 'MT'>Montana</option><option value = 'NE'>Nebraska</option>
		<option value = 'NV'>Nevada</option><option value = 'NH'>New Hampshire</option><option value = 'NJ'>New Jersey</option>
		<option value = 'NM'>New Mexico</option><option value = 'NY'>New York</option><option value = 'NC'>North Carolina</option>
		<option value = 'ND'>North Dakota</option><option value = 'OH'>Ohio</option><option value = 'OK'>Oklahoma</option>
		<option value = 'OR'>Oregon</option><option value = 'PA'>Pennsylvania</option><option value = 'RI'>Rhode Island</option>
		<option value = 'SC'>South Carolina</option><option value = 'SD'>South Dakota</option><option value = 'TN'>Tennessee</option>
		<option value = 'TX'>Texas</option><option value = 'UT'>Utah</option><option value = 'VT'>Vermont</option>
		<option value = 'VA'>Virginia</option><option value = 'WA'>Washington</option><option value = 'WV'>West Virginia</option>
		<option value = 'WI'>Wisconsin</option><option value = 'WY'>Wyoming</option>
		</select></h3>
		<h3><p><label>*Zip Code:</label> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'zip' name = 'zip' type = 'text'/></p></h3> <!-- Area zip code -->
		<h3><p><label>Phone Number:</label> &nbsp; &nbsp; &nbsp; &nbsp;
		<input id = 'phone' name = 'phone' type = 'text'/></p></h3> <!-- User's phone number -->
		<input type = 'button' value = 'Create Account' onClick = 'account()'/> <!-- Click to create account -->
		<input type = 'reset' value = 'Clear'/>
		<h3><p>* Required Field</p></h3>
	</div>
	</form>

   </body>
</html>";

?>
