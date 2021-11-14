#Didier Teifreto Octobre 2021
.include "macro.asm"
.data
	resOK : .word 0
	resErreur: .word 0
	score : .word 0
	tabRes : .space 33
	
	parseInt1 : .asciiz "1123713025"
	parseInt2 : .asciiz "123"
	parseInt3 : .asciiz "FFFFFFFF"
	parseInt4 : .asciiz "0"
				
.text	
	print_str2("=====================  Test forDigit==========================\n")
	print_str2("1. $a0=6 =>")
	li $a0,6
	jal forDigit
	testEQ($v0,'6',resOK,resErreur,score,1)
	print_str2("2. $a0=0xA =>")
	li $a0,0xA
	jal forDigit
	testEQ($v0,'A',resOK,resErreur,score,1)


	print_str2("========================= Test digit ==========================\n")
	print_str2("1. $a0='6' =>")
	li $a0,'6'
	jal digit
	testEQ($v0,6,resOK,resErreur,score,1)
	print_str2("1. $a0='C' =>")
	li $a0,'C'
	jal digit
	testEQ($v0,12,resOK,resErreur,score,1)	

	print_str2("======================== toHexString  ==========================\n")
	print_str2("1. $a0=0x42FA8001 =>")	
	li $a0,0x42FA8001
	la $a1,tabRes
	jal toHexString
	testSTR(tabRes,"42FA8001",resOK,resErreur,score,1)
	print_str2("2. $a0=0x7B =>")	
	li $a0,0x7B
	la $a1,tabRes
	jal toHexString
	testSTR(tabRes,"0000007B",resOK,resErreur,score,1)
	print_str2("3. $a0=0x80000001 =>")	
	li $a0,0x80000001
	la $a1,tabRes
	jal toHexString
	testSTR(tabRes,"80000001",resOK,resErreur,score,1)	
	print_str2("4. $a0=0x00000000 =>")	
	li $a0,0
	la $a1,tabRes
	jal toHexString
	testSTR(tabRes,"00000000",resOK,resErreur,score,1)
	
	print_str2("================ toBinaryString =============================\n")
	print_str2("1. $a0=0x42FA8001 =>")	
	li $a0,0x42FA8001
	la $a1,tabRes
	jal toBinaryString
	testSTR(tabRes,"01000010111110101000000000000001",resOK,resErreur,score,1)	
	print_str2("2. $a0=0x7B =>")	
	li $a0,0x7B
	la $a1,tabRes
	jal toBinaryString
	testSTR(tabRes,"00000000000000000000000001111011",resOK,resErreur,score,1)
	print_str2("1. $a0=0x800000001 =>")	
	li $a0,0x80000001
	la $a1,tabRes
	jal toBinaryString
	testSTR(tabRes,"10000000000000000000000000000001",resOK,resErreur,score,1)
	print_str2("1. $a0=0 =>")	
	li $a0,0
	la $a1,tabRes
	jal toBinaryString
	testSTR(tabRes,"00000000000000000000000000000000",resOK,resErreur,score,1)

	print_str2("================= toUnsignedString ==========================\n")	
	print_str2("1. $a0=1123713025, $a2=10 =>")	
	li $a0,1123713025
	la $a1,tabRes
	li $a2,10
	jal toUnsignedString
	testSTR(tabRes,"1123713025",resOK,resErreur,score,1)	
	print_str2("2. $a0=123, $a2=10 =>")	
	li $a0,123
	la $a1,tabRes
	li $a2,10
	jal toUnsignedString
	testSTR(tabRes,"123",resOK,resErreur,score,1)
	print_str2("3. $a0=0xFFFFFFFF, $a2=10 =>")	
	li $a0,0xFFFFFFFF
	la $a1,tabRes
	li $a2,10
	jal toUnsignedString
	testSTR(tabRes,"4294967295",resOK,resErreur,score,1)
	print_str2("4. $a0=0, $a2=10 =>")	
	li $a0,0
	la $a1,tabRes
	li $a2,10
	jal toUnsignedString
	testSTR(tabRes,"0",resOK,resErreur,score,1)
	print_str2("======================= parseUnsigned===========================\n")
	print_str2("1. *$a0=1123713025, $a2=10 =>")
	la $a1,parseInt1
	li $a2,10
	jal parseUnsigned
	testEQ($v0,1123713025,resOK,resErreur,score,1)	
	print_str2("3. *$a0=123, $a2=16 =>")
	la $a1,parseInt2
	li $a2,16
	jal parseUnsigned
	testEQ($v0,0x123,resOK,resErreur,score,1)
	print_str2("4. *$a0=FFFFFFFF, $a2=16 =>")
	la $a1,parseInt3
	li $a2,16
	jal parseUnsigned
	testEQ($v0,4294967295,resOK,resErreur,score,1)
	print_str2("5. *$a0=0, $a2=10 =>")
	la $a1,parseInt4
	li $a2,10
	jal parseUnsigned
	testEQ($v0,0,resOK,resErreur,score,1)	

	# Resultat du test.		
	print_str2("Résultat(s) correct(s) :")
	la $a0,resOK
	lw $a0,0($a0)
	print_int($a0)
	print_str2("\nRésultat(s) incorrect(s) :")
	la $a0,resErreur
	lw $a0,0($a0)
	print_int($a0)
	
	print_str2("\n")
	la $a0,score
	lw $a0,0($a0)		
	li $v0,17
	syscall

cmpstr:
	#$a0,$a1
	sw $a0,0($sp)
	sw $a1,-4($sp)	
	sw $t0,-8($sp)
	sw $t0,-12($sp)
	sw $t0,-16($sp)
	addi $sp,$sp,-20		
	lb $t0,0($a0)
	lb $t1,0($a1)
	bne $t0,$t1, cmpstrNEQ
	or $t2,$t0,$t1
	beq $t2,$0,cmpstrEQ
	addi $a0,$a0,1
	addi $a1,$a1,1	
	beq $0,$0,cmpstr
cmpstrNEQ:
	li $v0,1
	beq $0,$0,cmpstrFIN
cmpstrEQ:
	li $v0,0
cmpstrFIN:
	addi $sp,$sp,20	
	sw $a0,0($sp)
	sw $a1,-4($sp)	
	sw $t0,-8($sp)
	sw $t0,-12($sp)
	sw $t0,-16($sp)
	jr $ra		

.include "nombre_non_signe.asm"
