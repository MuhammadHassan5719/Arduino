#include <ModbusMaster.h>
#include<Arduino.h>
#include<ArduinoJson.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>


#define TFT_GREY 0x5AEB

ModbusMaster node;

int counter = 0;

#define RXD2 15
#define TXD2 16


int SlaveAddr = 1 ;
int id;
float VLRN, VLYN, VLBN, VLPN, VLRY, VLYB, VLBR, VLPP, CR, CY, CB, ACP, PFR, PFY, PFBP, APF, FQ, TKVA, TKW, TKVAr, IKWh, EKWh, TKWh, IKVArh, EKVArh, TKVArh, TKVAh, RH, KWR, KWY, KWB, VLTHDFLR, VLTHDFLY, VLTHDFLB, CTHDFLR, CTHDFLY, CTHDFLB;
float vl_rn, vl_yn, vl_bn, avg_vl_pn , vl_ry, vl_yb, vl_br, curr_r, curr_y, curr_b, avg_curr_3p, avg_pf_3p, frequency, total_va, w_r, w_y, w_b, total_w, total_var, total_wh, vl_thdf_lr, vl_thdf_ly, vl_thdf_lb, curr_thdf_lr, curr_thdf_ly, curr_thdf_lb;
float  MXCR, MXCY, MXCB, MXW, KWhR, KWhY, KWhY1 , KWhB;
float  max_curr_r, max_curr_y, max_curr_b, max_w, wh_r, wh_y, wh_b;
float  VLRN1 , VLRN2, VLRN3, VLRN4, VLRN5;

float modbus_volt = 0;
int status_volt ;
uint32_t i = 0, a = 0;


float Hextofloat(uint32_t x)
{
  return {*(float*)&x};
}

uint32_t FloattoHex(float x)
{
  return {*(uint32_t*)&x};
}


int64_t UinttoInt (uint64_t x)
{
  return (* (int64_t *) & x);
}

double HextoDouble (uint32_t x)

{
  return (* (double *) & x);
}

float DHextofloat (uint64_t x)

{
  return (* (float *) & x);
}

uint64_t HextoDHex (uint32_t x)

{
  return (* (uint64_t *) & x);
}

int64_t HexToint(uint32_t x)
{
  return (*(int32_t*)&x);
}


void setup()
{
  Serial.begin(9600);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  node.begin(SlaveAddr, Serial2);

}

void loop()
{

  uint8_t j;
  uint16_t data[4];
  uint32_t value = 0;
  uint8_t  result, resulta, resultb, resultc, resultd  ;

 // node.slaveid(SlaveAddr); delay(5);
  node.begin(SlaveAddr, Serial2); delay(1000);

  Serial.print("SlaveAddr "); Serial.print( SlaveAddr); Serial.print(": "); delay(1000);


  Serial.println("1st Loop");
  node.clearResponseBuffer();
  result = node.readHoldingRegisters(1000, 20); //4096
  if (result == node.ku8MBSuccess)
  {


    float  val1 = node.getResponseBuffer(1);
    float  val2 = node.getResponseBuffer(0);
    uint16_t RN[2] = {val1, val2};
    memcpy(&VLRN, RN, 6);
    Serial.println("VLRN ");
    Serial.println(VLRN  );
    delay(1000);
    
  }//result
  if (result == node.ku8MBResponseTimedOut)
  {
    Serial.println("Inside Timeout block ");
  }

  if (result == node.ku8MBInvalidCRC)
  {
    Serial.println("Inside ku8MBInvalidCRC block ");
  }

  if (result == node.ku8MBInvalidFunction)
  {
    Serial.println("Inside ku8MBInvalidFunction block ");
  }

  if (result == node.ku8MBInvalidSlaveID)
  {
    Serial.println("Inside ku8MBInvalidFunction block ");
  }

  if (result == node.ku8MBSlaveDeviceFailure)
  {
    Serial.println("Inside ku8MBSlaveDeviceFailure block ");
  }

  if (result == node.ku8MBIllegalDataValue)
  {
    Serial.println("Inside ku8MBIllegalDataValue block ");
  }
  delay(1000);
}//loop
