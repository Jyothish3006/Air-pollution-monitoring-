#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Ultrasonic.h>

const char* ssid = "YourWiFiSSID";        // Your WiFi network SSID
const char* password = "YourWiFiPassword"; // Your WiFi network password

ESP8266WebServer server(80); // HTTP server

Ultrasonic ultrasonic(8,9);   // Ultrasonic sensor connected to pins 8 and 9
int bolt = 2;     // Reads the status of the pin connected to the bolt module
int enable = 3;   // Enable pin of LM293D motor driver
int in1 = 4;      // Input pin 1 and 2 of LM293D motor driver
int in2 = 5;
int buz = 6;     // Connected to the buzzer
int old_state = 0;    // Variable to hold the previous state value of the pin connected to bolt. It is initialized to 0. Change in state indicates that the garage door is opened or closed.
int new_state;        // Variable to hold the new state value
int distance;         // Holds the distance between the vehicle and the garage wall

void setup() {
  Serial.begin(9600);
  
  pinMode(bolt,INPUT);       
  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(buz, OUTPUT);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/open", handleOpen);
  server.on("/close", handleClose);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  new_state = digitalRead(bolt);
  if (new_state != old_state) {
    if (new_state == 0) {
      digitalWrite(buz,LOW);
      closeGarage();
      Serial.println("Garage Closed");
    }
    else if(new_state == 1) {
      openGarage();
      Serial.println("Garage Opened");
    }
  }
  old_state = new_state;

  if (new_state == 1) {
    distance = ultrasonic.read();
    Serial.print("Distance in CM: ");
    Serial.println(distance);
    if (distance < 30) {
      Serial.println("STOP!");   
      digitalWrite(buz,HIGH);
    }
    else {
      digitalWrite(buz,LOW);  
    }
  }
  delay(5000);
}

void handleRoot() {
  server.send(200, "text/html", "<h1>Welcome to the Smart Garage Door!</h1>");
}

void handleOpen() {
  openGarage();
  server.send(200, "text/plain", "Garage door is opening...");
}

void handleClose() {
  closeGarage();
  server.send(200, "text/plain", "Garage door is closing...");
}

void openGarage() {
  analogWrite(enable, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(4000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void closeGarage() {
  analogWrite(enable, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(4000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
