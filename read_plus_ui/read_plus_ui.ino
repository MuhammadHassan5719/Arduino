
#include <ModbusMaster.h>
#include <Arduino.h>

#define RXD2 1
#define TXD2 42
#define RTS_PIN 2

ModbusMaster node;

int SlaveAddr = 1;
float VLRN;

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
// LVGL
// https://github.com/lvgl/lvgl
#include <lvgl.h>
#include "ui.h"




/*----------------------------lCD CONFIG PART--------------------------*/
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7796 _panel_instance;
  lgfx::Bus_Parallel8 _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_FT5x06 _touch_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.freq_write = 40000000;
      cfg.pin_wr = 47;
      cfg.pin_rd = -1;
      cfg.pin_rs = 0;
      cfg.pin_d0 = 9;
      cfg.pin_d1 = 46;
      cfg.pin_d2 = 3;
      cfg.pin_d3 = 8;
      cfg.pin_d4 = 18;
      cfg.pin_d5 = 17;
      cfg.pin_d6 = 16;
      cfg.pin_d7 = 15;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs = -1;
      cfg.pin_rst = 4;
      cfg.pin_busy = -1;
      cfg.memory_width = 320;
      cfg.memory_height = 480;
      cfg.panel_width = 320;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = 45;
      cfg.invert = false;
      cfg.freq = 44100;
      cfg.pwm_channel = 7;

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }

    {
      auto cfg = _touch_instance.config();
      cfg.i2c_port = 1;
      cfg.i2c_addr = 0x38;
      cfg.pin_sda = 6;
      cfg.pin_scl = 5;
      cfg.freq = 400000;
      cfg.x_min = 0;
      cfg.x_max = 320;
      cfg.y_min = 0;
      cfg.y_max = 480;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};

static LGFX tft;

/*Change to your screen resolution*/
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {

  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;

  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}
/*--------------------------------------LCD CONFIG PARD ENG-----------------------*/
void setup() {
  
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(RTS_PIN, OUTPUT);
  digitalWrite(RTS_PIN, LOW); 
  node.begin(SlaveAddr, Serial2);
  
  initDisplay();
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_init();
  ui_reset();
}

void loop() {
  lv_timer_handler();
  delay(1);


  uint8_t result;

  Serial.print("SlaveAddr ");
  Serial.print(SlaveAddr);
  Serial.print(": ");

  digitalWrite(RTS_PIN, HIGH); // Enable Transmit Mode
  delay(10);

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

  Serial2.flush();
  delay(2); // Small delay to ensure data is sent
  digitalWrite(RTS_PIN, LOW);
  


  ui_background();
  delay(1000);
  
}

void ui_reset() {
  lv_slider_set_value(ui_tempslider, 0, LV_ANIM_OFF);
  lv_obj_clear_flag(ui_tempslider, LV_OBJ_FLAG_CLICKABLE);
  lv_label_set_text(ui_tempMinLabel," 0");
  lv_label_set_text(ui_tempMaxLabel,"250");
  lv_label_set_text(ui_tempreading,"000");
  

}

void initDisplay() {
  tft.begin();
  tft.setRotation(2);
  tft.setBrightness(255);
  tft.fillScreen(TFT_BLACK);
}

void ui_background() {
 lv_label_set_text(ui_tempreading, String(VLRN,0).c_str());
 lv_slider_set_value(ui_tempslider, int(VLRN), LV_ANIM_ON);

}
