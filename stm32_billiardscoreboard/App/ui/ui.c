// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.3.4
// PROJECT: SquareLine_Pool3

#include "ui.h"
#include "appMain.h"

///////////////////// VARIABLES ////////////////////
void ui_event_ResetBTN(lv_event_t *e);
lv_obj_t *ui_ResetBTN;

void ui_event_Screen0(lv_event_t *e);
lv_obj_t *ui_Screen0;
lv_obj_t *ui_Time;

void ui_event_Screen1(lv_event_t *e);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_Label1P;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Label1M;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Label2P;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Label2M;
lv_obj_t * ui_Switch;

void ui_event_Screen2(lv_event_t *e);
lv_obj_t *ui_Screen2;
lv_obj_t *ui_Panel3;
lv_obj_t *ui_Label3P;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Label3M;
lv_obj_t *ui_Panel4;
lv_obj_t *ui_Label4P;
lv_obj_t *ui_Label4;
lv_obj_t *ui_Label4M;
lv_obj_t *ui_Panel5;
lv_obj_t *ui_Label5P;
lv_obj_t *ui_Label5;
lv_obj_t *ui_Label5M;

int32_t ply1_score_value;
int32_t ply2_score_value;
int32_t ply3_score_value;
int32_t ply4_score_value;
int32_t ply5_score_value;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

void time_event_cb(lv_event_t *e)
{
	lv_obj_t *label = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		lv_msg_t *m = lv_event_get_msg(e);
	    lv_label_set_text(label, lv_msg_get_payload(m));
	}
}

void label_event_cb(lv_event_t *e)
{
	lv_obj_t *label = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		if (label == ui_Label1P)
		{
			++ply1_score_value;
			lv_msg_update_value(&ply1_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label1M)
		{
			--ply1_score_value;
			lv_msg_update_value(&ply1_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label2P)
		{
			++ply2_score_value;
			lv_msg_update_value(&ply2_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label2M)
		{
			--ply2_score_value;
			lv_msg_update_value(&ply2_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label3P)
		{
			++ply3_score_value;
			lv_msg_update_value(&ply3_score_value);
		}
		else if (label == ui_Label3M)
		{
			--ply3_score_value;
			lv_msg_update_value(&ply3_score_value);
		}
		else if (label == ui_Label4P)
		{
			++ply4_score_value;
			lv_msg_update_value(&ply4_score_value);
		}
		else if (label == ui_Label4M)
		{
			--ply4_score_value;
			lv_msg_update_value(&ply4_score_value);
		}
		else if (label == ui_Label5P)
		{
			++ply5_score_value;
			lv_msg_update_value(&ply5_score_value);
		}
		else if (label == ui_Label5M)
		{
			--ply5_score_value;
			lv_msg_update_value(&ply5_score_value);
		}
	}
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		lv_msg_t *m = lv_event_get_msg(e);
		const int32_t *v = lv_msg_get_payload(m);
		lv_label_set_text_fmt(label, "%ld", *v);
	}
}

void switch_event_cb(lv_event_t *e)
{
	lv_obj_t *sw = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		if(lv_obj_has_state(sw, LV_STATE_CHECKED))
			lv_obj_clear_state(sw, LV_STATE_CHECKED);
		else
			lv_obj_add_state(sw, LV_STATE_CHECKED);

		lv_obj_invalidate(sw);
	}
}

void ui_event_ResetBTN(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	if (event_code == LV_EVENT_CLICKED)
	{
		resetTimer();

		lv_msg_send(MSG_TIME_CHANGED, "0:00:00");

		ply1_score_value = 0;
		lv_msg_update_value(&ply1_score_value);
		ply2_score_value = 0;
		lv_msg_update_value(&ply2_score_value);
		ply3_score_value = 0;
		lv_msg_update_value(&ply3_score_value);
		ply4_score_value = 0;
		lv_msg_update_value(&ply4_score_value);
		ply5_score_value = 0;
		lv_msg_update_value(&ply5_score_value);
	}
}


void ui_event_Screen0(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	if (event_code == LV_EVENT_GESTURE)
	{
		lv_dir_t direction = lv_indev_get_gesture_dir(lv_indev_get_act());
		if (direction == LV_DIR_LEFT)
		{
			lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 100, 0, false);
		}
		else if (direction == LV_DIR_RIGHT)
		{
			lv_scr_load_anim(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 100, 0, false);
		}
	}
}
void ui_event_Screen1(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	if (event_code == LV_EVENT_GESTURE)
	{
		lv_dir_t direction = lv_indev_get_gesture_dir(lv_indev_get_act());
		if (direction == LV_DIR_LEFT)
		{
			lv_scr_load_anim(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 100, 0, false);
		}
		else if (direction == LV_DIR_RIGHT)
		{
			lv_scr_load_anim(ui_Screen0, LV_SCR_LOAD_ANIM_NONE, 100, 0, false);
		}
	}
}
void ui_event_Screen2(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	if (event_code == LV_EVENT_GESTURE)
	{
		lv_dir_t direction = lv_indev_get_gesture_dir(lv_indev_get_act());
		if (direction == LV_DIR_LEFT)
		{
			lv_scr_load_anim(ui_Screen0, LV_SCR_LOAD_ANIM_NONE, 100, 0, false);
		}
		else if (direction == LV_DIR_RIGHT)
		{
			lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 100, 0, false);
		}
	}
}


