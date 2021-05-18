#ifndef __LV_LAYOUT_PREVIEW_H
#define __LV_LAYOUT_PREVIEW_H

#include "lvgl/lvgl.h"

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    lv_obj_t* root;
    lv_obj_t* obj_cur;

    struct {
        lv_obj_t* cont;

        struct {
            lv_obj_t* view;

            struct {
                lv_obj_t* tab;
                lv_obj_t* roller_flow;
                lv_obj_t* checkbox_scrl;
            }flex;

            struct {
                lv_obj_t* tab;
                lv_obj_t* roller_align_main;
                lv_obj_t* roller_align_cross;
                lv_obj_t* roller_align_track;
            }align;

            struct {
                lv_obj_t* tab;
                lv_obj_t* spinbox_width;
                lv_obj_t* spinbox_height;
                lv_obj_t* spinbox_pad_top;
                lv_obj_t* spinbox_pad_bottom;
                lv_obj_t* spinbox_pad_left;
                lv_obj_t* spinbox_pad_right;
                lv_obj_t* spinbox_pad_column;
                lv_obj_t* spinbox_pad_row;
                lv_obj_t* spinbox_flex_grow;
            }layout;
        }tab;

        struct {
            lv_obj_t* cont;
            lv_obj_t* add;
            lv_obj_t* remove;
        }btn;

    }ctrl_pad;
}view_t;

void lv_layout_preview_create(lv_obj_t* par);

void view_create(lv_obj_t* par, view_t* ui);
void view_ctrl_pad_create(lv_obj_t* par, view_t* ui);
lv_obj_t* obj_child_node_create(lv_obj_t* par, view_t* ui);

void ctrl_pad_attach(view_t* ui);
void ctrl_pad_obj_update(lv_obj_t* obj, view_t* ui);
void flex_loader_obj_update(lv_obj_t* obj, view_t* ui);
void flex_loader_attach(view_t* ui);

#ifdef __cplusplus
}
#endif

#endif // ! __LV_LAYOUT_PREVIEW_H
