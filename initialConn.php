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
		//echo "<p> Time: " . $time . "</p>";
		//file_put_contents('display.html',$Write);

		

	  if($_POST['accelData']==1){
	    $index=$_POST['accelIndex'];
	    if($index==0)
	      break;


	    $accel=$_POST['accel'];
	    $time=$_POST['atime'];

	   

	    for($i = 0;$i<$index;$i++){
	 
	      $stmt="INSERT INTO accelData Values (".$time[$i]. ", " .$accel[$i].");";
	      echo $stmt;
	      $result=$conn->query($stmt);
	      if(!$result){
		logToFile('query failed: '.$stmt);
	      }
	    }

	  }

	  if($_POST['tempData']==1){
	    $index=$_POST['tempIndex'];
	    if($index==0)
	      break;


	    $temp=$_POST['temp'];
	    $hum=$_POST['hum'];
	    $HI=$_POST['HI'];
	    $time=$_POST['ttime'];

	   

	    for($i = 0;$i<$index;$i++){
	 
	      $stmt="INSERT INTO tempData Values (".$time[$i]. ", " .$temp[$i].", ".$hum[$i].", ".$HI[$i].");";
	      echo $stmt;
	      $result=$conn->query($stmt);
	      if(!$result){
		logToFile('query failed: '.$stmt);
	      }
	    }
	  }

      }
    
	
	


?>