///////////////////// SCREENS ////////////////////
void ui_Screen0_screen_init(void)
{
    ui_Screen0 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen0, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen0, lv_color_hex(0x28D1CD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen0, lv_color_hex(0x03000E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen0, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time = lv_label_create(ui_Screen0);
    lv_obj_set_width(ui_Time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Time, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Time, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_Time, "0:00:00");
    lv_obj_set_style_text_color(ui_Time, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Time, &ui_font_Ubuntu80Digits, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ResetBTN = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ResetBTN, &ui_img_icn_history_png);
    lv_obj_set_width(ui_ResetBTN, 20);
    lv_obj_set_height(ui_ResetBTN, 20);
    lv_obj_set_x(ui_ResetBTN, 120);
    lv_obj_set_y(ui_ResetBTN, -80);
    lv_obj_set_align(ui_ResetBTN, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ResetBTN, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ResetBTN, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_ResetBTN, ui_event_ResetBTN, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen0, ui_event_Screen0, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Time, time_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj(MSG_TIME_CHANGED, ui_Time, NULL);
}

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1, &ui_font_Ubuntu80Digits, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, lv_pct(50));
    lv_obj_set_height(ui_Panel1, lv_pct(100));
    lv_obj_set_align(ui_Panel1, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel1, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1P = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1P, lv_pct(50));
    lv_obj_set_height(ui_Label1P, lv_pct(30));
    lv_obj_set_align(ui_Label1P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label1P, "+");
    lv_obj_add_flag(ui_Label1P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label1 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1, lv_pct(95));
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label1, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label1, "0");

    ui_Label1M = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1M, lv_pct(50));
    lv_obj_set_height(ui_Label1M, lv_pct(30));
    lv_obj_set_align(ui_Label1M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label1M, "-");
    lv_obj_add_flag(ui_Label1M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Panel2 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel2, lv_pct(50));
    lv_obj_set_height(ui_Panel2, lv_pct(100));
    lv_obj_set_align(ui_Panel2, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel2, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel2, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2P = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2P, lv_pct(50));
    lv_obj_set_height(ui_Label2P, lv_pct(30));
    lv_obj_set_align(ui_Label2P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label2P, "+");
    lv_obj_add_flag(ui_Label2P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label2 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2, lv_pct(95));
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label2, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label2, "0");

    ui_Label2M = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2M, lv_pct(50));
    lv_obj_set_height(ui_Label2M, lv_pct(30));
    lv_obj_set_align(ui_Label2M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label2M, "-");
    lv_obj_add_flag(ui_Label2M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Switch = lv_switch_create(ui_Screen1);
    lv_obj_set_width(ui_Switch, 50);
    lv_obj_set_height(ui_Switch, 20);
    lv_obj_set_x(ui_Switch, 0);
    lv_obj_set_y(ui_Switch, 60);
    lv_obj_set_align(ui_Switch, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_Switch, LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_Switch, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Switch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Screen1, ui_event_Screen1, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label1, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply1_score_value, ui_Label1, NULL);

	lv_obj_add_event_cb(ui_Label2, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply2_score_value, ui_Label2, NULL);

	lv_obj_add_event_cb(ui_Label1P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label1M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label2P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label2M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Switch, switch_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj(MSG_SWITCH_CHANGED, ui_Switch, NULL);

}

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Screen2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen2, &ui_font_Ubuntu80Digits, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel3 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel3, lv_pct(33));
    lv_obj_set_height(ui_Panel3, lv_pct(100));
    lv_obj_set_align(ui_Panel3, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel3, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel3, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel3, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3P = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label3P, lv_pct(50));
    lv_obj_set_height(ui_Label3P, lv_pct(30));
    lv_obj_set_align(ui_Label3P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label3P, "+");
    lv_obj_add_flag(ui_Label3P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label3 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label3, lv_pct(95));
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label3, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label3, "0");

    ui_Label3M = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label3M, lv_pct(50));
    lv_obj_set_height(ui_Label3M, lv_pct(30));
    lv_obj_set_align(ui_Label3M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label3M, "-");
    lv_obj_add_flag(ui_Label3M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Panel4 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel4, lv_pct(33));
    lv_obj_set_height(ui_Panel4, lv_pct(100));
    lv_obj_set_align(ui_Panel4, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel4, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel4, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel4, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel4, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label4P = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label4P, lv_pct(50));
    lv_obj_set_height(ui_Label4P, lv_pct(30));
    lv_obj_set_align(ui_Label4P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label4P, "+");
    lv_obj_add_flag(ui_Label4P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label4 = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label4, lv_pct(95));
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label4, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label4, "0");

    ui_Label4M = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label4M, lv_pct(50));
    lv_obj_set_height(ui_Label4M, lv_pct(30));
    lv_obj_set_align(ui_Label4M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label4M, "-");
    lv_obj_add_flag(ui_Label4M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Panel5 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel5, lv_pct(33));
    lv_obj_set_height(ui_Panel5, lv_pct(100));
    lv_obj_set_align(ui_Panel5, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_Panel5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel5, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel5, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel5, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel5, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label5P = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5P, lv_pct(50));
    lv_obj_set_height(ui_Label5P, lv_pct(30));
    lv_obj_set_align(ui_Label5P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label5P, "+");
    lv_obj_add_flag(ui_Label5P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label5 = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5, lv_pct(95));
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label5, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label5, "0");

    ui_Label5M = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5M, lv_pct(50));
    lv_obj_set_height(ui_Label5M, lv_pct(30));
    lv_obj_set_align(ui_Label5M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label5M, "-");
    lv_obj_add_flag(ui_Label5M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    lv_obj_add_event_cb(ui_Screen2, ui_event_Screen2, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label3, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply3_score_value, ui_Label3, NULL);

	lv_obj_add_event_cb(ui_Label4, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply4_score_value, ui_Label4, NULL);

	lv_obj_add_event_cb(ui_Label5, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply5_score_value, ui_Label5, NULL);

	lv_obj_add_event_cb(ui_Label3P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label3M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label4P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label4M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label5P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label5M, label_event_cb, LV_EVENT_ALL, NULL);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_Screen0_screen_init();
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    lv_disp_load_scr(ui_Screen0);
}
