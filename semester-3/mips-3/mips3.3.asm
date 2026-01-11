.data
comma: .byte ','

# first
# number_a: .word 14
# number_b: .word 4

# second
# number_a: .word -14
# number_b: .word 4

# third
# number_a: .word 14
# number_b: .word -4

# forth
# number_a: .word -14
# number_b: .word -4

# fifth
# number_a: .word 14
# number_b: .word 0

# sixth
# number_a: .word -14
# number_b: .word 0

# seventh
# number_a: .word -2147483648
# number_b: .word 1

# eighth
# number_a: .word -2147483648
# number_b: .word 100

.text
.globl main

main:
lw $t1, number_a
lw $t2, number_b
div $t1, $t2
li $v0, 1
mflo $a0
syscall
li $v0, 11
lb $a0, comma
syscall
li $v0, 1
mfhi $a0
syscall

exit:
li $v0, 10
syscall
