.set noat
.set noreorder

.macro glabel label, visibility=global
    .\visibility \label
    .type \label, @function
    \label:
.endm
