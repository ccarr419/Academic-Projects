<?php
session_start();
unset($_SESSION['order']);

/*
	Name:         	Christian Carreras
	Project: 	Designing Web Page
	Purpose:	Book store website
	URL:         	http://unixweb.kutztown.edu/~ccarr419/removeOrder.php
	Course:      	CSC 242 - Fall 2013
*/

//Remove order and return to shopping cart
header("Location: viewcart.php");
?>