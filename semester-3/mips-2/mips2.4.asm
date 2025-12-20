.data
char: .byte '*'

.text 
.globl main

main:
li $t1, 1
lb $a0, char
li $v0, 11
li $t2, 6

loop:
syscall
addi $t1, $t1, 1

slt $t3, $t1, $t2
bnez $t3, loop

exit:
li $v0, 10
syscall
