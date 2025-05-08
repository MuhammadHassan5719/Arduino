#include <ModbusMaster.h>
#include <Arduino.h>
//#include <M5StickC.h>

#define RXD2 26
#define TXD2 0

ModbusMaster node;

int SlaveAddr = 1;
float VLRN;

void setup()
{
//  M5.begin(true, true, true);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  node.begin(SlaveAddr, Serial2);
   pinMode(5, OUTPUT);
     digitalWrite(5, 1);
//    M5.Lcd.setRotation(3);
//    M5.Lcd.setTextSize(2);
//    M5.Lcd.setTextColor(ORANGE);
//    M5.Lcd.setCursor(0, 0);
//
//    M5.Lcd.print("RS485 Demo");
//    Serial.println("RS485");
//    M5.Lcd.setTextSize(1);
//    M5.Lcd.setCursor(10, 20);
//    M5.Lcd.print("AutoSend Hello M5!");
//
//    M5.Lcd.setCursor(10, 30);
//    M5.Lcd.print("AutoPrint Receive");
//    M5.Lcd.setCursor(10, 50);
}

void loop()
{
  uint8_t result;

  Serial.print("SlaveAddr ");
  Serial.print(SlaveAddr);
  Serial.print(": ");

  node.clearResponseBuffer();
  result = node.readHoldingRegisters(1066, 2);
  
  if (result == node.ku8MBSuccess)
  {
    float val1 = node.getResponseBuffer(1);
    float val2 = node.getResponseBuffer(0);
    uint16_t RN[2] = {val1, val2};
    memcpy(&VLRN, RN, sizeof(VLRN));
    
    Serial.println("VLRN ");
    Serial.println(VLRN);
//    M5.Lcd.setTextSize(2);
//
//    M5.Lcd.println(VLRN);
  }
  else if (result == node.ku8MBResponseTimedOut)
  {
    Serial.println("Timeout");
  }
  else if (result == node.ku8MBInvalidCRC)
  {
    Serial.println("Invalid CRC");
  }
  else if (result == node.ku8MBInvalidFunction)
  {
    Serial.println("Invalid Function");
  }
  else if (result == node.ku8MBInvalidSlaveID)
  {
    Serial.println("Invalid Slave ID");
  }
  else if (result == node.ku8MBSlaveDeviceFailure)
  {
    Serial.println("Slave Device Failure");
  }
  else if (result == node.ku8MBIllegalDataValue)
  {
    Serial.println("Illegal Data Value");
  }

  delay(1000);
}
