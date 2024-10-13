#include <SoftwareSerial.h>
#include <Arduino.h>

SoftwareSerial BTSerial(D1, D2); 

const int solenoidPin = D3; 
const int buzzerPin = D1;
void unlockSolenoid();

void setup() {
  Serial.begin(115200);  // Initialize Serial for debugging
  BTSerial.begin(9600);  // HC-05 works at 9600 baudrate
  
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW);  //start mein lock rakhne kilye
  
  Serial.println("Bluetooth Serial started, waiting for commands...");
}
void beep(int type)
{
  if (type == 1)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(250);
    digitalWrite(buzzerPin, LOW);
    delay(250);
    digitalWrite(buzzerPin, HIGH);
    delay(250);
    digitalWrite(buzzerPin, LOW);
    delay(250);
  }
  else if (type == 2)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }
}
void loop() {
  if (BTSerial.available()) {
    String receivedData = BTSerial.readString();  // Read the entire string
    
    Serial.print("Received: ");
    Serial.println(receivedData);

    // to check karna sirf ek hi string ho aur access
    if (receivedData.length() == 1 && receivedData[0] == '#') {
      unlockSolenoid();
    } else {
      Serial.print("Invalid input: ");
      Serial.println(receivedData);
    }
  }

  delay(20);
}

void unlockSolenoid() {
  Serial.println("Unlocking solenoid...");
  digitalWrite(solenoidPin, HIGH);  // open
  beep(1);
 
  delay(3000);

  // Lock the solenoid again
  Serial.println("Locking solenoid...");
  digitalWrite(solenoidPin, LOW);  
  beep(2);
}
