#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>

// Constants
#define DHTPIN 2           // DHT11 Data pin connected to digital pin 2
#define DHTTYPE DHT11      // DHT11 sensor for humidity only

DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);  // Initialize BMP180

void setup() {
  Serial.begin(9600);
  dht.begin(); // Start DHT sensor for humidity
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1);
  } else {
    Serial.println("BMP180 sensor initialized.");
  }
}

void loop() {
  // Read humidity from DHT11
  float humidity = dht.readHumidity();
  
  // Check if humidity read failed
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity from DHT11 sensor!");
    return;
  }

  // Read 
  //pressure from BMP180
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    float pressure = event.pressure;      // Get pressure from BMP180
    
    // Display values on the Serial Monitor
    Serial.print("DHT11 - Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    
    float temperature = dht.readTemperature();

    Serial.print("Temperature from DHT11: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print(" Pressure from BMP: ");
    Serial.print(pressure);
    Serial.println(" mb");

  

  } else {
    Serial.println("Sensor error!");
  }

  delay(2000);  // Wait for 2 seconds before the next reading
}