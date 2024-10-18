# EnviroSync
## Overview
**EnviroSync** is a real-time environmental monitoring system designed to measure temperature, humidity, and air quality using an ESP32 microcontroller, DHT11 sensor, MQ135 air quality sensor, and Blynk cloud platform. The system also simulates an air conditioner (AC) using an LED bulb, which turns on or off based on temperature thresholds.

This project is ideal for smart home applications, environmental monitoring, or educational demonstrations where students can learn about IoT, sensor networks, and automated control systems.

## Features
- **Real-time Monitoring**: Continuously tracks temperature, humidity, and air quality.
- **Automated AC Control**: Turns on a dummy AC (LED bulb) when the temperature exceeds 31°C and turns it off when the temperature drops below.
- **Cloud-based Visualization**: Uses Blynk to display data in a user-friendly interface accessible via mobile or web apps.
- **Air Quality Assessment**: Provides detailed information on air quality levels (e.g., healthy, ventilation needed, hazardous).
  
## Components
- **ESP32**: Microcontroller with built-in Wi-Fi used for sensor data collection and transmission.
- **DHT11**: Sensor for temperature and humidity measurement.
- **MQ135**: Air quality sensor for detecting gas concentrations and estimating air quality.
- **Relay Module**: Controls the state of the dummy AC (LED bulb).
- **LED Bulb**: Simulates an air conditioner that turns on or off based on temperature.
- **Blynk Cloud**: Displays the sensor data in real-time for remote monitoring.

## Working Principle
1. **Temperature & Humidity Monitoring**:
   - The DHT11 sensor collects temperature and humidity data, which is sent to the Blynk Cloud for visualization.
   - If the temperature exceeds 31°C, the system turns on the dummy AC (represented by an LED bulb).
   
2. **Air Quality Monitoring**:
   - The MQ135 sensor measures air quality and compares it against a calibrated baseline value to provide feedback on air quality levels.
   
3. **AC Control**:
   - The system uses a relay module to control the state of the LED bulb (dummy AC) based on temperature readings.

## User Interface
The Blynk Cloud interface provides real-time data on:
- **V0**: Temperature
- **V1**: Humidity
- **V2**: Air Quality

You can monitor these values remotely via the Blynk mobile app or web dashboard.

## Setup and Installation

1. **Hardware Connections**:
   - Connect the DHT11 sensor to GPIO 27 on the ESP32.
   - Connect the MQ135 sensor to GPIO 34 on the ESP32.
   - Connect the relay module and LED bulb to GPIO 17 on the ESP32 for controlling the dummy AC.
   - Power the ESP32 through USB.

2. **Software Configuration**:
   - Clone the repository and open the project in the Arduino IDE.
   - Install the necessary libraries:
     - Blynk library
     - DHT sensor library
   - Define your Blynk credentials and WiFi SSID/password in the code:
     ```cpp
     #define BLYNK_AUTH_TOKEN "YourAuthToken"
     char ssid[] = "YourWiFiName";
     char pass[] = "YourWiFiPassword";
     ```
   - Upload the code to your ESP32.

3. **Blynk Setup**:
   - Create a new project on the Blynk app.
   - Add three virtual pins:
     - **V0** for temperature.
     - **V1** for humidity.
     - **V2** for air quality.
   - Obtain the Blynk authentication token and insert it into the code.

4. **Run the Project**:
   - After uploading the code, the ESP32 will connect to the WiFi network and start sending data to Blynk.
   - Open the Blynk app to monitor real-time data on temperature, humidity, and air quality.

## Calibration of Air Quality Sensor
- The MQ135 sensor is calibrated during setup by measuring the air quality in a clean air environment. The baseline value obtained during calibration is used to determine the air quality status.

## Air Quality Levels
- **Healthy outdoor air**
- **Healthy indoor air**
- **Acceptable level**
- **Ventilation required**
- **Negative health effects**
- **Hazardous prolonged exposure**

## Future Enhancements
- **Improved Sensor Accuracy**: Upgrade to more accurate sensors like DHT22 and a professional-grade air quality sensor.
- **Remote AC Control**: Extend Blynk to allow remote control of the dummy AC from the dashboard.
- **Data Logging**: Implement data logging for historical environmental trends.
- **Push Notifications**: Add alerts for critical thresholds (e.g., high temperature or poor air quality).

## License
This project is open-source and licensed under the MIT License. Feel free to modify and distribute as needed.

---

Enjoy using EnviroSync! If you have any questions or improvements, feel free to contribute or open an issue on GitHub.
