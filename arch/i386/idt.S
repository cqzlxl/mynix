.extern handle_interrupt


.macro handler_with_error_code num
.global interrupt_handler_\num
interrupt_handler_\num:
    pushl $\num
    jmp   do_handle_interrupt
.endm

.macro handler_without_error_code num
.global interrupt_handler_\num
interrupt_handler_\num:
    pushl $0
    pushl $\num
    jmp   do_handle_interrupt
.endm


.section .data
.align 4
.global idt_start, idt_limit
idt_start:
.skip 8 * 256
idt_limit:

idtr:
.align 4
.2byte idt_limit - idt_start - 1
.4byte idt_start


.section .text
.global load_idtr
load_idtr:
    lidt  idtr
    ret

do_handle_interrupt:
    pushl %esp
    pushl %ebp
    pushl %edi
    pushl %esi
    pushl %ss
    pushl %gs
    pushl %fs
    pushl %es
    pushl %ds
    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax

    call handle_interrupt

    popl  %eax
    popl  %ebx
    popl  %ecx
    popl  %edx
    popl  %ds
    popl  %es
    popl  %fs
    popl  %gs
    popl  %ss
    popl  %esi
    popl  %edi
    popl  %ebp
    popl  %esp

    // error code & interrupt number
    addl $8, %esp

    iret

