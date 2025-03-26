#include <WiFi.h>

#include <HTTPClient.h>

#include <ArduinoJson.h>

#include <TFT_eSPI.h>  // For LILYGO T-Display



// WiFi Credentials

const char* ssid = "Your_SSID";

const char* password = "Your_PASSWORD";



// API Endpoint (CoinGecko BTC Price)

const char* api_url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";



// TFT Display

TFT_eSPI tft = TFT_eSPI(); 



void setup() {

    Serial.begin(115200);

    WiFi.begin(ssid, password);

    

    // Connect to WiFi

    while (WiFi.status() != WL_CONNECTED) {

        delay(500);

        Serial.print(".");

    }

    Serial.println("\nConnected to WiFi!");



    // Initialize Display

    tft.init();

    tft.setRotation(1);

    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setTextSize(2);

}



void loop() {

    if (WiFi.status() == WL_CONNECTED) {

        HTTPClient http;

        http.begin(api_url);

        int httpResponseCode = http.GET();



        if (httpResponseCode == 200) {

            String payload = http.getString();

            Serial.println(payload);



            // Parse JSON

            DynamicJsonDocument doc(1024);

            deserializeJson(doc, payload);

            float btcPrice = doc["bitcoin"]["usd"];



            // Display Data

            tft.fillScreen(TFT_BLACK);

            tft.setCursor(10, 20);

            tft.print("BTC Price: $");

            tft.print(btcPrice);

        } else {

            Serial.println("Error fetching data");

        }



        http.end();

    }
    delay(5000); // Refresh every 5 seconds

}
