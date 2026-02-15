.data
# first
# number_a: .word 0xffffffff
# number_b: .word 0x3fffffff

# second
# number_a: .word 0xffffffff
# number_b: .word 0xffffffff

# third - overflow
# number_a: .word 0x7fffffff
# number_b: .word 0x00000001

# forth
# number_a: .word 0x80000001
# number_b: .word 0xffffffff

.text
.globl main

main:
lw $t1, number_a
lw $t2, number_b
add $a0, $t1, $t2
li $v0, 1
syscall 

exit:
li $v0, 10
syscall
