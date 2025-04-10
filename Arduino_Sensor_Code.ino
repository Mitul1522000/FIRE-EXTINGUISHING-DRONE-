#include <Wire.h>  // Include Wire library for I2C communication
#include <Adafruit_BMP085.h>  // Include Adafruit BMP085 (BMP180) sensor library
#include <SoftwareSerial.h>  // Include SoftwareSerial library for Bluetooth communication

// Define analog sensor pins
#define LDRpin A6   // LDR sensor connected to A6
#define IRpin A2    // IR sensor connected to A2
#define MQ9pin A7   // MQ-9 gas sensor connected to A7  

Adafruit_BMP085 bmp;  // Create BMP180 sensor object
SoftwareSerial BTSerial(10, 11); // Define Bluetooth communication pins (RX = 10, TX = 11)

int LDRValue = 0;  // Variable to store LDR sensor value
int IRValue = 0;   // Variable to store IR sensor value
int MQ9Value = 0;  // Variable to store MQ-9 sensor value  

void setup()
{
  Serial.begin(9600);  // Start serial communication for debugging at 9600 baud rate
  BTSerial.begin(9600); // Start Bluetooth module communication at 9600 baud rate
  Wire.begin();  // Initialize I2C communication for BMP180 sensor

  // Check if BMP180 sensor is connected properly
  if (!bmp.begin()) {  
    Serial.println("Could not find BMP180 sensor!"); // Print error message if not found
    while (1); // Halt the program indefinitely
  }
}

void loop()
{
  // Read analog values from sensors
  LDRValue = analogRead(LDRpin);  // Read light intensity from LDR sensor
  IRValue = analogRead(IRpin);  // Read IR sensor value
  MQ9Value = analogRead(MQ9pin);  // Read gas concentration from MQ-9 sensor
  
  // Read temperature, pressure, and altitude from BMP180 sensor
  float temperature = bmp.readTemperature();  // Get temperature in °C
  float pressure = bmp.readPressure() / 100.0F; // Get pressure in hPa (hectopascals)

  // Create a formatted data string with sensor readings
  String data = "LDR: " + String(LDRValue) + 
                ", IR: " + String(IRValue) + 
                ", MQ-9: " + String(MQ9Value) + 
                ", Temp: " + String(temperature) + "C" +
                ", Pressure: " + String(pressure) + "hPa" +

  // Print sensor data to Serial Monitor (for debugging)
  Serial.println(data);

  // Send the same sensor data to the Bluetooth module
  BTSerial.println(data);

  // Print a separator line for better readability in Serial Monitor
  Serial.println("-------------------");

  delay(1000); // Wait 1 second before taking new readings
}
