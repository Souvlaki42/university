.data
str: .space 16

.text 
.globl main

main:
li $t0, 16

la $a0, str
la $a1, ($t0)
li $v0, 8
syscall

loop:
bltz $t0, exit
lb $a0, str($t0)

li $v0, 11
syscall

subi $t0, $t0, 1
b loop

exit:
li $v0, 10
syscall
