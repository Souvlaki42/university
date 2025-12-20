.data
star: .byte '*'
nl: .byte '\n'

.text 
.globl main

main:
li $v0, 5
syscall

li $t1, 0
la $t2, ($v0)
li $v0, 11

loop:
lb $a0, star
syscall
lb $a0, nl
syscall

addi $t1, $t1, 1

slt $t3, $t1, $t2
bnez $t3, loop

exit:
li $v0, 10
syscall
