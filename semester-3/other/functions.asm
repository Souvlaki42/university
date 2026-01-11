.data
number: .word 0x80000000
nl: .byte '\n'

.text
.globl main

main:
lw $s7, number
jal println_int
j exit

println:
move $a0, $s7
li $v0, 4
syscall
lb $a0, nl
li $v0, 11
syscall
jr $ra

println_mul:
li $v0, 1
mfhi $a0
syscall
mflo $a0
syscall
lb $a0, nl
li $v0, 11
syscall
jr $ra

println_int:
li $v0, 1
move $a0, $s7
syscall
lb $a0, nl
li $v0, 11
syscall
jr $ra


exit:
li $v0, 10
syscall
