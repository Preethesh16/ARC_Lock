#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>
SoftwareSerial espSerial(13,15);

#define LED_G D1//define green LED pin
#define LED_R D0 //define red LED
#define ACCESS_DELAY 4000
#define DENIED_DELAY 1000

//paste the hidden code id: 1
//This part of code is removed for confidential information

//paste the hidden code id: 2
//This part of code is removed for confidential information
// #define wifiName "ALIGATOR 7499"
// #define password "12341234"

bool flag=false;

WiFiClient wifiClient;
 
//access function
//1 Access granted
//2 Access denied
void access(int a){
  switch(a)
  {
    case 1: espSerial.print("@");
            delay(ACCESS_DELAY);
            espSerial.print("%");
            break;
    case 2: 
            espSerial.print("&");
            delay(DENIED_DELAY);
  }
}
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  Serial.println();
  espSerial.begin(9600);
  
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
  WiFi.begin(wifiName, password);
 while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_G, HIGH);
   delay(500);
   Serial.println("Connecting to WiFi...");
    digitalWrite(LED_G, LOW);
   delay(500);
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

    if(WiFi.status() == WL_CONNECTED){
      Serial.println("Connected to WiFi and Firebase"); 
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_R, LOW);
    }
}
void loop() 
{
  if(Firebase.getString("lock") == "open"){
    Serial.println("Someone opened door");
    access(1);
    Firebase.setString("lock","close");
  }
  while(WiFi.status() != WL_CONNECTED){
  digitalWrite(LED_R, HIGH);
    Serial.println("Wifi disconnected");
    flag=true;
   digitalWrite(LED_G, HIGH);
   delay(500);
  digitalWrite(LED_G, LOW);
  }
  if(WiFi.status() == WL_CONNECTED&&flag){
    Serial.println("Wifi connected");
    flag=false;
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
  }
  delay(500);
}
