#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// Define sensor pins
const int temperaturePin = A0;
const int humidityPin = A0; // Use A0 if A1 is not recognized
const int rainPin = D2;     // Example: Rain sensor connected to digital pin D2

// ThingSpeak parameters
const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";
unsigned long myChannelNumber = 123456; // Your ThingSpeak channel number
const char *myWriteAPIKey = "YourWriteAPIKey"; // Your ThingSpeak Write API Key

// Thresholds for alerts
const float temperatureThreshold = 30.0; // Temperature threshold for extreme events (e.g., in Celsius)
const float humidityThreshold = 70.0;    // Humidity threshold for extreme events (e.g., in percentage)
const int rainThreshold = 500;           // Rain threshold for extreme events (e.g., in analog value)

void setup() {
  Serial.begin(115200);
  pinMode(temperaturePin, INPUT);
  pinMode(humidityPin, INPUT);
  pinMode(rainPin, INPUT);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  // Initialize ThingSpeak
  WiFiClient client; // Declare WiFiClient object
  ThingSpeak.begin(client);
}

void loop() {
  // Read sensor values
  float temperature = analogRead(temperaturePin) * 0.09765625; // Convert analog reading to Celsius
  float humidity = analogRead(humidityPin) * 0.1906; // Convert analog reading to percentage
  int rain = digitalRead(rainPin);
  
  // Upload data to ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, rain);
  
  int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (status == 200) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.println("Failed to upload data to ThingSpeak");
  }
  
  // Check for extreme events
  if (temperature > temperatureThreshold) {
    Serial.println("Extreme temperature detected! Take necessary precautions.");
  }
  
  if (humidity > humidityThreshold) {
    Serial.println("High humidity detected! Take necessary precautions.");
  }
  
  if (rain > rainThreshold) {
    Serial.println("Heavy rainfall detected! Take necessary precautions.");
  }
  
  delay(10000); // Delay for 10 seconds before next reading
}


float readTemperature() {
  // Read temperature sensor
  // Replace this with your actual temperature sensor reading logic
  return analogRead(temperaturePin) * 0.09765625; // Convert analog reading to Celsius
}

float readHumidity() {
  // Read humidity sensor
  // Replace this with your actual humidity sensor reading logic
  return analogRead(humidityPin) * 0.1906; // Convert analog reading to percentage
}

void uploadData(float temperature, float humidity, int rain) {
  // Upload data to ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, rain);
  
  int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (status == 200) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.println("Failed to upload data to ThingSpeak");
  }
}

void checkExtremeEvents(float temperature, float humidity, int rain) {
  // Check for extreme events based on thresholds
  if (temperature > temperatureThreshold) {
    Serial.println("Extreme temperature detected! Take necessary precautions.");
    // Send alert message or trigger external alert mechanism
  }
  
  if (humidity > humidityThreshold) {
    Serial.println("High humidity detected! Take necessary precautions.");
    // Send alert message or trigger external alert mechanism
  }
  
  if (rain > rainThreshold) {
    Serial.println("Heavy rainfall detected! Take necessary precautions.");
    // Send alert message or trigger external alert mechanism
  }
}
