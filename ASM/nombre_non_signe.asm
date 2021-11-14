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
	sll $t3,$t3,4
	jal forDigit
	sb $v0,0($sp)
	add $a1,$a1,1
	sw $t3,24($sp)
	addi $t2,$t2,1
	j loop1
	
exit:
	addi $a1,$a1,'\0'
	jr $ra
	
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
	addi $sp,$sp,16
	lw $a0,0($sp)
	lw $a1,-4($sp)	
	lw $ra,-8($sp)
	lw $t0,-12($sp)	
	jr $ra
