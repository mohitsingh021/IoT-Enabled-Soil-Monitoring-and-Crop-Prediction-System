CREATE DATABASE soil_data;
USE soil_data;

CREATE TABLE soil_results (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    soil_moisture FLOAT,
    soil_temp FLOAT,
    is_rain VARCHAR(5),
    rain_value FLOAT
);

SELECT * FROM soil_results;