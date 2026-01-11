.data
input_msg: .asciiz "Give an integer between 0 and 255: "
hex_table: .ascii "0123456789abcdef"
new_line: .byte '\n'

.text
.globl main

main:
li $v0, 4
la $a0, input_msg
syscall

li $v0, 5
syscall

srl $t0, $v0, 4
and $t0, 15
and $t1, $v0, 15

li $v0, 11
lb $a0, hex_table($t0)
syscall

lb $a0, hex_table($t1)
syscall

exit:
li $v0, 10
syscall
