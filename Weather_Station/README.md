# Weather Station using Arduino

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)


This project uses **DHT11** and **BMP180** sensors to measure:
- 🌡️ Temperature
- 💧 Humidity
- 📈 Atmospheric Pressure

The data is printed on the Arduino Serial Monitor every 2 seconds.

## 🧰 Components Used
- Arduino Uno
- DHT11 Sensor
- BMP180 Sensor
- Jumper Wires
- Breadboard
- USB Cable

  ## ⚙️ Features

- 🌡️ **Real-time temperature, humidity, and pressure monitoring** using DHT11 and BMP180 sensors  
- 🔔 **Buzzer alert** when temperature exceeds a configurable threshold  
- 📲 **Bluetooth transmission** of sensor readings to a mobile app (e.g., Serial Bluetooth Terminal)  
- 🔄 **Continuous updates** every 2 seconds for responsive tracking  
- 📟 Easy to integrate with IoT dashboards or Android apps via HC-05  
- ⚡ Low-power and compact solution suitable for weather-based automation projects  

## 🛠️ Circuit Overview

### 🔹 DHT11 Sensor (Humidity & Temperature)
- **VCC** → 5V  
- **GND** → GND  
- **Data** → Digital Pin **2**

> 💡 (Optional) Add a 10kΩ pull-up resistor between Data and VCC for better stability

---

### 🔹 BMP180 Sensor (Barometric Pressure)
- **VCC** → 3.3V or 5V *(based on module specs)*  
- **GND** → GND  
- **SDA** → Analog Pin **A4** *(I2C Data Line)*  
- **SCL** → Analog Pin **A5** *(I2C Clock Line)*

> ⚠️ BMP180 communicates using the I2C protocol — no need for additional libraries beyond `Wire.h`


## 📚 Libraries Required
Make sure to install these libraries from Arduino Library Manager:
- `DHT sensor library` by Adafruit
- `Adafruit Unified Sensor`
- `Adafruit BMP085 Unified` (also works for BMP180)

## 🧾 Code Overview

```cpp
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

```

## 📌 Authors

- Pulagam Ajay Kumar Reddy(B22EC007)

  ## 📚 References

- [Arduino Tutorials](https://www.arduino.cc/en/Tutorial/HomePage)
- [DHT11 Datasheet](https://components101.com/sensors/dht11-temperature-sensor)
- [HC-05 Module Guide](https://lastminuteengineers.com/bluetooth-module-arduino-tutorial)

