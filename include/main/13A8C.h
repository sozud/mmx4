#ifndef MAIN_13A8C_H
#define MAIN_13A8C_H

struct DialogueGlyphData {
    u16 count;
    u16 active;
    struct DialogueGlyph glyphs[60];
};

void func_80023A54(struct EngineObj* arg0);

void func_80023624(struct EngineObj*);
void func_80023684(struct EngineObj*);
void func_80023698(struct EngineObj*);
void func_800237E4(struct EngineObj*);
void func_80023870(struct EngineObj*);
void func_800238F0(struct EngineObj*);
void func_80023970(struct EngineObj*);
void func_800239E0(struct EngineObj*);

void func_80023AA8(struct MiscObj*);
void func_80023B98(struct MiscObj*);
void func_80023C0C(struct MiscObj*);

#endif
