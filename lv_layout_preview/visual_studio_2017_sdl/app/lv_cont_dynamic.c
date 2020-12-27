#include "lv_cont_dynamic.h"

#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#endif

struct win_obj_s;

typedef struct {
    lv_obj_t* cont;
    lv_obj_t* btn_inc;
    lv_obj_t* btn_dec;
    lv_obj_t* label_data;
    const char* name;
    struct win_obj_s* win;
}pad_ctrl_t;

typedef struct win_obj_s {
    struct {
        lv_obj_t* cont;
        lv_obj_t* slider_width;
        lv_obj_t* slider_height;
        lv_obj_t* label_width;
        lv_obj_t* label_height;
    }cont_base;

    lv_obj_t* roller_layout;

    pad_ctrl_t pad_ctrl_top;
    pad_ctrl_t pad_ctrl_bottom;
    pad_ctrl_t pad_ctrl_left;
    pad_ctrl_t pad_ctrl_right;
    pad_ctrl_t pad_ctrl_inner;
}win_obj_t;

#define STYLE_VALUE_CTRL(val)\
do{\
    if (strcmp(pad_ctrl->name, "pad_"#val) == 0)\
    {\
        if (obj == pad_ctrl->btn_inc)\
        {\
            val++;\
        }\
        else if (obj == pad_ctrl->btn_dec)\
        {\
            val--;\
        }\
        lv_label_set_text_fmt(pad_ctrl->label_data, "%d", val);\
    }\
}while(0)

static void pad_ctrl_event_handler(lv_obj_t* obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED || event == LV_EVENT_LONG_PRESSED_REPEAT)
    {
        pad_ctrl_t* pad_ctrl = (pad_ctrl_t*)lv_obj_get_user_data(obj);
        win_obj_t* win = pad_ctrl->win;

        lv_obj_t* cont = win->cont_base.cont;

        lv_style_int_t top = lv_obj_get_style_pad_top(cont, LV_BTN_PART_MAIN);
        lv_style_int_t bottom = lv_obj_get_style_pad_bottom(cont, LV_BTN_PART_MAIN);
        lv_style_int_t inner = lv_obj_get_style_pad_inner(cont, LV_BTN_PART_MAIN);
        lv_style_int_t left = lv_obj_get_style_pad_left(cont, LV_BTN_PART_MAIN);
        lv_style_int_t right = lv_obj_get_style_pad_right(cont, LV_BTN_PART_MAIN);

        STYLE_VALUE_CTRL(top);
        STYLE_VALUE_CTRL(bottom);
        STYLE_VALUE_CTRL(inner);
        STYLE_VALUE_CTRL(left);
        STYLE_VALUE_CTRL(right);

        lv_obj_set_style_local_pad_top(cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, top);
        lv_obj_set_style_local_pad_bottom(cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, bottom);
        lv_obj_set_style_local_pad_inner(cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, inner);
        lv_obj_set_style_local_pad_left(cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, left);
        lv_obj_set_style_local_pad_right(cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, right);
    }
}

static void pad_ctrl_create(
    lv_obj_t* par,
    win_obj_t* win,
    pad_ctrl_t* pad_ctrl,
    const char* name,
    lv_align_t align,
    lv_coord_t x_ofs,
    lv_coord_t y_ofs
)
{
    pad_ctrl->name = name;
    pad_ctrl->win = win;

    lv_obj_t* cont = lv_cont_create(par, NULL);
    lv_obj_set_size(cont, 90, 60);
    lv_obj_align(cont, NULL, align, x_ofs, y_ofs);

    lv_obj_set_style_local_value_str(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, name);
    lv_obj_set_style_local_value_align(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_IN_TOP_MID);

    lv_obj_t* btn = lv_btn_create(cont, NULL);
    lv_obj_set_size(btn, 25, 30);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 2, -2);
    lv_obj_set_style_local_value_str(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_PLUS);
    lv_obj_set_event_cb(btn, pad_ctrl_event_handler);
    lv_obj_set_user_data(btn, pad_ctrl);

    pad_ctrl->btn_inc = btn;

    btn = lv_btn_create(cont, btn);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -2, -2);
    lv_obj_set_style_local_value_str(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_MINUS);

    pad_ctrl->btn_dec = btn;

    lv_obj_t* label = lv_label_create(cont, NULL);
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
    lv_obj_set_auto_realign(label, true);

    pad_ctrl->label_data = label;

    lv_event_send(pad_ctrl->btn_inc, LV_EVENT_CLICKED, NULL);
    lv_event_send(pad_ctrl->btn_dec, LV_EVENT_CLICKED, NULL);
}

static void pad_ctrl_grp_create(lv_obj_t* par, win_obj_t* win)
{
    lv_obj_t* obj = lv_obj_create(par, NULL);

    lv_obj_set_size(obj, 300, 250);
    lv_obj_align(obj, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -20, -30);

    pad_ctrl_create(obj, win, &(win->pad_ctrl_top),    "pad_top",    LV_ALIGN_IN_TOP_MID, 0, 5);
    pad_ctrl_create(obj, win, &(win->pad_ctrl_bottom), "pad_bottom", LV_ALIGN_IN_BOTTOM_MID, 0, -5);
    pad_ctrl_create(obj, win, &(win->pad_ctrl_left),   "pad_left",   LV_ALIGN_IN_LEFT_MID, 5, 0);
    pad_ctrl_create(obj, win, &(win->pad_ctrl_right),  "pad_right",  LV_ALIGN_IN_RIGHT_MID, -5, 0);
    pad_ctrl_create(obj, win, &(win->pad_ctrl_inner),  "pad_inner",  LV_ALIGN_CENTER, 0, 0);
}

