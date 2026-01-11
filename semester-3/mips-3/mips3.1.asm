.data
# 1.
# number_a: .word 0x3fffffff
# number_b: .word 0x3fffffff

# 2.
# number_a: .word 0xffffffff
# number_b: .word 0xffffffff

# 3.
# number_a: .word 0x7fffffff
# number_b: .word 0x00000001

# 4.
# number_a: .word 0x80000000
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
