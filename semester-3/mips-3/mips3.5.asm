.data
emsg: .asciiz "Number is even!\n"
omsg: .asciiz "Number is odd!\n"

.text
.globl main

main:
li $v0, 5
syscall

and $t1, $v0, 0x1
li $v0, 4
beqz $t1, even
la $a0, omsg
syscall
b exit

even:
la $a0, emsg
syscall

exit:
li $v0, 10
syscall