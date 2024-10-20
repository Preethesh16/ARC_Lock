#include <Arduino.h> 

const int solenoidPin = D3; 
const int buzzerPin = D4;
void unlockSolenoid();

void setup() {
  Serial.begin(9600);  // Initialize Serial for debugging
  
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
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');  // Read the entire string
    
    Serial.print("Received: ");
    Serial.println(receivedData);

    // to check karna sirf ek hi string ho aur access
    if (receivedData == "arc@123") {
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
 
  delay(5000);

  // Lock the solenoid again
  Serial.println("Locking solenoid...");
  digitalWrite(solenoidPin, LOW);  
  beep(2);
}