// interrupt 8, 10, 11, 12, 13, 14 and 17 has error code
handlers:
handler_without_error_code 0
handler_without_error_code 1
handler_without_error_code 2
handler_without_error_code 3
handler_without_error_code 4
handler_without_error_code 5
handler_without_error_code 6
handler_with_error_code    7
handler_without_error_code 8
handler_with_error_code    9
handler_with_error_code    10
handler_with_error_code    11
handler_with_error_code    12
handler_with_error_code    13
handler_without_error_code 14
handler_without_error_code 15
handler_with_error_code    16
handler_without_error_code 17
handler_without_error_code 18
handler_without_error_code 19
handler_without_error_code 20
handler_without_error_code 21
handler_without_error_code 22
handler_without_error_code 23
handler_without_error_code 24
handler_without_error_code 25
handler_without_error_code 26
handler_without_error_code 27
handler_without_error_code 28
handler_without_error_code 29
handler_without_error_code 30
handler_without_error_code 31
handler_without_error_code 32
handler_without_error_code 33
handler_without_error_code 34
handler_without_error_code 35
handler_without_error_code 36
handler_without_error_code 37
handler_without_error_code 38
handler_without_error_code 39
handler_without_error_code 40
handler_without_error_code 41
handler_without_error_code 42
handler_without_error_code 43
handler_without_error_code 44
handler_without_error_code 45
handler_without_error_code 46
handler_without_error_code 47
handler_without_error_code 48
handler_without_error_code 49
handler_without_error_code 50
handler_without_error_code 51
handler_without_error_code 52
handler_without_error_code 53
handler_without_error_code 54
handler_without_error_code 55
handler_without_error_code 56
handler_without_error_code 57
handler_without_error_code 58
handler_without_error_code 59
handler_without_error_code 60
handler_without_error_code 61
handler_without_error_code 62
handler_without_error_code 63
handler_without_error_code 64
handler_without_error_code 65
handler_without_error_code 66
handler_without_error_code 67
handler_without_error_code 68
handler_without_error_code 69
handler_without_error_code 70
handler_without_error_code 71
handler_without_error_code 72
handler_without_error_code 73
handler_without_error_code 74
handler_without_error_code 75
handler_without_error_code 76
handler_without_error_code 77
handler_without_error_code 78
handler_without_error_code 79
handler_without_error_code 80
handler_without_error_code 81
handler_without_error_code 82
handler_without_error_code 83
handler_without_error_code 84
handler_without_error_code 85
handler_without_error_code 86
handler_without_error_code 87
handler_without_error_code 88
handler_without_error_code 89
handler_without_error_code 90
handler_without_error_code 91
handler_without_error_code 92
handler_without_error_code 93
handler_without_error_code 94
handler_without_error_code 95
handler_without_error_code 96
handler_without_error_code 97
handler_without_error_code 98
handler_without_error_code 99
handler_without_error_code 100
handler_without_error_code 101
handler_without_error_code 102
handler_without_error_code 103
handler_without_error_code 104
handler_without_error_code 105
handler_without_error_code 106
handler_without_error_code 107
handler_without_error_code 108
handler_without_error_code 109
handler_without_error_code 110
handler_without_error_code 111
handler_without_error_code 112
handler_without_error_code 113
handler_without_error_code 114
handler_without_error_code 115
handler_without_error_code 116
handler_without_error_code 117
handler_without_error_code 118
handler_without_error_code 119
handler_without_error_code 120
handler_without_error_code 121
handler_without_error_code 122
handler_without_error_code 123
handler_without_error_code 124
handler_without_error_code 125
handler_without_error_code 126
handler_without_error_code 127
handler_without_error_code 128
handler_without_error_code 129
handler_without_error_code 130
handler_without_error_code 131
handler_without_error_code 132
handler_without_error_code 133
handler_without_error_code 134
handler_without_error_code 135
handler_without_error_code 136
handler_without_error_code 137
handler_without_error_code 138
handler_without_error_code 139
handler_without_error_code 140
handler_without_error_code 141
handler_without_error_code 142
handler_without_error_code 143
handler_without_error_code 144
handler_without_error_code 145
handler_without_error_code 146
handler_without_error_code 147
handler_without_error_code 148
handler_without_error_code 149
handler_without_error_code 150
handler_without_error_code 151
handler_without_error_code 152
handler_without_error_code 153
handler_without_error_code 154
handler_without_error_code 155
handler_without_error_code 156
handler_without_error_code 157
handler_without_error_code 158
handler_without_error_code 159
handler_without_error_code 160
handler_without_error_code 161
handler_without_error_code 162
handler_without_error_code 163
handler_without_error_code 164
handler_without_error_code 165
handler_without_error_code 166
handler_without_error_code 167
handler_without_error_code 168
handler_without_error_code 169
handler_without_error_code 170
handler_without_error_code 171
handler_without_error_code 172
handler_without_error_code 173
handler_without_error_code 174
handler_without_error_code 175
handler_without_error_code 176
handler_without_error_code 177
handler_without_error_code 178
handler_without_error_code 179
handler_without_error_code 180
handler_without_error_code 181
handler_without_error_code 182
handler_without_error_code 183
handler_without_error_code 184
handler_without_error_code 185
handler_without_error_code 186
handler_without_error_code 187
handler_without_error_code 188
handler_without_error_code 189
handler_without_error_code 190
handler_without_error_code 191
handler_without_error_code 192
handler_without_error_code 193
handler_without_error_code 194
handler_without_error_code 195
handler_without_error_code 196
handler_without_error_code 197
handler_without_error_code 198
handler_without_error_code 199
handler_without_error_code 200
handler_without_error_code 201
handler_without_error_code 202
handler_without_error_code 203
handler_without_error_code 204
handler_without_error_code 205
handler_without_error_code 206
handler_without_error_code 207
handler_without_error_code 208
handler_without_error_code 209
handler_without_error_code 210
handler_without_error_code 211
handler_without_error_code 212
handler_without_error_code 213
handler_without_error_code 214
handler_without_error_code 215
handler_without_error_code 216
handler_without_error_code 217
handler_without_error_code 218
handler_without_error_code 219
handler_without_error_code 220
handler_without_error_code 221
handler_without_error_code 222
handler_without_error_code 223
handler_without_error_code 224
handler_without_error_code 225
handler_without_error_code 226
handler_without_error_code 227
handler_without_error_code 228
handler_without_error_code 229
handler_without_error_code 230
handler_without_error_code 231
handler_without_error_code 232
handler_without_error_code 233
handler_without_error_code 234
handler_without_error_code 235
handler_without_error_code 236
handler_without_error_code 237
handler_without_error_code 238
handler_without_error_code 239
handler_without_error_code 240
handler_without_error_code 241
handler_without_error_code 242
handler_without_error_code 243
handler_without_error_code 244
handler_without_error_code 245
handler_without_error_code 246
handler_without_error_code 247
handler_without_error_code 248
handler_without_error_code 249
handler_without_error_code 250
handler_without_error_code 251
handler_without_error_code 252
handler_without_error_code 253
handler_without_error_code 254
handler_without_error_code 255
