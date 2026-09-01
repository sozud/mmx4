.ifndef __MMX4_MACRO_INC
.set __MMX4_MACRO_INC, 1

.macro jlabel label
    glabel \label
.endm

.macro glabel label
    .global \label
    \label:
.endm

.macro .def #
.endm
.endif
