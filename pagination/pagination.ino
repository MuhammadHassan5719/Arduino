#include <M5StickC.h>  
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <map>

std::map<String, int> eepromMap = {
  {"ssid", 0},
  {"pass", 100},
  {"brand", 200},
  {"deviceId", 300},
  {"publicCert", 400},
  {"slaveId", 500},
  {"rootCert", 600},
  {"accountId", 700},
  {"privateCert", 800}
};

#define EEPROM_SIZE 1024 
#define BUTTON_PIN 37    

WebServer server(80);

void setup() {
    M5.begin();  
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setRotation(1); 
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.println("Try to Connect App Configurator");
    delay(5000);  

    EEPROM.begin(EEPROM_SIZE);
    pinMode(BUTTON_PIN, INPUT);

    if (digitalRead(BUTTON_PIN) == LOW) {  
        Serial.println("Button Pressed! Switching to STA Mode...");
        
     // Clear EEPROM to remove old credentials
        clearStoredCredentials();

        M5.Lcd.fillScreen(RED);
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.println("STA Mode Activated!");

        WiFi.mode(WIFI_AP);
        WiFi.softAP("Zainergy", "12345678");
        Serial.println("Station Point Started");

        // Handle credential saving
        // ssid & pass
        server.on("/setting", HTTP_GET, []() {
            Serial.println("Request Received from App!");

            if (server.hasArg("ssid") && server.hasArg("pass") ) {
                String ssid = server.arg("ssid");
                String pass = server.arg("pass");
                
                

                Serial.println("Received Data:");
                Serial.println("SSID: " + ssid);
                Serial.println("PASS: " + pass);
                
                

                writeStringToEEPROM(eepromMap["ssid"], ssid);
                writeStringToEEPROM(eepromMap["pass"], pass);
                server.send(200, "text/plain", " WiFi Credentials Saved!");
                delay(2000); 
                  ESP.restart(); 
            } else {
                Serial.println("Missing parameters!");
                server.send(400, "text/plain", " Missing parameters");
            }
        });

        // Handle WiFi network scanning
        server.on("/networks", HTTP_GET, []() {
            String networkList = scanWiFiNetworks();
            server.send(200, "text/plain", networkList);
        });

        // handle brand and device credentials
server.on("/energy", HTTP_GET, []() {
  const char* keys[] = {"brand", "deviceId", "publicCert", "slaveId", "rootCert", "accountId", "privateCert"};
  bool missing = false;

  Serial.println("Received /brand request");

  for (auto key : keys) {
    if (!server.hasArg(key)) {
      Serial.println("❌ Missing parameter: " + String(key));
      missing = true;
    } else {
      Serial.println(String(key) + " = " + server.arg(key));
    }
  }

  if (!missing) {
    for (auto key : keys) {
      saveToEEPROMByKey(key, server.arg(key));
    }
    server.send(200, "text/plain", " Brand & Certs Saved!");
  } else {
    server.send(400, "text/plain", " Missing one or more brand-related parameters");
  }
});

        server.begin();
        while (true) {
            server.handleClient();
        }
    }

    // Normal mode
    Serial.println("Loading stored WiFi Credentials...");
    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.println("Connecting to WiFi...");
    connectToWiFi();
}

void loop() {
    server.handleClient();
}

// Function to scan and return available WiFi networks
String scanWiFiNetworks() {
    Serial.println("Scanning for WiFi networks...");
    int networkCount = WiFi.scanNetworks();
    String networkList = "";

    if (networkCount == 0) {
        Serial.println("No networks found!");
        return "No Networks Found";
    } else {
        for (int i = 0; i < networkCount; i++) {
            networkList += WiFi.SSID(i) + ",";
        }
        networkList.remove(networkList.length() - 1); // Remove last comma
    }
    Serial.println("Available Networks: " + networkList);
    return networkList;
}

// Function to clear only stored credentials in EEPROM
void clearStoredCredentials() {
    Serial.println("🔁 Clearing all stored credentials using eepromMap...");

    const int sectionSize = 100; // each param block size — same as used in map

    for (const auto& pair : eepromMap) {
        String key = pair.first;
        int addr = pair.second;
        Serial.println("🧹 Clearing key: " + key + " at address: " + String(addr));

        for (int i = 0; i < sectionSize; i++) {
            EEPROM.write(addr + i, 0);
        }
    }

    EEPROM.commit();
    delay(200);
    Serial.println("✅ All EEPROM credentials cleared.");
}
// Function to save data in EEPROM


void writeStringToEEPROM(int startAddr, String data) {
  for (int i = 0; i < data.length(); i++) {
    EEPROM.write(startAddr + i, data[i]);
  }
  EEPROM.write(startAddr + data.length(), '\0');
  EEPROM.commit();
}

// Function to connect to WiFi
void connectToWiFi() {
String ssid = readStringFromEEPROM(eepromMap["ssid"], 100);
String pass = readStringFromEEPROM(eepromMap["pass"], 100);

    Serial.println("Read SSID: " + ssid);
    Serial.println("Read PASS: " + pass);

    if (ssid.length() > 0) {
        WiFi.begin(ssid.c_str(), pass.c_str());
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 10) {
            delay(1000);
            Serial.print(".");
            attempts++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\nConnected to WiFi!");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
            M5.Lcd.fillScreen(BLUE);
            M5.Lcd.setCursor(10, 20);
            M5.Lcd.println("Connected!");
        } else {
            Serial.println("\nWiFi Connection Failed!");
            M5.Lcd.fillScreen(ORANGE);
            M5.Lcd.setCursor(10, 20);
            M5.Lcd.println("WiFi Failed!");
        }
    } else {
        Serial.println("No stored WiFi credentials!");
        M5.Lcd.fillScreen(ORANGE);
        M5.Lcd.setCursor(10, 20);
        M5.Lcd.println("No WiFi Data!");
    }
}

// Function to read a string from EEPROM
String readStringFromEEPROM(int startAddr, int maxLength) {
  String data = "";
  for (int i = 0; i < maxLength; i++) {
    char c = EEPROM.read(startAddr + i);
    if (c == '\0') break;
    data += c;
  }
  return data;
}

void saveToEEPROMByKey(String key, String value) {
  if (eepromMap.count(key)) {
    writeStringToEEPROM(eepromMap[key], value);
  } else {
    Serial.println("Unknown EEPROM key: " + key);
  }
}