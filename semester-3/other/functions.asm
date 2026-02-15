.data
number_a: .word 0x00000009
number_b: .word 0x0000000b
nl: .byte '\n'

message: .asciiz "It worked!"

.text
.globl main

main:
li $v0, 1
lw $t1, number_a
lw $t2, number_b
mult $t1, $t2
jal println_mul
multu $t1, $t2
jal println_mul
la $s7, message
jal println
j exit

println:
move $a0, $s7
li $v0, 4
syscall
lb $a0, nl
li $v0, 11
syscall
jr $ra

println_mul:
li $v0, 1
mfhi $a0
syscall
mflo $a0
syscall
lb $a0, nl
li $v0, 11
syscall
jr $ra

exit:
li $v0, 10
syscall
