<?php
 require 'db_config.php';
  $conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
	if(!$conn){
			echo("connection to server failed");
			die('Could not connect: ' . mysql_error());
	}
    $stmt="DELETE FROM accelData;";
    $result=$conn->query($stmt);
    echo $result;
    $stmt="DELETE FROM tempData;";
    $result=$conn->query($stmt);
    echo $result;

?>