## Objective:

The purpose of the code is to control a **solenoid lock** via a Bluetooth connection using the **HC-05 Bluetooth module**. The user sends a command from a paired Bluetooth device, and if the correct command (`#`) is received, the solenoid unlocks for a few seconds and then locks again.

## Reason:
The reason for using Bluetooth for door locking system is if the wifi is disconnected it is difficult for the lock to unlock. As an alternate way to unlock, we are using Bluetooth medium.

## Components involved
- ESP8266 (ESP-12E NodeMCU 1.0) with Serial Transfer pins in use.
- **HC-05 Bluetooth module** for receiving wireless commands.
- **Solenoid lock** controlled by a digital pin (D3).

## Points to be noted

1. [[Why HC-05 Bluetooth module?]]
2. [[Changes made in code from accessing through character to string]]
3. Serial begin(9600)