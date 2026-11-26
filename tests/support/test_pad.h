#ifndef TEST_PAD_H
#define TEST_PAD_H
#ifdef MMX4_SATURN
#include "saturn/menu.h"
#define TEST_PAD_PRESSED saturn_pad_pressed
#define TEST_PAD_HELD saturn_pad_held
#define TEST_PAD_UP SATURN_PAD_UP
#define TEST_PAD_DOWN SATURN_PAD_DOWN
#define TEST_PAD_LEFT SATURN_PAD_LEFT
#define TEST_PAD_RIGHT SATURN_PAD_RIGHT
#define TEST_PAD_START SATURN_PAD_START
#define TEST_PAD_CONFIRM SATURN_PAD_CONFIRM
#define TEST_PAD_CANCEL SATURN_PAD_CANCEL
#define TEST_PAD_SELECTION_ALT SATURN_PAD_CANCEL
#define TEST_PAD_L1 SATURN_PAD_L
#define TEST_PAD_R1 SATURN_PAD_R
#else
#define TEST_PAD_PRESSED controller_input.pressed
#define TEST_PAD_HELD controller_input.held
#define TEST_PAD_UP PADLup
#define TEST_PAD_DOWN PADLdown
#define TEST_PAD_LEFT PADLleft
#define TEST_PAD_RIGHT PADLright
#define TEST_PAD_START PADstart
#define TEST_PAD_CONFIRM PAD_CONFIRM
#define TEST_PAD_CANCEL PAD_CANCEL
#define TEST_PAD_SELECTION_ALT PAD_SELECTION_ALT
#define TEST_PAD_L1 PADL1
#define TEST_PAD_R1 PADR1
#endif

#ifdef MMX4_SATURN
#define TEST_FADE_OUT_ACTIVE 2
#define TEST_FADE_OUT_AMOUNT(amount, before) (before)
#else
#define TEST_FADE_OUT_ACTIVE -1
#define TEST_FADE_OUT_AMOUNT(amount, before) (amount)
#endif
#endif
