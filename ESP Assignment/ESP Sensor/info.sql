
CREATE TABLE SensorRegister (
    node_name VARCHAR(100) PRIMARY KEY,
    manufacturer VARCHAR(100),
    longitude DECIMAL(9,6),
    latitude DECIMAL(9,6)
);

CREATE TABLE SensorData (
    node_name VARCHAR(100),
    time_received DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    temperature FLOAT,
    humidity FLOAT,
    FOREIGN KEY (node_name) REFERENCES SensorRegister(node_name)
);


CREATE TABLE SensorActivity (
    node_name VARCHAR(100) PRIMARY KEY,
    record_count INT DEFAULT 0,
    FOREIGN KEY (node_name) REFERENCES SensorRegister(node_name)
);


DELIMITER //

CREATE TRIGGER after_sensor_data_insert
AFTER INSERT ON SensorData
FOR EACH ROW
BEGIN
    INSERT INTO SensorActivity (node_name, record_count)
    VALUES (NEW.node_name, 1)
    ON DUPLICATE KEY UPDATE record_count = record_count + 1;
END//

DELIMITER ;


INSERT INTO SensorRegister (node_name, manufacturer, latitude, longitude) VALUES 
("node_1", "man_1", 39.1, 122.8),
("node_2", "man_2", 40.1, 122.32),
("node_3", "man_3", 42.0, 123.09);


INSERT INTO SensorData (node_name, time_received, temperature, humidity) VALUES
("node_1", "2025-10-22 01:00:00", 74.1, 1.3),
("node_1", "2025-10-22 01:30:00", 82, 2.1),
("node_1", "2025-10-22 02:00:00", 68.9, 3),
("node_1", "2025-10-22 02:30:00", 71.5, 7.9),
("node_1", "2025-10-22 03:00:00", 87.1, 8.3),
("node_2", "2025-10-22 01:00:00", 74.1, 1.3),
("node_2", "2025-10-22 01:30:00", 82, 2.1),
("node_2", "2025-10-22 02:00:00", 68.9, 3),
("node_2", "2025-10-22 02:30:00", 71.5, 7.9),
("node_2", "2025-10-22 03:00:00", 87.1, 8.3);

ALTER TABLE SensorData
ADD CONSTRAINT unique_node_time UNIQUE (node_name, time_received);

SELECT * FROM SensorData;
