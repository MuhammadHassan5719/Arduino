

#include <Arduino.h>
#include <ModbusMaster.h>

#define RXD2 26   // ESP32 UART RX
#define TXD2 0  // ESP32 UART TX
#define MODBUS_SLAVE_ID 1  // Modbus Slave ID
#define FREQUENCY_REGISTER 1066  // First register for frequency

// Relay control pins
#define RELAY_1 5
#define RELAY_2 18
#define RELAY_3 19
#define RELAY_4 21

// GND sense input pins
#define GND_1 32
#define GND_2 33
#define GND_3 25
#define GND_4 26

// Buzzer pin
#define BUZZER 27

HardwareSerial modbusSerial(2);
ModbusMaster node;

// Frequency thresholds
#define FREQ_LOW 49.800
#define FREQ_HIGH 50.100

int relayStep = 0;  // Keeps track of which relay is active
bool modbusError = false;  // Tracks if there was a Modbus read error

void preTransmission() { digitalWrite(4, HIGH); }
void postTransmission() { digitalWrite(4, LOW); }

float convertToFloat(uint16_t high, uint16_t low) {
  union {
    uint32_t i;
    float f;
  } converter;
  converter.i = ((uint32_t)high << 16) | low;
  return converter.f;
}

void setup() {
  Serial.begin(115200);
  modbusSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);  // Ensure buzzer is off initially

  // Set relay pins as output
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Set GND sense pins as input with pull-up resistors
  pinMode(GND_1, INPUT_PULLUP);
  pinMode(GND_2, INPUT_PULLUP);
  pinMode(GND_3, INPUT_PULLUP);
  pinMode(GND_4, INPUT_PULLUP);

  // Ensure all relays are OFF initially
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);

  node.begin(MODBUS_SLAVE_ID, modbusSerial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  Serial.println("⏳ Waiting 30 seconds for frequency stabilization...");
  delay(30000);  // Wait 30 seconds before starting relay operations
  Serial.println("✅ Frequency stabilization complete. Starting operations...");
}

bool isGndDetected(int pin) {
  return digitalRead(pin) == LOW;
}

void controlRelays(float frequency) {
  if (!(isGndDetected(GND_1) || isGndDetected(GND_2) || isGndDetected(GND_3) || isGndDetected(GND_4))) {
    Serial.println("⚠ No Ground Signal Detected! Turning all relays OFF.");
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, HIGH);
    relayStep = 0;
    return;
  }

  if (frequency < FREQ_LOW || frequency > FREQ_HIGH) {
    Serial.println("⚠ Frequency Out of Range! Activating Relays in Sequence...");

    switch (relayStep) {
      case 0:
        if (isGndDetected(GND_1)) {
          digitalWrite(RELAY_1, LOW);
          Serial.println("🔴 Relay 1 ON");
        }
        break;
      case 1:
        if (isGndDetected(GND_2)) {
          digitalWrite(RELAY_2, LOW);
          Serial.println("🟠 Relay 2 ON");
        }
        break;
      case 2:
        if (isGndDetected(GND_3)) {
          digitalWrite(RELAY_3, LOW);
          Serial.println("🟡 Relay 3 ON");
        }
        break;
      case 3:
        if (isGndDetected(GND_4)) {
          digitalWrite(RELAY_4, LOW);
          Serial.println("🟢 Relay 4 ON");
        }
        break;
    }

    relayStep++;
    if (relayStep > 3) relayStep = 3;

    delay(1000);
  } else {
    Serial.println("✅ Frequency Normal! Resetting Relays...");
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, HIGH);
    relayStep = 0;
  }
}

void loop() {
  uint8_t result;
  uint16_t rawDataHigh, rawDataLow;

  Serial.println("Reading Frequency (32-bit Float)...");

  result = node.readHoldingRegisters(FREQUENCY_REGISTER, 2);

  if (result == node.ku8MBSuccess) {
    rawDataHigh = node.getResponseBuffer(0);
    rawDataLow = node.getResponseBuffer(1);

    float frequency = convertToFloat(rawDataHigh, rawDataLow);

    Serial.print("Frequency: ");
    Serial.printf("%.6f Hz\n", frequency);

    if (modbusError) {
      Serial.println("✅ Modbus error resolved. Waiting 30 seconds before resuming...");
      digitalWrite(BUZZER, LOW); // Turn off buzzer when error resolves
      delay(30000);
      modbusError = false;
    }

    controlRelays(frequency);
  } else {
    Serial.println("❌ Modbus Read Error! Turning on Buzzer...");
    digitalWrite(BUZZER, HIGH); // Turn on buzzer on error
    modbusError = true;
  }

  delay(500);
}
