#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>
#include <Servo.h>

Servo servo_test;
int gas = A0; 
int co = 17; // Example: Carbon Monoxide sensor connected to GPIO pin 17
int no2 = 18; // Example: Nitrogen Dioxide sensor connected to GPIO pin 18
const char* ssid = "Bablu";//your hotspot ID  
const char* password = "123451234";//your password
WiFiClient client;  
unsigned long myChannelNumber = 2535162;//your ThingSpeak channel ID 
const char * myWriteAPIKey = "3CPQCIOEV53ALC7L";// API Key

void setup()  
{
  pinMode(D0, OUTPUT); 
  pinMode(D1, OUTPUT); 
  pinMode(gas, INPUT);  
  pinMode(co, INPUT); // Set CO sensor pin as input
  pinMode(no2, INPUT); // Set NO2 sensor pin as input
  servo_test.attach(D2);
  Serial.begin(115200);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
    delay(500);  
    Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);
}  

void loop()   
{  
  static boolean data_state = true;  
  int gasValue = analogRead(gas);
  float gasConcentration = gasValue * (5.0 / 1023.0);

  int coValue = analogRead(co);
  float coConcentration = coValue * (5.0 / 1023.0);

  int no2Value = analogRead(no2);
  float no2Concentration = no2Value * (5.0 / 1023.0);

  if (gasConcentration > 1 || coConcentration > 1 || no2Concentration > 1)
  {
    ThingSpeak.writeField(myChannelNumber, 1, gasConcentration, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 2, coConcentration, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 3, no2Concentration, myWriteAPIKey);
    Serial.println("Data uploaded");
    digitalWrite(D1, LOW);
    digitalWrite(D0, HIGH);
    for (int angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
    {                                  
      servo_test.write(angle);                 //command to rotate the servo to the specified angle
      delay(15);                       
    }  
  }
  else
  {
    digitalWrite(D0, LOW);
    digitalWrite(D1, HIGH);
    ThingSpeak.writeField(myChannelNumber, 1, gasConcentration, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 2, coConcentration, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 3, no2Concentration, myWriteAPIKey);
    Serial.println("Data uploaded");
  }
  Serial.print("Gas Concentration: ");
  Serial.println(gasConcentration);
  Serial.print("CO Concentration: ");
  Serial.println(coConcentration);
  Serial.print("NO2 Concentration: ");
  Serial.println(no2Concentration);
  delay(1000);

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to fields 1, 2, and 3 for gas, CO, and NO2 respectively.
  delay(1000); // ThingSpeak will only accept updates every 1 second.  
}
