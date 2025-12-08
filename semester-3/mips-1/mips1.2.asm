.data
value: .word 0, 0, 0
message1: .asciiz "RESULT\n"
message2: .asciiz "addition = "
.text
.globl main
main:
la $t0,value
li $v0,5 # Δώσε τον πρώτο αριθμό
syscall
sw $v0,0($t0) # Αποθήκευσε τον αριθμό στη θέση value
li $v0,5 # Δώσε τον δεύτερο αριθμό
syscall
sw $v0,4($t0) # Αποθήκευσε τον αριθμό στη θέση value+4
lw $t1,0($t0) # Φόρτωσε τον πρώτο αριθμό στον $t1
lw $t2,4($t0) # Φόρτωσε τον δεύτερο αριθμό στον $t2
add $t3,$t1,$t2 # Πρόσθεσε τους δύο αριθμούς
# και βάλε το άθροισμα στον $t3
sw $t3,8($t0) # Αποθήκευσε το άθροισμα στη θέση value+8
li $v0,4 # Εμφάνισε το message1
la $a0,message1
syscall
li $v0,4 # Εμφάνισε το message2
la $a0,message2
syscall
li $v0,1 # Εμφάνισε το άθροισμα
move $a0,$t3
syscall
li $v0,10
syscall # Έξοδος