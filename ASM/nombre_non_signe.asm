#Didier Teifreto Octobre 2021
forDigit:
#$a0 : digit valide 
#$v0 : caractère correspondant
	# A écrire 
	addi $v0 ,$a0 ,-9
	blez $v0 ,fin
	addi $v0 ,$v0 ,7
fin:
	addi $v0,$v0 ,0x39 # ’9’
	jr $ra	
digit:
#$a0 : caractère valide
#$v0 : digit 
	# A écrire
	li $v0,0
	addi $v0,$a0,-0x39
	blez $v0,fin2
	addi $v0 ,$v0 ,-7
fin2:
	addi $v0,$v0,9
	jr $ra	

toHexString:
# $a0 :nombre non signe 
# $a1 : adresse chaine de caractères
	sw $a0,0($sp)
	sw $a1,-4($sp)
	sw $ra,-8($sp)
	sw $t0,-12($sp)
	sw $t1,-16($sp)	
	sw $v0,-20($sp)	
	addi $sp,$sp,-24
	# A écrire
	li $t2,0
loop1:
	bgt $t2,7,exit
	lw $t3,24($sp)
	
	srl $a0,$t3,28
	jal forDigit
	sb $v0,0($a1)
	add $a1,$a1,1
	
	sll $t3,$t3,4
	sw $t3,24($sp)
	
	addi $t2,$t2,1
	j loop1
	
exit:
	
	addi $sp,$sp,24
	lw $a0,0($sp)
	lw $a1,-4($sp)	
	lw $ra,-8($sp)
	lw $t0,-12($sp)
	lw $t1,-16($sp)	
	lw $v0,-20($sp)	
	jr $ra
	
toBinaryString:
# $a0 : nombre entier
# $a1 :adresse chaine de caractère 
	sw $a0,0($sp)
	sw $a1,-4($sp)	
	sw $t0,-8($sp)
	sw $t1,-12($sp)	
	addi $sp,$sp,-16
	# A écrire
	li $t2,0
loop2:
	bgt $t2,31,exit2
	lw $t3,16($sp)
	srl $a0,$t3,31
	addi $a0,$a0,0x30
	sb $a0,0($a1)
	add $a1,$a1,1
	sll $t3,$t3,1
	sw $t3,16($sp)
	addi $t2,$t2,1
	j loop2
	
exit2:

	addi $sp,$sp,16
	lw $a0,0($sp)
	lw $a1,-4($sp)	
	lw $t0,-8($sp)
	lw $t1,-12($sp)	
	jr $ra

toUnsignedString:
# $a0 : nbre entier non signe 
# $a1: adresse du chaine de caractères 
# $a2: base valide  
	sw $a0,0($sp)
	sw $a1,-4($sp)
	sw $ra,-8($sp)
	sw $v0,-12($sp)	
	addi $sp,$sp,-16	
	# A écrire
	#$t2 position
	#$t3 nombre
	#$t4 nombre1
	#$t5 modulo
	li $t2,0
	lw $t4,16($sp)
	
doWhile1:
	lw $t3,16($sp)
	addiu $t2,$t2,1
	divu $t3,$t3,$a2
	mflo $t3
	sw $t3,16($sp)
	beq $t3,$zero,next
	j doWhile1

next:
	addu $a1,$a1,$t2
	sb $0,0($a1)
	
doWhile2:
	addiu $t2,$t2,-1
	divu $t4,$t4,$a2
	mfhi $t4
	move $a0,$t4
	jal forDigit
	sb $v0,-1($a1)
	mflo $t4
	sw $t4,16($sp)
	addiu $a1,$a1,-1
	bne $t4,$zero,doWhile2
        
	addi $sp,$sp,16			
	lw $a0,0($sp)
	lw $a1,-4($sp)
	lw $ra,-8($sp)
	lw $v0,-12($sp)	
	jr $ra	

	
parseUnsigned:
# $a1 : adresse chaine de caracteres valide
# $a2 : base valide 
# $v0 : nombre non signe
	sw $a0,0($sp)
	sw $a1,-4($sp)
	sw $ra,-8($sp)
	sw $t0,-12($sp)
	addi $sp,$sp,-16
	# A écrire
	lw $t1,0 #position -- 28
	lw $t2,0 #resultat -- 24
	lw $v0,0
while:
	addu $a1,$a1,$t1
	beq $a1,$0,quit
	move $t2,$v0
	move $a0,$a1
	jal digit
	multu $t2,$a2
	mflo $t2
	addu $t2,$t2,$v0
	sw $t2,0($v0)
	addiu $t1,$t1,1
	b while
quit:

	addi $sp,$sp,16
	lw $a0,0($sp)
	lw $a1,-4($sp)	
	lw $ra,-8($sp)
	lw $t0,-12($sp)	
	jr $ra
