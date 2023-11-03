#ifndef _GUI_SNOOKER_H
#define _GUI_SNOOKER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
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

// Balls part

extern lv_obj_t* ui_BPanelBalls;
extern lv_obj_t* ui_BButtonRed;
extern lv_obj_t* ui_BLabel1;
extern lv_obj_t* ui_BButtonBlack;
extern lv_obj_t* ui_BLabel7;
extern lv_obj_t* ui_BButtonPink;
extern lv_obj_t* ui_BLabel6;
extern lv_obj_t* ui_BButtonBlue;
extern lv_obj_t* ui_BLabel5;
extern lv_obj_t* ui_BButtonBrown;
extern lv_obj_t* ui_BLabel4;
extern lv_obj_t* ui_BButtonGreen;
extern lv_obj_t* ui_BLabel3;
extern lv_obj_t* ui_BButtonYellow;
extern lv_obj_t* ui_BLabel2;
extern lv_obj_t* ui_BButtonMiss;
extern lv_obj_t* ui_BLabel0;
extern lv_obj_t* ui_BButtonFoul;
extern lv_obj_t* ui_BLabelFoul;
extern lv_obj_t* ui_BButtonFreeBall;
extern lv_obj_t* ui_BLabelFreeBall;
extern lv_obj_t* ui_BButtonCancel;
extern lv_obj_t* ui_BLabelCancel;
extern lv_obj_t* ui_BPanelFree;
extern lv_obj_t* ui_BButtonRedF;
extern lv_obj_t* ui_BLabelFB1;
extern lv_obj_t* ui_BButtonYellowF;
extern lv_obj_t* ui_BLabelFB2;
extern lv_obj_t* ui_BButtonGreenF;
extern lv_obj_t* ui_BLabelFB3;
extern lv_obj_t* ui_BButtonBrownF;
extern lv_obj_t* ui_BLabelFB4;
extern lv_obj_t* ui_BButtonBlueF;
extern lv_obj_t* ui_BLabelFB5;
extern lv_obj_t* ui_BButtonPinkF;
extern lv_obj_t* ui_BLabelFB6;
extern lv_obj_t* ui_BPanelFoul;
extern lv_obj_t* ui_BButtonF4;
extern lv_obj_t* ui_BLabelF4;
extern lv_obj_t* ui_BButtonF5;
extern lv_obj_t* ui_BLabelF5;
extern lv_obj_t* ui_BButtonF6;
extern lv_obj_t* ui_BLabelF6;
extern lv_obj_t* ui_BButtonF7;
extern lv_obj_t* ui_BLabelF7;
extern lv_obj_t* ui_BButtonF1;
extern lv_obj_t* ui_BLabelF1;

extern lv_obj_t* ui_MBPanelSnookerYellow;
extern lv_obj_t* ui_MBLabelSnookerYellowQ;
extern lv_obj_t* ui_MBBtnSnookerYellowYes;
extern lv_obj_t* ui_MBLabelSnookerYellowYes;
extern lv_obj_t* ui_MBBtnSnookerYellowNo;
extern lv_obj_t* ui_MBLabelSnookerYellowNo;

// Snooker part

extern lv_obj_t* ui_ScreenSnooker;
extern lv_obj_t* ui_NLabelHome;
extern lv_obj_t* ui_NLabelRefresh;
extern lv_obj_t* ui_NRestYellow;
extern lv_obj_t* ui_NRestGreen;
extern lv_obj_t* ui_NRestBrown;
extern lv_obj_t* ui_NRestBlue;
extern lv_obj_t* ui_NRestPink;
extern lv_obj_t* ui_NRestBlack;
extern lv_obj_t* ui_NRestRed;
extern lv_obj_t* ui_NLabelRestRed;
extern lv_obj_t* ui_NLabelRestScore;
extern lv_obj_t* ui_NPanelPly1;
extern lv_obj_t* ui_NPlyLabelName1;
extern lv_obj_t* ui_NPlyLabelScore1;
extern lv_obj_t* ui_NPlyLabelMaxScore1;
extern lv_obj_t* ui_NPlyLabelDiff1;
extern lv_obj_t* ui_NPanelPlyBreak;
extern lv_obj_t* ui_NLabelPlyBreak;
extern lv_obj_t* ui_NPanelPly2;
extern lv_obj_t* ui_NPlyLabelName2;
extern lv_obj_t* ui_NPlyLabelScore2;
extern lv_obj_t* ui_NPlyLabelMaxScore2;
extern lv_obj_t* ui_NPlyLabelDiff2;
extern lv_obj_t* ui_NButtonCancel;
extern lv_obj_t* ui_NLabelCancel;

extern lv_obj_t* ui_MBPanelSnookerReset;
extern lv_obj_t* ui_MBLabelSnookerResetQ;
extern lv_obj_t* ui_MBBtnSnookerResetYes;
extern lv_obj_t* ui_MBLabelSnookerResetYes;
extern lv_obj_t* ui_MBBtnSnookerResetNo;
extern lv_obj_t* ui_MBLabelSnookerResetNo;
extern lv_obj_t* ui_MBPanelSnookerPool;
extern lv_obj_t* ui_MBLabelSnookerPoolQ;
extern lv_obj_t* ui_MBBtnSnookerPoolYes;
extern lv_obj_t* ui_MBLabelSnookerPoolYes;
extern lv_obj_t* ui_MBBtnSnookerPoolNo;
extern lv_obj_t* ui_MBLabelSnookerPoolNo;


void gui_snooker_create();
void gui_snooker_delete();

String gui_snooker_getScoreMessage();

#endif

