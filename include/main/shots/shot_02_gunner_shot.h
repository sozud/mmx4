#ifndef MAIN_SHOTS_SHOT_02_GUNNER_SHOT_H
#define MAIN_SHOTS_SHOT_02_GUNNER_SHOT_H

void gunner_shot_update(struct ShotObj*);
void eregion_fireball_update(struct ShotObj*);
void eregion_wing_slash_update(struct ShotObj*);
void mech_boulder_update(struct ShotObj*);

void gunner_shot_unused(struct ShotObj*);

void func_80099D54(struct ShotObj*);
void gunner_shot_fly(struct ShotObj*);
void gunner_shot_despawn(struct ShotObj*);

void func_80099F48(struct ShotObj*);
void func_8009A10C(struct ShotObj*);
void eregion_fireball_despawn(struct ShotObj*);
void eregion_fireball_explode(struct ShotObj*);

void func_8009A448(struct ShotObj*);
void eregion_wing_slash_active(struct ShotObj*);
void eregion_wing_slash_despawn(struct ShotObj*);

void func_8009A5F4(struct ShotObj*);
void mech_boulder_fall(struct ShotObj*);
void mech_boulder_despawn(struct ShotObj*);
void mech_boulder_shockwave_start(struct ShotObj*);
void mech_boulder_shockwave(struct ShotObj*);
void mech_boulder_shockwave_despawn(struct ShotObj*);

#endif
