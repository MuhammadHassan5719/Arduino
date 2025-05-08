/////////////////////////////////////////////////////////////////
/*
  QR Code Maker (ESP32+LVGL8)
  For More Information: https://youtu.be/Ss3zBO-V9kI
  Created by Eric N. (ThatProject)
*/
/////////////////////////////////////////////////////////////////
//WT32-SC01(ST7796 Setup)
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
//FT6236 Capacitive Touch Screen
#include <FT6236.h>
#define SDA_FT6236 6
#define SCL_FT6236 5

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7796     _panel_instance;
    lgfx::Bus_Parallel8 _bus_instance;
    lgfx::Light_PWM     _light_instance;

  public:
    LGFX(void)
    {
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

      setPanel(&_panel_instance);
    }
};

static LGFX tft;
FT6236 ts = FT6236();
