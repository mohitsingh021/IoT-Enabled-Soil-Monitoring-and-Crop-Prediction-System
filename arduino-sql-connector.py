import serial
import mysql.connector
from datetime import datetime

# Configure Serial Port
arduino_port = 'COM12'  # Replace with your Arduino's port
baud_rate = 9600       # Match the baud rate of your Arduino
ser = serial.Serial(arduino_port, baud_rate)

# Connect to SQL Database
db = mysql.connector.connect(
    host="localhost",
    user="root",          # Replace with your MySQL username
    password="rootroot",  # Replace with your MySQL password
    database="soil_data"
)
cursor = db.cursor()

# Read from Arduino and Save to Database 
try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            # Assuming data is sent as "soil_moisture,soil_temp,is_rain,rain_value"
            soil_moisture, soil_temp, is_rain, rain_value = data.split(',')

            # Insert into SQL table
            query = "INSERT INTO soil_results (soil_moisture, soil_temp, is_rain, rain_value) VALUES (%s, %s, %s, %s)"
            cursor.execute(query, (float(soil_moisture), float(soil_temp), is_rain, float(rain_value)))
            db.commit()
            print(f"Data saved: soil_moisture={soil_moisture}, soil_temp={soil_temp}, is_rain={is_rain}, rain_value={rain_value}")

except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()
    db.close()
    print("Successfully exited the db.")
