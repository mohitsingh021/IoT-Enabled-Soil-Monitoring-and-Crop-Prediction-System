#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>  // For GPS and NPK communication

// Initialize LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
#define SOIL_MOISTURE_PIN A0
#define RAIN_DIGITAL 2      // D0 connected to Digital Pin 2
#define RAIN_ANALOG A1      // A1 connected to Analog Pin A1
#define ONE_WIRE_BUS 7      // DS18B20 data pin

// Setup OneWire instance and DallasTemperature instance
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Variables for sensor values
int soilMoistureValue = 0;
float temperatureValue = 0.0;
int rainValue = 0;  // Analog rain sensor value
int rainDigital = 0; // Digital rain sensor value

void setup() {
  // Start serial communication for Serial Monitor
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Soil Analysis");
  delay(2000);
  lcd.clear();

  // Initialize DS18B20 sensor
  sensors.begin();

  // Print startup message
  //Serial.println("Soil Analysis System Initialized");
}

void loop() {
  // Read soil moisture and map to percentage
  soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  int soilMoisturePercent = map(soilMoistureValue, 0, 1023, 0, 100);

  // Request and read temperature
  sensors.requestTemperatures();
  temperatureValue = sensors.getTempCByIndex(0);

  // Read rain drop sensor values
  rainDigital = digitalRead(RAIN_DIGITAL);
  rainValue = analogRead(RAIN_ANALOG);

  // Determine if rain is detected (Yes or No)
  String isRain = (rainDigital == HIGH) ? "No" : "Yes";

  // Print sensor data in CSV format
  Serial.print(soilMoisturePercent);  // Soil moisture
  Serial.print(",");
  Serial.print(temperatureValue);    // Temperature
  Serial.print(",");
  Serial.print(isRain);              // Rain status ("Yes" or "No")
  Serial.print(",");
  Serial.println(rainValue);         // Rain analog value

  // Display data on LCD
  lcd.setCursor(0, 0);
  lcd.print("Soil: ");
  lcd.print(soilMoisturePercent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureValue);
  lcd.print(" C");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Rain: ");
  lcd.print(isRain);

  lcd.setCursor(0, 1);
  lcd.print("Intensity: ");
  lcd.print(rainValue);

  delay(2000);
  lcd.clear();
}


