
#include <lvgl.h>
#include "MyDisplay.h"
#include <ModbusMaster.h>
#include <Arduino.h>

#define RXD2 21
#define TXD2 13

ModbusMaster node;

int SlaveAddr = 1;
float VLRN;


static const uint32_t screenWidth  = 320;
static const uint32_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

lv_obj_t * mainScreen;
//lv_obj_t * titleImage;
lv_obj_t * qrCode;
//LV_IMG_DECLARE(ui_logo_img_obj);

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  tft.startWrite();
  tft.setAddrWindow( area->x1, area->y1, w, h );
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready( disp );
}

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
  if (ts.touched()) {
    data->state = LV_INDEV_STATE_PR;
    TS_Point p = ts.getPoint();
    data->point.x = p.x;
    data->point.y = p.y;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  node.begin(SlaveAddr, Serial2);

  tft.begin();
  tft.setRotation(0);
  tft.setBrightness(255);

  if (!ts.begin(40, SDA_FT6236, SCL_FT6236)) {
    Serial.println("Unable to start the capacitive touch Screen.");
  }

  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);


}

void loop() {
  lv_timer_handler();
  delay( 5 );

  uint8_t result;

  Serial.print("SlaveAddr ");
  Serial.print(SlaveAddr);
  Serial.print(": ");

  node.clearResponseBuffer();
  result = node.readHoldingRegisters(1000, 20);
  
  if (result == node.ku8MBSuccess)
  {
    float val1 = node.getResponseBuffer(1);
    float val2 = node.getResponseBuffer(0);
    uint16_t RN[2] = {val1, val2};
    memcpy(&VLRN, RN, sizeof(VLRN));
    
    Serial.println("VLRN ");
    Serial.println(VLRN);

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

  ui_background();
  lv_disp_load_scr(mainScreen);
  delay(1000);
}



void ui_background() {
  mainScreen = lv_obj_create(NULL);
  lv_obj_clear_flag(mainScreen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *label = lv_label_create(mainScreen);
  lv_label_set_text(label, String(VLRN).c_str());
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);


}
