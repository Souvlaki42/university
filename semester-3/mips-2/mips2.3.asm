.data
pmsg: .asciiz "Positive"
nmsg: .asciiz "Negative"
zmsg: .asciiz "Zero"

.text 
.globl main

main:
li $v0, 5
syscall
bltz $v0, negative
beqz $v0, zero
li, $v0, 4
la $a0, pmsg
syscall
j exit

negative:
li $v0, 4
la $a0, nmsg
syscall
j exit

zero:
li $v0, 4
la $a0, zmsg
syscall

exit:
li $v0, 10
syscall
