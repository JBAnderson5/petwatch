<?php
	require 'db_config.php';
	
	$conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
	if(!$conn){
			logToFile("connection test failed");
			die('Could not connect: ' . mysql_error());
	}
	
	else{
		mysqli_close($conn);
		logToFile("connection test succeeded");
	}
?>
