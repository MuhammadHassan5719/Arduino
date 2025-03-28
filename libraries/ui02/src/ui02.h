// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui02_helpers.h"
#include "ui02_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_MainPanal;
extern lv_obj_t * ui_logo;
void ui_event_ToogleButton(lv_event_t * e);
extern lv_obj_t * ui_ToogleButton;
extern lv_obj_t * ui_ToogleImage;
extern lv_obj_t * ui_charPanel;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_Image6;
extern lv_obj_t * ui_Image5;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_MainPanal1;
extern lv_obj_t * ui_logo1;
void ui_event_ToogleButton1(lv_event_t * e);
extern lv_obj_t * ui_ToogleButton1;
extern lv_obj_t * ui_ToogleImage2;
extern lv_obj_t * ui_TablePanel2;
extern lv_obj_t * ui_Image7;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_1661332484);    // assets/logo (1).png
LV_IMG_DECLARE(ui_img_87194987);    // assets/blue-arrow-png-36989.png
LV_IMG_DECLARE(ui_img_ble_rect_png);    // assets/ble_rect.png
LV_IMG_DECLARE(ui_img_greeb_tri_png);    // assets/greeb_tri.png
LV_IMG_DECLARE(ui_img_red_tri_png);    // assets/red_tri.png
LV_IMG_DECLARE(ui_img_greentable5x4_png);    // assets/greenTable5x4.png






void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
