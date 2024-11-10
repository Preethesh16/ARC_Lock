### Overview

This project involves building an RFID-based attendance system using an ESP8266 micro controller, which records attendance data in a Firebase real-time database. The system checks RFID cards against a list of authorized IDs, and marks attendance for valid users. It also features a relay to control access (like opening a door), a buzzer for feedback, and an NTP client for accurate timestamping.

### Hardware Components

- **ESP8266 Microcontroller**: For connecting to Wi-Fi and Firebase.
- **RFID Reader (MFRC522)**: Reads RFID cards to identify users.
- **Relay Module**: Controls access, e.g., to unlock a door.
- **Buzzer**: Provides audible feedback on access status.
- **Wi-Fi Module**: ESP8266’s onboard Wi-Fi to connect to Firebase.

### Libraries Used

- **FirebaseESP8266**: For Firebase database operations and is faster than the other libraries.You can refer Test report in ARC-LOCK-DOC.
- **MFRC522**: Handles RFID reader operations.
- **NTPClient**: Manages time synchronization via NTP.

### Project Setup

1. **Wi-Fi Configuration**: Set `WIFI_SSID` and `WIFI_PASSWORD` to connect the ESP8266 to Wi-Fi.
2. **Firebase Configuration**: Set `DATABASE_URL` and `config.signer.tokens.legacy_token` for Firebase authentication.
3. **Relay and Buzzer Pins**: Define relay and buzzer pins (D2 for relay, D1 for buzzer).

### Code Functionality

- **Wi-Fi Connection**: The ESP8266 attempts to connect to Wi-Fi. If it fails after a set period (`wifiWaitTime`), it reports a connection failure.
- **Firebase Initialization**: Sets Firebase to test mode and configures database parameters.
- **RFID Detection**: When a new card is detected, its UID is read and stored in `cardID`.
- **Attendance Marking**:
    - **Valid IDs**: For specific pre-defined UIDs, access is granted, and attendance is marked.
    - **Dynamic Access Check**: For other UIDs, the system checks Firebase for access status:
        - **Access Granted**: If the card status is "granted," access is allowed, and attendance is marked.
        - **Access Denied**: If not in the database, the card status is set to "denied," and a guest entry is created in Firebase.
    - **Access Locking**: Uses the `lock` variable from Firebase to manually override and unlock the relay if set to "open."
- **Date & Time Syncing**: Uses NTP for accurate timestamping, with data converted into day-month-year format.

### Firebase Data Structure

- **Access Control**: Stored as `/access/[cardID]` with `name`, `status`, and `last_access` fields.
- **Attendance Records**: Recorded under `/attendance/[month_year]/[name]/count` to track attendance counts per user.

### Functions

- **`beep(int type)`**: Provides audible feedback; `type` 1 is a short beep sequence, and `type` 2 is a longer beep for access denial.
- **`markAttendance(String cardID)`**: Marks attendance by checking the last access date; if the date differs, it increments the attendance count in Firebase.