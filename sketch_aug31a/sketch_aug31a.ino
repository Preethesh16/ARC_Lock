#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
#define SS_PIN D8
#define RST_PIN D4
#define LED_G D1//define green LED pin
#define LED_R D0 //define red LED
#define ACCESS_DELAY 5000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


//paste the hidden code id: 1
//This part of code is removed for confidential information

//paste the hidden code id: 2
//This part of code is removed for confidential information

// #define wifiName "SALT-SNAP"
// #define password "Salt@4650"
bool flag=false;

int count=0;

WiFiClient wifiClient;
 
//access function
//1 Access granted
//2 Access denied
void access(int a){
  switch(a)
  {
    case 1: Serial.println("@");
            delay(ACCESS_DELAY);
            Serial.println("%");
            break;
    case 2: 
            Serial.println("&");
            delay(DENIED_DELAY);
  }
}
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  Serial.println();
  
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
  WiFi.begin(wifiName, password);
 while (WiFi.status() != WL_CONNECTED&&count<=8) {
    digitalWrite(LED_G, HIGH);
   delay(500);
   Serial.println("Connecting to WiFi...");
    digitalWrite(LED_G, LOW);
   delay(500);
   count++;
  }
  count=0;
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
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
    //Serial.println("Someone opened door");
    access(1);
    Firebase.setString("lock","close");
  }
  if(mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial()){
   Serial.print("UID tag : ");
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     cardUID += (mfrc522.uid.uidByte[i]< 10)? "0":"";
     cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    Serial.print("Message : ");
    if (Firebase.getString("access/" + cardUID+"/status") == "granted"||cardUID=="49771005")//change here the UID of the card/cards that you want to give access
    {
      Serial.println("Authorized access");
     access(1);
    }

    else   {
      Firebase.setString("access/" + cardUID+"/status","denied");
      Serial.println("Access denied");
      access(2);
    }
    mfrc522.PICC_HaltA(); 
  }
  if(WiFi.status() != WL_CONNECTED){
  digitalWrite(LED_R, HIGH);
    Serial.println("Wifi disconnected");
    flag=true;
   digitalWrite(LED_G, HIGH);
   delay(250);
  digitalWrite(LED_G, LOW);
   delay(250);
  }
  if(WiFi.status() == WL_CONNECTED&&flag){
    Serial.println("Wifi connected");
    flag=false;
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
  }
//delay(50);
}
