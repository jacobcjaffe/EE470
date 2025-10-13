<?php
//setting header to json
header('Content-Type: application/json');

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

//query to get data from the table
$query = sprintf("SELECT * FROM sensor_data");

//execute query
$result = $mysqli->query($query);

//loop through the returned data
$data = array();
foreach ($result as $row) {
  $data[] = $row;
}

//close connection
$mysqli->close();

//now print the data
print json_encode($data);
