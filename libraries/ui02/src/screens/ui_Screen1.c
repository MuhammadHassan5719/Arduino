// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui02.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_MainPanal = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_MainPanal, 320);
    lv_obj_set_height(ui_MainPanal, 480);
    lv_obj_set_align(ui_MainPanal, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MainPanal, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MainPanal, lv_color_hex(0x4EF4E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MainPanal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MainPanal, lv_color_hex(0x024F49), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MainPanal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MainPanal, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_logo = lv_img_create(ui_MainPanal);
    lv_img_set_src(ui_logo, &ui_img_1661332484);
    lv_obj_set_width(ui_logo, LV_SIZE_CONTENT);   /// 369
    lv_obj_set_height(ui_logo, LV_SIZE_CONTENT);    /// 120
    lv_obj_set_x(ui_logo, -55);
    lv_obj_set_y(ui_logo, -190);
    lv_obj_set_align(ui_logo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_logo, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_logo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_logo, 125);

    ui_ToogleButton = lv_btn_create(ui_MainPanal);
    lv_obj_set_width(ui_ToogleButton, 100);
    lv_obj_set_height(ui_ToogleButton, 50);
    lv_obj_set_x(ui_ToogleButton, 80);
    lv_obj_set_y(ui_ToogleButton, 190);
    lv_obj_set_align(ui_ToogleButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ToogleButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ToogleButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ToogleButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ToogleButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ToogleImage = lv_img_create(ui_ToogleButton);
    lv_img_set_src(ui_ToogleImage, &ui_img_87194987);
    lv_obj_set_width(ui_ToogleImage, LV_SIZE_CONTENT);   /// 512
    lv_obj_set_height(ui_ToogleImage, LV_SIZE_CONTENT);    /// 512
    lv_obj_set_align(ui_ToogleImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ToogleImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ToogleImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_ToogleImage, 50);

    ui_charPanel = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_charPanel, 300);
    lv_obj_set_height(ui_charPanel, 310);
    lv_obj_set_align(ui_charPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_charPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_charPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_charPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_charPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_charPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image4 = lv_img_create(ui_charPanel);
    lv_img_set_src(ui_Image4, &ui_img_ble_rect_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Image4, 0);
    lv_obj_set_y(ui_Image4, -1);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Image4, 450);

    ui_Image1 = lv_img_create(ui_charPanel);
    lv_img_set_src(ui_Image1, &ui_img_greeb_tri_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Image1, -99);
    lv_obj_set_y(ui_Image1, 0);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Image1, -900);

    ui_Image2 = lv_img_create(ui_charPanel);
    lv_img_set_src(ui_Image2, &ui_img_red_tri_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Image2, 100);
    lv_obj_set_y(ui_Image2, 0);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Image2, 900);

    ui_Image6 = lv_img_create(ui_charPanel);
    lv_img_set_src(ui_Image6, &ui_img_red_tri_png);
    lv_obj_set_width(ui_Image6, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Image6, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Image6, 0);
    lv_obj_set_y(ui_Image6, 100);
    lv_obj_set_align(ui_Image6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Image6, 1800);

    ui_Image5 = lv_img_create(ui_charPanel);
    lv_img_set_src(ui_Image5, &ui_img_greeb_tri_png);
    lv_obj_set_width(ui_Image5, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Image5, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Image5, 0);
    lv_obj_set_y(ui_Image5, -100);
    lv_obj_set_align(ui_Image5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_ToogleButton, ui_event_ToogleButton, LV_EVENT_ALL, NULL);

}
