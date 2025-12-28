.data
nl: .byte '\n'

.text
.globl main

main:
li $v0, 6
syscall
mov.s $f2, $f0
syscall
mov.s $f4, $f0

lb $a0, nl

li $v0, 2
add.s $f12, $f2, $f4
syscall

li $v0, 11
syscall

li $v0, 2
sub.s $f12, $f2, $f4
syscall

li $v0, 11
syscall

li $v0, 2
mul.s $f12, $f2, $f4
syscall

exit:
li $v0, 10
syscall