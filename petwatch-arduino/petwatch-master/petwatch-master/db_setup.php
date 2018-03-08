<?php

require 'db_config.php';

$conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
if(!$conn){
  die('Could not connect: '.mysql_error());
}

$userTable = "CREATE TABLE Users ( user_id INTEGER, first_name VARCHAR(255), last_name VARCHAR(255), pets_name VARCHAR (255), email VARCHAR(255), password VARCHAR(255) );";
$result = $conn ->query($userTable);
//TODO: what does result turn back in this instance, check made table correctly

$testTable = "CREATE TABLE Ellie ( log_time INTEGER, accel INTEGER, temp INTEGER, humid INTEGER, tag_id INTEGER, tag_time INTEGER);";
$result = $conn -> query($testTable);
//TODO: change the data types to more accurate ones

?>
