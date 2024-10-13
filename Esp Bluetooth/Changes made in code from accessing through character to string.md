### Original Code (Character Handling):
```
if (BTSerial.available()) {
    char receivedChar = BTSerial.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);

    if (receivedChar == '#') {
        unlockSolenoid();
    } else {
        Serial.print("Wrong character: ");
        Serial.println(receivedChar);
    }
}

```
### Modified Code (String Handling):
```
if (BTSerial.available()) {
    String receivedData = BTSerial.readString();  // Read the full string
    Serial.print("Received: ");
    Serial.println(receivedData);

    // Check if the received data is exactly one character and is '#'
    if (receivedData.length() == 1 && receivedData[0] == '#') {
        unlockSolenoid();  // Correct command received
    } else {
        Serial.print("Invalid input: ");
        Serial.println(receivedData);  // Handle incorrect input
    }
}
```

- **Original Approach:** The code handled individual characters and unlocked the solenoid only when a `#` character was received.
- **Modified Approach:** Now, the code reads the entire input as a **string**. It checks if the input is exactly one character (`#`) before unlocking the solenoid, ensuring greater stability and preventing incorrect input.

This change provides more flexibility and robust input handling, making the code suitable for more complex systems where Bluetooth commands might vary in length or content.