.data
lf: .byte '\n'
comma: .byte ','

# first
# number_a: .word 0x00000009
# number_b: .word 0x0000000b

# second
# number_a: .word 0x00000009
# number_b: .word 0xffffffff

# third
# number_a: .word 0x80000000
# number_b: .word 0x80000000

.text
.globl main

main:
lw $t1, number_a
lw $t2, number_b

mult $t1, $t2
li $v0, 1
mfhi $a0
syscall
li $v0, 11
lb $a0, comma
syscall
li $v0, 1
mflo $a0
syscall
li $v0, 11
lb $a0, lf
syscall
multu $t1, $t2
li $v0, 1
mfhi $a0
syscall
li $v0, 11
lb $a0, comma
syscall
li $v0, 1
mflo $a0
syscall

exit:
li $v0, 10
syscall
