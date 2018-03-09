<?php
 require 'db_config.php';
  $conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
	if(!$conn){
			echo("connection to server failed");
			die('Could not connect: ' . mysql_error());
	}
	else{
		$time=$_POST['prevTrans'];
		var_dump($_POST);
		echo "<p> Time: " . $time . "</p>";
		//file_put_contents('display.html',$Write);

		$dataType=$_POST['dataType'];

	  if($dataType=="accel"){
	    $index=$_POST['index'];
	    for($i = 0;$i<$index;$i++){
	      $temp='accel'+$i;
	      $accel=$_POST[$temp];
	      $temp='time'+$i;
	      $log_time=$POST[$temp];
	      $stmt="INSERT INTO Ellie Values (".$log_time. ", " .$accel.");";
	      echo $stmt;
	      $result=$conn->query($stmt);
	    }

	  }else if($dataType=="temp"){

	  }else{
	  //shouldn't run unless inital message
	  }

      }
    
	
	


?>
