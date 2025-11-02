<!--
Name: LED Control
Author: Jacob Jaffe
Date: November 2, 2025
Description: This program controls the value in results.txt using two buttons. These buttons represent on and off,
and the value of the one last pressed will be written to results.txt for the ESP to then read the value of. The page
queries the value in results.txt every 3 seconds so if someone else changes it, the correct value is displayed.
Input: on/off buttons
Output: text "on" or "off" in results.txt
!-->
<!DOCTYPE html>
<html>
<head>
    <title>LED Control</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 100px;
            background-color: #f2f2f2;
        }
        h1 {
            color: #333;
        }
        form {
            margin: 20px;
        }
        button {
            padding: 15px 30px;
            margin: 10px;
            font-size: 18px;
            border: none;
            border-radius: 8px;
            cursor: pointer;
        }
        .on {
            background-color: #4CAF50;
            color: white;
        }
        .off {
            background-color: #f44336;
            color: white;
        }
    </style>
</head>
<body>
    <h1>LED Control Panel</h1>
    <form method="post">
        <button class="on" name="led" value="on">Turn ON</button>
        <button class="off" name="led" value="off">Turn OFF</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        $state = $_POST["led"];

        // Write to results.txt
        file_put_contents("results.txt", $state);

        echo "<h2>LED is now: <span style='color:" . 
            ($state === "on" ? "green" : "red") . ";'>" . strtoupper($state) . "</span></h2>";
    }
    ?>
    <h1>LED Status</h1>
    <div id="status">Checking...</div>
    <script>
            // Function to check results.txt every few seconds
        function checkLEDState() {
            fetch('results.txt?nocache=' + new Date().getTime()) // prevent caching
                .then(response => response.text())
                .then(text => {
                    document.getElementById('status').textContent = 'LED is ' + text.trim().toUpperCase();
                })
                .catch(err => {
                    document.getElementById('status').textContent = 'Error reading state';
                    console.error(err);
                });
        }

        // Run immediately and then every 3 seconds
        checkLEDState();
        setInterval(checkLEDState, 3000);
    </script>
</body>
</html>