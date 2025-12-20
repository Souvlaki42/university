.data
str: .space 16

.text 
.globl main

main:
li $t0, 0
la $t1, 16

la $a0, str
la $a1, ($t1)
li $v0, 8
syscall

loop:
bge $t0, $t1, loop_end
lb $a0, str($t0)
beqz $a0, loop_end

addi $t0, $t0, 1
b loop

loop_end:
subi $t0, $t0, 1
la $a0, ($t0)
li $v0, 1
syscall

exit:
li $v0, 10
syscall
