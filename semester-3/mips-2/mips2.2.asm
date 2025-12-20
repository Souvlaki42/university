.data
pmsg: .asciiz "Positive"
npmsg: .asciiz "Non Positive"

.text 
.globl main

main:
li $v0, 5
syscall
bgtz $v0, positive
li, $v0, 4
la $a0, npmsg
syscall
j exit

positive:
li $v0, 4
la $a0, pmsg
syscall

exit:
li $v0, 10
syscall
