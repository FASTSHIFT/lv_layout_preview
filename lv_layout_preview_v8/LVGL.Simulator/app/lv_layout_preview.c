#include "lv_layout_preview.h"

void lv_layout_preview_create(lv_obj_t* par)
{
    static view_t view;

    view_create(par, &view);

    ctrl_pad_attach(&view);
}
