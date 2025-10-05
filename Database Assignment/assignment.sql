-- create the sensor_register table
CREATE TABLE sensor_register(
    node_name VARCHAR(10) NOT NULL,
    -- it must have a name
    manufacturer VARCHAR(10) NOT NULL,
    -- it must have a manufacturer name
    longitude DOUBLE(15, 12),
    -- longitude and latitude, decimal with maximum of 15 digits
    latitude DOUBLE(15, 12),
    -- 3 digits max before the decimal, so we restrict desimals to 12 digits
    PRIMARY KEY(node_name)
); 

-- create the sensor data table
CREATE TABLE sensor_data(
    measurement_id INT NOT NULL AUTO_INCREMENT, -- good practice to always have primary key
    node_name VARCHAR(10) NOT NULL,
    time_received DATETIME CHECK (time_received >= '2022-10-1 11:00:00'), -- make sure datetime is above October 1, 2022 11:00 AM
    temperature DOUBLE(6, 4)
    	CHECK
        	(temperature BETWEEN -10 AND 100), 
    		-- limits two four decimal places, only 100 is the outlier where it could allow 3, but we won't allow anything above 100
    humidity DOUBLE(6, 4)
    	CHECK
        	(humidity BETWEEN 0 AND 100),
    PRIMARY KEY(measurement_id),
    FOREIGN KEY(node_name) REFERENCES sensor_register(node_name)
);

-- Create a trigger for every time we insert into sensor data to make sure that
-- the data is a half hour apart
DELIMITER $$ -- for stored routine
CREATE TRIGGER timecheck
BEFORE INSERT ON sensor_data
FOR EACH ROW
BEGIN 
	IF EXISTS (
        SELECT 1 FROM sensor_data d
        WHERE d.node_name = NEW.node_name
        	AND d.time_received > DATE_SUB(NEW.time_received, INTERVAL 30 MINUTE)
        ) THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'measurements from the same node must be 30 minutes apart or more';
        -- user defined error, measurements have to be 30 minutes apart
    END IF;
END$$
DELIMITER ;

-- insert 5 different nodes with different manufacturers
INSERT INTO sensor_register(node_name, manufacturer, longitude, latitude) VALUES
	('node_1', 'Samsung', 38, 122),
     ('node_2', 'Motorola', 38.12, 122.01),
     ('node_3', 'Microchip', 38.15, 121.98),
     ('node_4', 'Infineon', 38.54, 122.4223),
     ('node_5', 'TI', 38.32, 122.222);

-- insert sensor data, 4 records for each sensor, starting at October 1, 2022 11:00 AM
INSERT INTO sensor_data(node_name, time_received, temperature, humidity) VALUES
	('node_1', '2022-10-01 11:00:00', 27, 11),
    ('node_1', '2022-10-01 11:30:00', 28, 12),
    ('node_1', '2022-10-01 12:00:00', 22, 14),
    ('node_1', '2022-10-01 12:30:00', 27, 14),
    ('node_2', '2022-10-01 11:00:00', 25, 11),
    ('node_2', '2022-10-01 11:30:00', 27.3, 13),
    ('node_2', '2022-10-01 12:00:00', 28, 13),
    ('node_2', '2022-10-01 12:30:00', 23, 14),
    ('node_3', '2022-10-01 11:00:00', 25, 9),
    ('node_3', '2022-10-01 11:30:00', 22, 24),
    ('node_3', '2022-10-01 12:00:00', 21, 2),
    ('node_3', '2022-10-01 12:30:00', 20, 2),
    ('node_4', '2022-10-01 11:00:00', 21, 10),
    ('node_4', '2022-10-01 11:30:00', 22, 13),
    ('node_4', '2022-10-01 12:00:00', 21, 12),
    ('node_4', '2022-10-01 12:30:00', 20, 2),
    ('node_5', '2022-10-01 11:00:00', 13, 9),
    ('node_5', '2022-10-01 11:30:00', 12, 11),
    ('node_5', '2022-10-01 12:00:00', 11, 33),
    ('node_5', '2022-10-01 12:30:00', 20, 12);


-- create a view of both tables information as a join
CREATE VIEW sensor_combined AS
SELECT
	d.node_name,
    d.time_received,
	d.temperature, 
    d.humidity,
    r.manufacturer,
    r.latitude,
    r.longitude
FROM 
	sensor_data AS d
JOIN
	sensor_register AS r ON d.node_name = r.node_name; -- join on the node_name

-- this will fail because 'node_19' is not a registered node
INSERT INTO sensor_data (node_name, time_received, temperature, humidity) VALUES 
	('node_19', '2022-10-01 14:00:00', 12, 12);
