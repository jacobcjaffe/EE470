
<?php
    // Overview: A program that inserts data into the sensor_data table. It uses my credentials to log in, then looks 
    // at the URL for the parameters. If the query parameters are base64 encoded, it will attempt to do so. Then it pushes
    // if all humidity, temperature, and node_name are present. Time received is optional, and if not present, it will use
    // the present time.
    // Author: Jacob Jaffe
    // Input: humidity, temperature, and node_name. time_received is optional
    // Output: none
    // Date: 10/14/2025

	echo "<h3>Trying to insert value...</h3>";
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
	$node_name = "";
	$temperature = "";
	$humidity = "";
	$t = "";
	$iscoded = false;
	$tempreq = false;
	if (isset($_GET['node_name']) && isset($_GET['temperature']) && isset($_GET['humidity'])) {
		$node_name = $_GET['node_name'];
		$temperature = $_GET['temperature'];
		$humidity = $_GET['humidity'];
		echo "<p> node_name: $node_name, temperature: $temperature, humidity: $humidity, ";
	}
	else {
		$iscoded = true;
	}
	// if decoding not required
	if (!$iscoded) {
		if (isset($_GET['time_received'])) {
			$t = $_GET['time_received'];
		}
		else {
			$t = date('Y-m-d H:i:s');
		}
		echo "temperature: $t</p>";
	}
	else { // decoding required
		// get the query string
		$query = $_SERVER['QUERY_STRING'] ?? '';

		// make sure the string is safe to decode with the function
		$query = strtr($query, '-_', '+/');

		// Fix missing padding
		if (strlen($query) % 4 !== 0) {
		    $query .= str_repeat('=', 4 - (strlen($query) % 4));
		}

		// Decode the query string
		$decoded = base64_decode($query, true);

		if ($decoded === false) {
		    echo "Invalid base64 data!";
		} else {
		    echo "Decoded value: " . htmlspecialchars($decoded, ENT_QUOTES, 'UTF-8');
		}
		parse_str($decoded, $params);
		print_r($params);

		// parse the parameters from the query string
		if (isset($params['node_name']) && isset($params['temperature']) && isset($params['humidity'])) {
			$temperature = $params['temperature'];
			$humidity = $params['humidity'];
			$node_name = $params['node_name'];
		}
		else {
			die("not valid base64 encoded data, needs node_name, temperature, humidity encoded in base 64");
		}

		if (isset($params['time_received'])) {
			$t = $params['time_received'];
		}
		else {
			$t = date('Y-m-d H:i:s');
		}
		echo "temperature: $t</p>";

		echo "<p>base64 decode successful</p>";
	}
	

	$sql = "INSERT INTO sensor_data (node_name, temperature, humidity, time_received) VALUES (?, ?, ?, ?)";
	$prep = $mysqli->prepare($sql);
	if(!$prep) {
		https_response_code(500);
		die("sql preparation failed" . $mysqli->error);
	}

	$prep->bind_param('ssss', $node_name, $temperature, $humidity, $t);

	if(!$prep->execute()) {
		https_response_code(500);
		die("sql execution failed" . $mysqli->error);
	}
	echo "<p>inserting data successful</p>";
?>
