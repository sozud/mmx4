void FUNC_NAME(struct BackgroundObj* arg0)
{
    s16 delta;

    delta = arg0->x_pos.i.hi - arg0->unk14.i.hi;
    if (delta >= 0) {
        if (delta >= 0x10) {
            if (delta >= 0x148) {
                arg0->x_pos.i.hi = arg0->x_pos.i.hi - 0x140;
            } else {
                arg0->x_pos.i.hi = arg0->unk14.i.hi + 0x10;
            }
        }
    } else {
        delta = -delta;
        if (delta >= 0x10) {
            if (delta >= 0x148) {
                arg0->x_pos.i.hi = arg0->x_pos.i.hi + 0x140;
            } else {
                arg0->x_pos.i.hi = arg0->unk14.i.hi - 0x10;
            }
        }
    }

    delta = arg0->y_pos.i.hi - arg0->unk18.i.hi;
    if (delta >= 0) {
        if (delta >= 0x10) {
            if (delta >= 0x148) {
                arg0->y_pos.i.hi = arg0->y_pos.i.hi - 0x140;
            } else {
                arg0->y_pos.i.hi = arg0->unk18.i.hi + 0x10;
            }
        }
    } else {
        delta = -delta;
        if (delta >= 0x10) {
            if (delta >= 0x148) {
                arg0->y_pos.i.hi = arg0->y_pos.i.hi + 0x140;
            } else {
                arg0->y_pos.i.hi = arg0->unk18.i.hi - 0x10;
            }
        }
    }
}
