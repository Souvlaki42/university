.text 
.globl main

main:
li $t0, 0 # Μεγεθος λιστας
li $t1, 1 # Χωρητικοτητα λιστας σε bytes

sll $v0, $t1, 2
move $a0, $v0
li $v0, 9
syscall
move $t2, $v0

input:
li $v0, 12
syscall
beq $v0, '#', setup
subi $v0, $v0, 0x30
move $t3, $v0
beq $t0, $t1, increase
bne $t0, $t1, push

increase:
sll $t1, $t1, 1
sll $v0, $t1, 2
move $a0, $v0
li $v0, 9
syscall
li $t4, 0

copy:
sll $t5, $t4, 2
addu $t5, $t5, $t2
sll $t6, $t4, 2
addu $t6, $t6, $v0
lw $t7, 0($t5)
sw $t7, 0($t6)
addi $t4, $t4, 1
blt $t4, $t0, copy
move $t2, $v0

push:
sll $v0, $t0, 2
addu $v0, $v0, $t2
sw $t3, 0($v0)
addi $t0, $t0, 1
b input 

setup:
move $t4, $t0
subi $t4, $t4, 1
li $t5, 1 # Δυναμη του 10
li $t6, 0 # Τελικο αποτελεσμα

parse:
bltz $t4, result
sll $v0, $t4, 2
addu $v0, $v0, $t2
lw $a0, 0($v0)
mulo $a0, $a0, $t5
mulo $t5, $t5, 10
add $t6, $t6, $a0
subi $t4, $t4, 1
b parse

result:
move $a0, $t6
li $v0, 1
syscall

exit:
li $v0, 10
syscall
