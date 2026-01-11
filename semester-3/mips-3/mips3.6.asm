.text
.globl main

main:
li $v0, 5
syscall
move $t0, $v0
li $t1, 32

loop:
srl $t2, $t0, 31 
and $t2, $t2, 1
addi $a0, $t2, 48
li $v0, 11
syscall
sll $t0, $t0, 1
addi $t1, $t1, -1
bnez $t1, loop

exit:
li $v0, 10
syscall