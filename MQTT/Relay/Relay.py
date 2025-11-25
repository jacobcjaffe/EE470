
# Purpose: Connect to broker.hivemq.com on port 80 with a websocket, and then subscribe to the potentiometer topic
#      so that when the voltage read changes, it pushes the data to the database.
#  Dependencies: paho.mqtt.client and mysql.connector
#  Compiler: N/A
#  Author: Jacob Jaffe
#  OUTPUT: publishes the volts at the wiper of the potentiometer to the database.   
#  INPUT: Every time the voltage is published on the topic testtopic/temp/inputTopic/pot, the voltage
#      value is parsed to be pushed to the database.
#  SETUP: Make sure the topic for testtopic/temp/inputTopic/pot is set up to receive the volts read and that
#      the ESP is programmed and powered on.
#  Versions: 
#   v1: Nov-25-2025: It all works

import paho.mqtt.client as mqtt
import mysql.connector

HOST = "185.212.71.102"
USER = "u719884646_MQTT"
PASSWORD = ""
DATABASE = "u719884646_MQTT"

def push(sensorValue):
  connection = None  # Initialize connection to None
  try:
    connection = mysql.connector.connect(
        host=HOST,
        user=USER,
        password=PASSWORD,
        database=DATABASE
    )
    if connection.is_connected():
        #create a cursor object
        cursor = connection.cursor()
        query = "INSERT INTO sensor_data (volts, time) VALUES (%s, NOW())"
        values = (sensorValue,)
        cursor.execute(query, values)
        connection.commit()
        print(f"Value {sensorValue} inserted into sensor_value table")
  except mysql.connector.Error as err:
    print(f"Error: {err}")
  finally:
    if connection and connection.is_connected(): # Check if connection is not None before using it
      cursor.close()
      connection.close()
      print("MySQL connection is closed")

# define the MQTT broker and topic
BROKER_URL = "broker.hivemq.com"
BROKER_PORT = 8000 # Reverted to 8000 for WebSocket
TOPIC = "testtopic/temp/outTopic/pot"

# define callback for connection
def on_connect(client, userdata, flags, rc):
  if rc == 0:
    print("Connected to HiveMQ broker")
    client.subscribe(TOPIC)
    print(f"Subscribed to topic: {TOPIC}")
  else:
    print(f"Failed to connect, return code {rc}")

# define callback for receiving messages
def on_message(client, userdata, msg):
  print(f"Received message: {msg.payload.decode()} from topic:{msg.topic}")
  value = msg.payload.decode()[7:]
  print(f"Value: {value}")
  push(value)

# create an MQTT client instance
client = mqtt.Client(transport="websockets")

# attach callback functions
client.on_connect = on_connect
client.on_message = on_message

print("Connecting to broker...")
client.connect(BROKER_URL, BROKER_PORT, 60)

client.loop_forever()
