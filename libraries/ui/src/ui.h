// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquarelineDisplay_Project

#ifndef _SQUARELINEDISPLAY_PROJECT_UI_H
#define _SQUARELINEDISPLAY_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_rootpanal;
extern lv_obj_t * ui_toppanal;
extern lv_obj_t * ui_toplabel;
extern lv_obj_t * ui_Temppanal;
extern lv_obj_t * ui_tempbg;
extern lv_obj_t * ui_tempslider;
extern lv_obj_t * ui_tempMinLabel;
extern lv_obj_t * ui_tempMaxLabel;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_tempPlacehold;
extern lv_obj_t * ui_tempreading;
extern lv_obj_t * ui_unitPlacehold;
extern lv_obj_t * ui_unitLabel;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_speedbg_png);    // assets/speedBG.png
LV_IMG_DECLARE(ui_img_speedfg_png);    // assets/speedFG.png
LV_IMG_DECLARE(ui_img_speedometer_1_png);    // assets/speedometer_1.png



LV_FONT_DECLARE(ui_font_dis100);
LV_FONT_DECLARE(ui_font_dis30);
LV_FONT_DECLARE(ui_font_dis50);
LV_FONT_DECLARE(ui_font_dis70);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif