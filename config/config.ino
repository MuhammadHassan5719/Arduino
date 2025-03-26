
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512  // Allocate 512 bytes for storage

0WebServer server(80);


void setup() {
    Serial.begin(115200);
    EEPROM.begin(EEPROM_SIZE);  // Initialize EEPROM before reading

    WiFi.mode(WIFI_AP);
    WiFi.softAP("Zainergy", "12345678");  // Creates an Access Point

    Serial.println(" Stored Data on Boot:");
    readFromEEPROM(); // Read stored data correctly

    // Handle GET request on "/setting"
    server.on("/setting", HTTP_GET, []() {
        Serial.println(" Request Received from MIT App!");

        if (server.hasArg("ssid") && server.hasArg("pass") && server.hasArg("register") && server.hasArg("addresses")) {
            String ssid = server.arg("ssid");
            String pass = server.arg("pass");
            String reg = server.arg("register");
            String addr = server.arg("addresses");

            Serial.println(" Received Data:");
            Serial.println("SSID: " + ssid);
            Serial.println("PASS: " + pass);
            Serial.println("REGISTER: " + reg);
            Serial.println("ADDRESSES: " + addr);

            // Store in EEPROM
            saveToEEPROM(ssid, pass, reg, addr);

            server.send(200, "text/plain", "Credentials Updated");
        } else {
            Serial.println(" ERROR: Missing parameters!");
            server.send(400, "text/plain", " Missing parameters");
        }
    });

    server.begin();
}

void loop() {
    server.handleClient();
}

// Function to store data in EEPROM
void saveToEEPROM(String ssid, String pass, String reg, String addr) {
    Serial.println(" Saving Data to EEPROM...");

    EEPROM.begin(EEPROM_SIZE);

    writeToEEPROM(0, ssid);
    writeToEEPROM(50, pass);
    writeToEEPROM(100, reg);
    writeToEEPROM(150, addr);

    EEPROM.commit(); // Ensure data is saved

    Serial.println(" EEPROM Save Complete!");
}

// Function to write a string to EEPROM
void writeToEEPROM(int startAddr, String data) {
    for (int i = 0; i < data.length(); i++) {
        EEPROM.write(startAddr + i, data[i]);
    }
    EEPROM.write(startAddr + data.length(), '\0');  // Null terminator
    EEPROM.commit();  // Commit changes
}

// Function to read stored data from EEPROM
void readFromEEPROM() {
    EEPROM.begin(EEPROM_SIZE);
    
    String ssid = readStringFromEEPROM(0, 50);
    String pass = readStringFromEEPROM(50, 50);
    String reg = readStringFromEEPROM(100, 50);
    String addr = readStringFromEEPROM(150, 50);

    Serial.println(" Stored Data:");
    Serial.println("SSID: " + ssid);
    Serial.println("PASS: " + pass);
    Serial.println("REGISTER: " + reg);
    Serial.println("ADDRESSES: " + addr);
}

// Helper function to read a string from EEPROM
String readStringFromEEPROM(int startAddr, int maxLen) {
    String data = "";
    for (int i = startAddr; i < startAddr + maxLen; i++) {
        char c = EEPROM.read(i);
        if (c == '\0') break;
        data += c;
    }
    return data;
}

//1. If cannot connect to any wifi show "Not Connected To Wifi!"  
//
  
//
//3. **Device Display & Connection**:  
//   - After turning on, some information will be displayed.  
//   - The app will show the **MAC address** and **three buttons**.  
//   - The device will switch to **station mode** (acts as a **router**).  
//   - The device's signal will appear on the **mobile screen**.  
//   - Connect to this signal to access the **configurator**.  
//
//4. **Connecting to the Internet**:  
//   - The screen will prompt you to connect the device to **WiFi**.  
//   - The device provides an internet signal named **"Janergy"**.  
//   - The WiFi **password** is also **"Janergy"**.  
//   - A list of available WiFi networks will be displayed.  
//   - Select a WiFi network, enter its **password**, and connect.  
//   - Once credentials are entered, the device will **connect to the internet**.
