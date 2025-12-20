.data
zmsg: .asciiz "Zero"
nzmsg: .asciiz "Non Zero"

.text 
.globl main

main:
li $v0, 5
syscall
beqz $v0, zero
li, $v0, 4
la $a0, nzmsg
syscall
j exit

zero:
li $v0, 4
la $a0, zmsg
syscall

exit:
li $v0, 10
syscall
