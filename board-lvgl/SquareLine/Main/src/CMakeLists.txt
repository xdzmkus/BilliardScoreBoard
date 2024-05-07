SET(SOURCES screens/ui_ScreenMain.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_snooker_table_480x320_png.c
    fonts/ui_font_UbuntuCyrillic25.c
    fonts/ui_font_UbuntuDigits92.c)

add_library(ui ${SOURCES})
