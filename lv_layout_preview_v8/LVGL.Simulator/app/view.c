#include "lv_layout_preview.h"

static lv_obj_t* btn_create(lv_obj_t* par, const char* str)
{
    lv_obj_t* btn = lv_btn_create(par);
    lv_obj_set_width(btn, lv_pct(30));
    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, str);
    lv_obj_center(label);
    return btn;
}

void view_create(lv_obj_t* par, view_t* ui)
{
    /* layout */
    lv_obj_set_flex_flow(par, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(
        par,
        LV_FLEX_ALIGN_SPACE_AROUND,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_SPACE_AROUND
    );

    /* root */
    ui->root = obj_child_node_create(par, ui);
    lv_obj_set_size(ui->root, lv_pct(50), lv_pct(80));

    /* ctrl_pad */
    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_set_size(obj, lv_pct(40), lv_pct(80));
    ui->ctrl_pad.cont = obj;
    lv_obj_set_flex_flow(ui->ctrl_pad.cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        ui->ctrl_pad.cont,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_SPACE_AROUND
    );

    /* tabview */
    view_ctrl_pad_create(ui->ctrl_pad.cont, ui);

    /* btn_cont */
    obj = lv_obj_create(ui->ctrl_pad.cont);
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, lv_pct(80), 60);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(
        obj,
        LV_FLEX_ALIGN_SPACE_AROUND,
        LV_FLEX_ALIGN_SPACE_AROUND,
        LV_FLEX_ALIGN_SPACE_AROUND
    );
    ui->ctrl_pad.btn.cont = obj;
    ui->ctrl_pad.btn.add = btn_create(obj, "add");
    ui->ctrl_pad.btn.remove = btn_create(obj, "remove");

    /* fade effect */
    lv_obj_fade_in(ui->root, 600, 0);
    lv_obj_fade_in(ui->ctrl_pad.cont, 600, 300);
}
