#ifndef MMX4_SATURN_OBJECT_STATE_H
#define MMX4_SATURN_OBJECT_STATE_H
extern struct MainObj* volatile saturn_current_main_object;
extern struct WeaponObj* volatile saturn_current_weapon_object;
extern struct ShotObj* volatile saturn_current_shot_object;
extern struct VisualObj* volatile saturn_current_visual_object;
extern struct EffectObj* volatile saturn_current_effect_object;
extern struct ItemObj* volatile saturn_current_item_object;
extern struct MiscObj* volatile saturn_current_misc_object;
extern struct UnkObj* volatile saturn_current_unk_object;
extern struct QuadObj* volatile saturn_current_quad_object;
extern struct LayerObj* volatile saturn_current_layer_object;
void saturn_queue_frozen_quad(struct QuadObj*);
void saturn_gameplay_prepare(void);
void saturn_update_object_texture(void*);
#undef SP_CUR_MAIN_OBJ
#undef SP_CUR_WEAPON_OBJ
#undef SP_CUR_SHOT_OBJ
#undef SP_CUR_VISUAL_OBJ
#undef SP_CUR_EFFECT_OBJ
#undef SP_CUR_ITEM_OBJ
#undef SP_CUR_MISC_OBJ
#undef SP_CUR_UNK_OBJ
#undef SP_CUR_QUAD_OBJ
#undef SP_CUR_LAYER_OBJ
#define SP_CUR_MAIN_OBJ saturn_current_main_object
#define SP_CUR_WEAPON_OBJ saturn_current_weapon_object
#define SP_CUR_SHOT_OBJ saturn_current_shot_object
#define SP_CUR_VISUAL_OBJ saturn_current_visual_object
#define SP_CUR_EFFECT_OBJ saturn_current_effect_object
#define SP_CUR_ITEM_OBJ saturn_current_item_object
#define SP_CUR_MISC_OBJ saturn_current_misc_object
#define SP_CUR_UNK_OBJ saturn_current_unk_object
#define SP_CUR_QUAD_OBJ saturn_current_quad_object
#define SP_CUR_LAYER_OBJ saturn_current_layer_object
#endif
