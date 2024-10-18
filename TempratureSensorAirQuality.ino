// #define BLYNK_TEMPLATE_ID "TMPL3uUbOTJHl"
// #define BLYNK_TEMPLATE_NAME "Temperature and Air Quality Sensor"
// #define BLYNK_AUTH_TOKEN "oc9HihaPKr_GxcBh7LogQ4PQlaAUhAxi"
#define BLYNK_TEMPLATE_ID "BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_TOKEN"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Define your WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_SSID";  // WiFi name
char pass[] = "YOUR_SSID_PASSWORD"; // WiFi password
int relayPin = 17;
BlynkTimer timer;

#define DHTPIN 27          // Pin connected to the DHT sensor
#define DHTTYPE DHT11      // DHT sensor type (DHT11)
DHT dht(DHTPIN, DHTTYPE);

#define LED_PIN 2          // GPIO pin for the LED (Built-in LED on GPIO 2 for ESP32)
#define MQ135_PIN 34       // Pin connected to MQ135 sensor

// Threshold temperature for turning the LED on
float tempThreshold = 31.0;

int air_quality_value = 0;
int baseline_value = 0;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Send temperature and humidity to Blynk virtual pins
  Blynk.virtualWrite(V0, t);  // Temperature to virtual pin V0
  Blynk.virtualWrite(V1, h);  // Humidity to virtual pin V1

  // Print the data to the Serial Monitor
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print(" °C    Humidity : ");
  Serial.print(h);
  Serial.println(" %");

  // LED control based on temperature threshold
  if (t > tempThreshold) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED ON
    Serial.println("LED ON: Temperature is greater than 31°C");
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn LED OFF
    Serial.println("LED OFF: Temperature is less than or equal to 31°C");
    digitalWrite(relayPin, LOW);
  }

  // Air Quality Sensor Reading
  air_quality_value = analogRead(MQ135_PIN);
  
  Serial.print("MQ135 Sensor Value: ");
  Serial.println(air_quality_value);

  // Determine the air quality message based on the calibrated baseline value
  String air_quality_status;
  if (air_quality_value <= baseline_value + 350) {
    air_quality_status = "Healthy outside air level";
  } else if (air_quality_value <= baseline_value + 600) {
    air_quality_status = "Healthy indoor climate";
  } else if (air_quality_value <= baseline_value + 800) {
    air_quality_status = "Acceptable level";
  } else if (air_quality_value <= baseline_value + 1000) {
    air_quality_status = "Ventilation required";
  } else if (air_quality_value <= baseline_value + 1200) {
    air_quality_status = "Ventilation necessary";
  } else if (air_quality_value <= baseline_value + 2000) {
    air_quality_status = "Negative health effects";
  } else {
    air_quality_status = "Hazardous prolonged exposure";
  }

  // Send air quality status to Blynk
  Blynk.virtualWrite(V2, air_quality_value);  // Air quality status to virtual pin V2
  
  Serial.print("Air Quality: ");
  Serial.println(air_quality_status);
}

void setup()
{
  // Start serial communication for debugging
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  digitalWrite(relayPin, LOW); // Keep relay OFF initially (LED OFF)
  // Connect to Blynk and WiFi
  Blynk.begin(auth, ssid, pass);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure the LED is off initially

  // Initialize MQ135 sensor
  pinMode(MQ135_PIN, INPUT);

  // Take some initial readings in clean air for calibration
  Serial.println("Calibrating... Please ensure clean air.");
  delay(251);
  baseline_value = analogRead(MQ135_PIN);  // Read baseline value in clean air
  Serial.print("Baseline value: ");
  Serial.println(baseline_value);

  // Set the timer to read and send data every 2 seconds (2000 milliseconds)
  timer.setInterval(300L, sendSensor);  // Adjusted interval to 3 seconds for smoother operation
}

void loop()
{
  Blynk.run();   // Run Blynk
  timer.run();   // Run the timer
}
