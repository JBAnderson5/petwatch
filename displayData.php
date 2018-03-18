<!DOCTYPE html>
<head>
	<title>accel data</title>
</head>
<body>
	<div class = "petData">


<?php
 require 'db_config.php';
  $conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
	if(!$conn){
			echo("connection to server failed");
			die('Could not connect: ' . mysql_error());
	}

	$stmt="SELECT * FROM accelData;";
	$result=$conn->query($stmt);
	$tstmt="SELECT * FROM tempData;";
	$tresult=$conn->query($tstmt);


	if($result->num_rows > 0){
	echo "<table><tr><th>time</th><th>accel</th><th>time</th><th>temp</th><th>hum</th><th>HI</th></tr>";
	while($row = $result->fetch_assoc()){

	if($trow=$tresult->fetch_assoc()){
	  $temp = "<td>".$trow["time"]."</td><td>".$trow["temp"]."</td><td>".$trow["hum"]."</td><td>".$trow["HI"]."</td></tr>";
	}
	else{
	 $temp="</tr>";
	}
		echo "<tr><td>".$row["time"]."</td><td>".$row["accel"]."</td>".$temp;
	}
	echo "</table>";
}
	mysqli_close($conn);

?>

</div>

</body>
