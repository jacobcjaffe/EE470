<!DOCTYPE html>
<html>
<head>
	<title>Dashboard Stuff</title>
	<style type="text/css">
		#chart-container {
			width: 640px;
			height: auto;
		}
	</style>
</head>
<body>
	<header>
		<h1>Sensor Register and Data</h1>
	</header>

	<div id="chart-container">
	<canvas id="mycanvas"></canvas>
	</div>

	<!-- javascript -->
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
	<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.7.1/chart.min.js"></script>
	<!-- This is the location of app.js file - we are assuming it is in the same folder as this file-->
	<script type="text/javascript" src="app.js"></script>

	<?php
		// function to build a table
		function buildTable($array) {
		    $html = '<table border="1" cellpadding="5" cellspacing="0">';
		    
		    // add header
		    if (!empty($array)) {
			$html .= '<tr>';
			foreach (array_keys($array[0]) as $header) {
			    $html .= "<th>" . htmlspecialchars($header) . "</th>";
			}
			$html .= '</tr>';
		    }

		    // Add rows
		    foreach ($array as $row) {
			$html .= '<tr>';
			foreach ($row as $cell) {
			    $html .= "<td>" . htmlspecialchars($cell) . "</td>";
			}
			$html .= '</tr>';
		    }

		    $html .= '</table>';

		    return $html;
		}

                //database
                define('DB_HOST', '185.212.71.102');
                define('DB_USERNAME', 'u719884646_db_JacobJaffe');
                define('DB_PASSWORD', 'EEatSSU88!');
                define('DB_NAME', 'u719884646_JacobJaffe');

                //get connection
                $mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

                if(!$mysqli){
                  die("Connection failed: " . $mysqli->error);
                }

                //query to get the sensor measurement data
                $querydata = sprintf("SELECT * FROM sensor_data ORDER BY node_name ASC, time_received DESC");

                //execute query
                $resultdata = $mysqli->query($querydata);

                //loop through the returned data
                $data = array();
                foreach ($resultdata as $row) {
                  $data[] = $row;
                }

		// query to get the sensor register data
		$queryregister = sprintf("SELECT * FROM sensor_register ORDER BY node_name ASC");

		//execute query
		$resultregister = $mysqli->query($queryregister);

                //loop through the returned data
                $register = array();
                foreach ($resultregister as $row) {
                  $register[] = $row;
                }

		// get the average temperature
		$avgTempQuery = sprintf("SELECT AVG(temperature) AS temp FROM sensor_data WHERE node_name='node_1';");
		$resultAvgTemp = $mysqli->query($avgTempQuery);
		if ($resultAvgTemp) {
			$row = $resultAvgTemp->fetch_assoc();
			$avgTemp = $row['temp'];
		}

		$avgHumQuery = sprintf("SELECT AVG(humidity) AS hum FROM sensor_data WHERE node_name='node_1';");
		$resultAvgHum = $mysqli->query($avgHumQuery);
		if ($resultAvgHum) {
			$row = $resultAvgHum->fetch_assoc();
			$avgHum = $row['hum'];
		}

                //close connection
                $mysqli->close();

		// build the table for the register
		echo "<h2>Sensor Register</h2>";
		echo buildTable($register);

		echo "<p>There average temperature recorded from node 1 is $avgTemp degrees Celcius.</p>";
		echo "<p>There average humidity recorded from node 1 is $avgHum percent.</p>";

		// build the table for the data
		echo "<h2>Sensor Data Table</h2>";
		echo buildTable($data);
	?>

</body>
</html>
