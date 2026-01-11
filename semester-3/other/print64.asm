.data
newline: .asciiz "\n"

.text
# Main program (Test with large value)
main:
    li $a0, 0x1234      # Test HI part
    li $a1, 0x56789ABC  # Test LO part
    jal print64
    
    li $v0, 10
    syscall

# ---------------------------------------------------------
# print64: Prints 64-bit unsigned integer in $a0:$a1
# Clobbers: $t0-$t9, $a0-$a1
# ---------------------------------------------------------
print64:
    # If High is 0, just print Low using syscall 1 (Optimization)
    bnez $a0, full_print
    li $v0, 1
    move $a0, $a1
    syscall
    jr $ra

full_print:
    move $t0, $a0       # $t0 = Current HI
    move $t1, $a1       # $t1 = Current LO
    li $t2, 0           # Digit counter (stack depth)

extract_digits:
    # We need to do: (HI:LO) / 10.
    # Since we can't do 64-bit div, we split it into 3 steps.
    
    # 1. Divide HI by 10
    divu $t0, 10
    mflo $t3            # $t3 = New HI Quotient
    mfhi $t4            # $t4 = Remainder from HI
    
    # 2. Prepare "Upper LO" (16 bits) combined with Remainder from HI
    srl $t5, $t1, 16    # Get top 16 bits of LO
    sll $t4, $t4, 16    # Shift HI-remainder to top 16 bits
    or  $t5, $t5, $t4   # Combine: (rem_hi << 16) | lo_upper
    
    divu $t5, 10
    mflo $t6            # $t6 = Quotient Middle
    mfhi $t7            # $t7 = Remainder Middle
    
    # 3. Prepare "Lower LO" (16 bits) combined with Remainder Middle
    andi $t8, $t1, 0xFFFF # Get bottom 16 bits of LO
    sll  $t7, $t7, 16     # Shift Mid-remainder to top
    or   $t8, $t8, $t7    # Combine: (rem_mid << 16) | lo_lower
    
    divu $t8, 10
    mflo $t9            # $t9 = Quotient Low
    mfhi $s0            # $s0 = Final Remainder (The Digit!)
    
    # Push digit to stack
    addi $sp, $sp, -4
    sw $s0, 0($sp)
    addi $t2, $t2, 1    # Increment count
    
    # Reconstruct the 64-bit Quotient for next iteration
    # New HI = $t3
    # New LO = ($t6 << 16) | $t9
    move $t0, $t3       
    sll  $t6, $t6, 16
    or   $t1, $t6, $t9
    
    # Check if value is 0 (Both HI and LO are 0)
    or $t3, $t0, $t1
    bnez $t3, extract_digits

print_loop:
    lw $a0, 0($sp)      # Pop digit
    addi $sp, $sp, 4
    li $v0, 1           # Print int
    syscall
    
    addi $t2, $t2, -1
    bnez $t2, print_loop
    
    jr $ra