static void silder_ctrl_event_handler(lv_obj_t* obj, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        win_obj_t* win = (win_obj_t*)lv_obj_get_user_data(obj);

        lv_coord_t w = lv_slider_get_value(win->cont_base.slider_width);
        lv_coord_t h_max = lv_slider_get_max_value(win->cont_base.slider_height);
        lv_coord_t h = h_max - lv_slider_get_value(win->cont_base.slider_height);

        lv_obj_set_size(win->cont_base.cont, w, h);
        lv_label_set_text_fmt(win->cont_base.label_width, "%d", w);
        lv_label_set_text_fmt(win->cont_base.label_height, "%d", h);
    }
}

static void silder_ctrl_create(lv_obj_t* par, win_obj_t* win)
{
    lv_obj_t* slider;
    lv_obj_t* label;

    lv_coord_t w = lv_obj_get_width(win->cont_base.cont);
    lv_coord_t h = lv_obj_get_height(win->cont_base.cont);

    slider = lv_slider_create(par, NULL);
    lv_obj_set_size(slider, w, 10);
    lv_obj_align(slider, win->cont_base.cont, LV_ALIGN_OUT_TOP_MID, 0, -20);
    lv_obj_set_event_cb(slider, silder_ctrl_event_handler);
    lv_obj_set_user_data(slider, win);
    lv_slider_set_range(slider, 0, w);
    lv_slider_set_value(slider, w, LV_ANIM_OFF);

    win->cont_base.slider_width = slider;

    slider = lv_slider_create(par, slider);
    lv_obj_set_size(slider, 10, h);
    lv_obj_align(slider, win->cont_base.cont, LV_ALIGN_OUT_LEFT_TOP, -20, 0);
    lv_slider_set_range(slider, 0, h);
    lv_slider_set_value(slider, 0, LV_ANIM_OFF);
    lv_color_t color_bg = lv_obj_get_style_bg_color(slider, LV_SLIDER_PART_BG);
    lv_color_t color_indic = lv_obj_get_style_bg_color(slider, LV_SLIDER_PART_INDIC);
    lv_obj_set_style_local_bg_color(slider, LV_SLIDER_PART_BG, LV_STATE_DEFAULT, color_indic);
    lv_obj_set_style_local_bg_color(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, color_bg);

    win->cont_base.slider_height = slider;

    label = lv_label_create(par, NULL);
    lv_obj_align(label, win->cont_base.cont, LV_ALIGN_OUT_TOP_MID, 0, -2);
    lv_obj_set_auto_realign(label, true);
    lv_label_set_text_fmt(label, "%d", w);

    win->cont_base.label_width = label;

    label = lv_label_create(par, label);
    lv_obj_align(label, win->cont_base.cont, LV_ALIGN_OUT_LEFT_MID, -2, 0);
    lv_label_set_text_fmt(label, "%d", h);

    win->cont_base.label_height = label;
}

static void roller_layout_event_handler(lv_obj_t* obj, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        win_obj_t* win = (win_obj_t*)lv_obj_get_user_data(obj);

        uint16_t sel_index = lv_roller_get_selected(obj);

        if (sel_index < _LV_LAYOUT_LAST)
        {
            lv_layout_t layout = (lv_layout_t)sel_index;
            lv_cont_set_layout(win->cont_base.cont, layout);
        }
    }
}

static void roller_layout_create(lv_obj_t* par, win_obj_t* win)
{
    lv_obj_t* roller = lv_roller_create(par, NULL);
    lv_roller_set_options(
        roller,
        "LV_LAYOUT_OFF\n"
        "LV_LAYOUT_CENTER\n"
        "LV_LAYOUT_COLUMN_LEFT\n"
        "LV_LAYOUT_COLUMN_MID\n"
        "LV_LAYOUT_COLUMN_RIGHT\n"
        "LV_LAYOUT_ROW_TOP\n"
        "LV_LAYOUT_ROW_MID\n"
        "LV_LAYOUT_ROW_BOTTOM\n"
        "LV_LAYOUT_PRETTY_TOP\n"
        "LV_LAYOUT_PRETTY_MID\n"
        "LV_LAYOUT_PRETTY_BOTTOM\n"
        "LV_LAYOUT_GRID",
        LV_ROLLER_MODE_NORMAL
    );

    lv_roller_set_visible_row_count(roller, 4);
    lv_obj_align(roller, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 20);
    lv_obj_set_event_cb(roller, roller_layout_event_handler);
    lv_obj_set_user_data(roller, win);

    win->roller_layout = roller;
}

static void cont_base_create(lv_obj_t* par, win_obj_t* win)
{
    lv_obj_t* cont = lv_cont_create(par, NULL);
    lv_obj_set_size(cont, lv_obj_get_width(par) / 2, lv_obj_get_height(par) - 80);
    lv_obj_align(cont, NULL, LV_ALIGN_IN_LEFT_MID, 40, 10);

    win->cont_base.cont = cont;
}

static void cont_base_add_child(win_obj_t* win, int num)
{
    lv_obj_t* cont = win->cont_base.cont;

    for (int i = 0; i < num; i++)
    {
        lv_obj_t* obj = lv_obj_create(cont, NULL);
        lv_obj_set_drag(obj, true);

        lv_obj_t* label = lv_label_create(obj, NULL);
        lv_label_set_text_fmt(label, "%d", i);
        lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
    }
}

void lv_cont_dynamic_create(lv_obj_t* par)
{
    static win_obj_t win_obj;

    cont_base_create(par, &win_obj);
    cont_base_add_child(&win_obj, 12);
    silder_ctrl_create(par, &win_obj);
    roller_layout_create(par, &win_obj);

    pad_ctrl_grp_create(par, &win_obj);
}
