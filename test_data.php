<?php

require 'db_config.php';

$conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
if(!$conn){
  die('Could not connect: '.mysql_error());
}

$log_time = 1;
$accel = 1;
$temp = 1;
$humid = 1;
$tag_id = 1;
$tag_time = 1;

$stmt = "INSERT INTO Ellie VALUES (".$log_time.", ".$accel.", ".$temp.", ".$humid.", ".$tag_id.", ".$tag_time.");";
echo $stmt;
$result = $conn->query($stmt);

?>
