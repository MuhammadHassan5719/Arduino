SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_speedbg_png.c
    images/ui_img_speedfg_png.c
    images/ui_img_speedometer_1_png.c
    fonts/ui_font_dis100.c
    fonts/ui_font_dis30.c
    fonts/ui_font_dis50.c
    fonts/ui_font_dis70.c)

add_library(ui ${SOURCES})
