#include "app.h"
#include "lv_layout_preview.h"

void app_create(void)
{
    lv_obj_remove_style_all(lv_scr_act());
    lv_layout_preview_create(lv_scr_act());
}
