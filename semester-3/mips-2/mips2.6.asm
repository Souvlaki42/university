.data
star: .byte '*'
nl: .byte '\n'

.text 
.globl main

main:
li $v0, 5
syscall
la $t2, ($v0)

li $v0, 5
syscall
la $t3, ($v0)

li $v0, 11
li $t0, 0

loopy:
bge $t0, $t2, exit
lb $a0, nl
syscall

li $t1, 0

loopx:
bge $t1, $t3, x_end
lb $a0, star
syscall

addi $t1, $t1, 1
b loopx

x_end:
addi $t0, $t0, 1
b loopy

exit:
li $v0, 10
syscall
