.data
arr: .word 1, 13, 0, -3, 99, 48, -18, -9, 20, 15

.text 
.globl main

main:
li $t0, 0
li $t1, 10
li $a0, 0

loop:
bge $t0, $t1, exit
sll $t2, $t0, 2
lw $t3, arr($t2)
addu $a0, $a0, $t3
addi $t0, $t0, 1
b loop

exit:
li $v0, 10
syscall
