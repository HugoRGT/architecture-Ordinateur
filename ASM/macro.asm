# Didier Teifreto Octobre 2021
#####################################
# Afficher un entier imm ou dans un reg
.macro print_int(%int)
	sw $a0,0($sp)
	sw $v0,-4($sp)	
	add $a0,$0,%int # pseudo inst remplacer par add ou addi 
	li $v0,1
	syscall
	lw $a0,0($sp)
	lw $v0,-4($sp)	
.end_macro 
# Afficher une chaine avec adresse 
.macro print_str(%str)
	sw $a0,0($sp)
	sw $v0,-4($sp)	
	la $a0,%str
	li $v0,4
	syscall
	lw $a0,0($sp)
	lw $v0,-4($sp)	
.end_macro 
# Afficher une chaine immédiate
.macro print_str2(%str)
	.data 
	local : .asciiz %str 
	.text
	sw $a0,0($sp)
	sw $v0,-4($sp)
	la $a0,local
	li $v0,4
	syscall
	lw $a0,0($sp)
	lw $v0,-4($sp)
.end_macro 	
# Test deux entiers 
# %int1 : found / %int2 : expect 
.macro testEQ (%FOUND,%EXPECT,%resOK,%resErreur,%score,%increment)
.data
	expect : .asciiz "Attendu:"
	found : .asciiz ",Trouvé:"
	OK : .asciiz "-> OK\n"
	erreur : .asciiz "-> Erreur\n"	
.text
	sw $a0,0($sp)
	sw $a1,-4($sp)
	addi $sp,$sp,-8	
	print_str(expect)
	print_int(%EXPECT)	
	print_str(found)
	print_int(%FOUND)
	add $a0,$0,%EXPECT
	add $a1,$0,%FOUND		
	beq $a0,$a1,pasErreur
	print_str(erreur)
	la $a0,%resErreur
	lw $a1,0($a0)
	addi $a1,$a1,1
	sw $a1,0($a0)
	beq $0,$0,fin	
pasErreur:
	print_str(OK)
	la $a0,%resOK
	lw $a1,0($a0)
	addi $a1,$a1,1
	sw $a1,0($a0)
	la $a0,%score
	lw $a1,0($a0)
	addi $a1,$a1,%increment
	sw $a1,0($a0)			
fin:
	addi $sp,$sp,8		
	lw $a0,0($sp)
	lw $a1,-4($sp)
.end_macro
# %FOUND Adresse / %EXPECT imm
.macro testSTR (%FOUND,%EXPECT,%resOK,%resErreur,%score,%increment)
.data
	expect : .asciiz "Attendu \""
	found : .asciiz "\",Trouvé \""
	OK : .asciiz "\"-> Correct\n"
	erreur : .asciiz "\"-> Erreur\n"	
	resTheo : .asciiz %EXPECT
.text
	sw $a0,0($sp)
	sw $a1,-4($sp)	
	addi $sp,$sp,-8
	print_str(expect)
	print_str(resTheo)	
	print_str(found)
	print_str(%FOUND)
	la $a0,%FOUND
	la $a1,resTheo
	jal cmpstr
	beq $v0,$0,pasErreur
	print_str(erreur)
	la $a0,%resErreur
	lw $a1,0($a0)
	addi $a1,$a1,1
	sw $a1,0($a0)	
	beq $0,$0,fin	
pasErreur:
	print_str(OK)
	la $a0,%resOK
	lw $a1,0($a0)
	addi $a1,$a1,1
	sw $a1,0($a0)
	la $a0,%score
	lw $a1,0($a0)
	addi $a1,$a1,%increment
	sw $a1,0($a0)	
fin:
	addi $sp,$sp,8
	lw $a0,0($sp)
	lw $a1,-4($sp)	
.end_macro

.macro testEQ2 (%FOUND1,%EXPECT1,%FOUND2,%EXPECT2,%resOK,%resErreur)
.data
	expect : .asciiz "Attendu:"
	found : .asciiz ",Trouvé:"
	OK : .asciiz "-> Correct\n"
	erreur : .asciiz "-> Erreur\n"	
	sep : .asciiz ","
.text
	sw $a0,0($sp)
	sw $a1,-4($sp)
	addi $sp,$sp,-8	
	print_str(expect)
	print_int(%EXPECT1)
	print_str(sep)	
	print_int(%EXPECT2)
	print_str(found)
	print_int(%FOUND1)
	print_str(sep)	
	print_str(sep)		
	add $a0,$0,%EXPECT1
	add $a1,$0,%FOUND1		
	bne $a0,$a1,Erreur
	
	print_str(erreur)
	la $a0,%resErreur
	lw $a1,0($a0)
	addi $a1,$a1,1
	sw $a1,0($a0)	
	beq $0,$0,fin	
pasErreur1:

	print_str(OK)
	la $a0,%resOK
	lw $a1,0($a0)
	addi $a1,$a1,1
	sw $a1,0($a0)		
fin:
	addi $sp,$sp,8		
	lw $a0,0($sp)
	lw $a1,-4($sp)
.end_macro
