.data:
arr: .word -10, -6, -2, 2, 6, 10, 14, 18
.text:
.globl main
main:
la $t1, arr
la $t2, arr
add $t3, $t1, 24
add $t4, $zero, $zero
loop:
lw $t5, 0($t2)
beq $t2, $t3, exit
add $t4, $t4, $t5
addi $t2, $t2, 8
j loop
exit:
move $a0, $t4
li $v0, 1
syscall
li $v0, 10
syscall
