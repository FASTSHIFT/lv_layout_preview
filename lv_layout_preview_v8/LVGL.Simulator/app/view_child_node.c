#include "lv_layout_preview.h"

static void obj_child_node_event_handler(lv_event_t* e)
{
    view_t* ui = (view_t*)lv_event_get_user_data(e);
    lv_obj_t* obj = lv_event_get_target(e);

    if (ui->obj_cur)
    {
        lv_obj_clear_state(ui->obj_cur, LV_STATE_CHECKED);
    }

    lv_obj_add_state(obj, LV_STATE_CHECKED);

    ui->obj_cur = obj;
    flex_loader_obj_update(obj, ui);
    ctrl_pad_obj_update(obj, ui);
}

lv_obj_t* obj_child_node_create(lv_obj_t* par, view_t* ui)
{
    if (par == NULL)
    {
        return NULL;
    }

    uint32_t cnt = lv_obj_get_child_cnt(par);

    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_set_size(obj, lv_pct(50), lv_pct(50));

    LV_LOG_USER("w:%d, h:%d", lv_obj_get_width(obj), lv_obj_get_height(obj));

    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);

    lv_obj_set_style_pad_all(obj, 0,  0);
    lv_obj_set_style_border_color(obj, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(obj, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(obj, 20, LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(obj, LV_OPA_COVER, LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(obj, LV_OPA_TRANSP, 0);

    static lv_style_transition_dsc_t tran;
    static const lv_style_prop_t prop[] = {
        LV_STYLE_SHADOW_OPA,
        LV_STYLE_BORDER_COLOR,
        LV_STYLE_PROP_INV
    };
    lv_style_transition_dsc_init(&tran, prop, lv_anim_path_ease_out, 300, 0);
    lv_obj_set_style_transition(obj, &tran, LV_STATE_CHECKED);

    lv_obj_t* label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "%d", cnt);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_center(label);

    lv_obj_add_event_cb(obj, obj_child_node_event_handler, LV_EVENT_CLICKED, ui);

    return obj;
}
