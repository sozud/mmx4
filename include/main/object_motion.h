#ifndef MAIN_OBJECT_MOTION_H
#define MAIN_OBJECT_MOTION_H

#ifdef MMX4_PC
extern u8 angle_from_delta (s32 arg0, s32 arg1);

extern u8 get_random ();
#endif

s16 func_8002BAA4(void);

ret_u8 get_random_nonzero(void);

ret_u8 angle_to_object(struct ObjectHeader*, struct ObjectHeader*);

s16 get_layout_screen(s16, s16, s16);

void move_object(struct MovingObj*);
ret_u8 angle_to_point(struct ObjectHeader*, s32, s32);
void set_velocity_from_angle(struct MovingObj*, arg_u8);
void func_8002B9F0(s32* arg0, s32* arg1, u8 arg2);

void move_with_gravity(struct AnimatedObj* arg0);

#endif
