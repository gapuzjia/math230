# Jia Gapuz
# MATH 230
# Instructor: Professor Mimi Rasky
# Date: 5/17/2024
# Lab #9

#List of registers:
#---------------------------
#$s0 = &fileName / &string
#$s1 = temp value
#$s2 = 0xD / ascii of CR char
#$s3 = 0xA / ascii of LF char
#$s4 = temp value
#$s5 = M
#$s6 = hashVal
#$s7 = g
#$t2 = current char in string
#$v1 = function return value

.data
	filename: .space 60
	buffer: .space 1024
	prompt: .asciiz "Enter your filename: "
	message: .asciiz "\nThe hash value of \n"
	is: .asciiz " is "

.text
	#load registers with values
	addi $s1, $zero, 0 #temp value
	addi $s2, $zero, 13 #CR
	addi $s3, $zero, 10 #LF
	addi $s4, $zero, 0 #temp value
	addi $s5, $zero, 1009 #M
	addi $s6, $zero, 0 #hashVal
	addi $s7, $zero, 0 #g
	addi $t2, $zero, 0 #current char
	
	
	li $v0, 4 #service 4 is to print prompt for filename
	la $a0, prompt
	syscall 
	
	li $v0, 8 #service 8 is to read a string
	la $a0, filename #put the address into the $a0 register
	li $a1, 60 #load desired number of char to read in
	syscall
	
	la $s0, filename #load filename into s0
	
CLEAR:
	lb $t2, 0($s0) #load current char of string
	beq $t2, $zero, SET #if current char in string 1 is a zero (null char), jump to SET
	beq $t2, $s3, SET #is the current char = 10? (a LF), if true jump to SET
	beq $t2, $s2, SET #is the current char = 13? (a CR), if true jump to SET
	addi $s0, $s0, 1 #update the address of the current char
	j CLEAR
	
SET:
	sb $zero, 0($s0) #replace current char with a 0
	
	#code falls through if a LF or CR was reached
	
	li $v0, 13 #service 13 is to open the file
	la $a0, filename #load address of filename
	li $a1, 0
	li $a2, 0
	syscall
	
	move $s0, $v0 #save file descriptor
	
	li $v0, 14 #service 14 is to read file
	move $a0, $s0 #load address of filename into a0
	la $a1, buffer #load address to space
	li $a2, 1024 #file size to read in
	syscall
		
	li $v0, 16 #close file
	syscall
	
	la $a1, buffer #move string to $a0 for function call

	jal hash #call hash function
	#v1 will contain hash value when returned
	
	li $v0, 4 #service 4 is to print "The hash value of "
	la $a0, message
	syscall
	
	li $v0, 4 #service 4 is to print the string
	la $a0, buffer
	syscall
	
	li $v0, 4 #service 4 is to print "is"
	la $a0, is
	syscall
	
	li $v0, 1 #service 1 is to print the hash value
	move $a0, $v1 #v1 contains hash value from function return
	syscall
	
	li $v0, 10 #exit gracefully
	syscall

hash:
	#a1 - &string[i]
	#s1 - temp val
	#s2 - CR
	#s3 - LF
	#s4 - temp value for hashval << 4
	#s5 - M
	#s6 - hashVal
	#s7 - g
	
	WHILE:
		lb $s1, 0($a1) #get current char
		beq $s1, $zero, QUIT #if current char is a 0, end of string, QUIT
		beq $s1, $s2, SKIP #if current char is a CR, ignore, jump to SKIP
		beq $s1, $s3, SKIP #if current char is a LF, ignore, jump to SKIP
		
		sll $s4, $s6, 4 #hashval << 4
		add $s6, $s4, $s1 #hashVal = (hashval << 4) + current char
		
		addi $s4, $zero, 15 #load F into s4
		sll $s4, $s4, 28 #shift left to get 0xF0000000
		
		and $s7, $s6, $s4 #g = hashVal & 0xF0000000
		bne $s7, $zero, IF #if g != 0, jump to IF
		j RESUME
		
		IF:
			srl $s1, $s7, 23 #g >> 23
			xor $s6, $s6, $s1  # hashVal ^= g >> 23
		

	RESUME:
		nor $s1, $s7, $s7 #~g
		and $s6, $s6, $s1 
		
		#fall through, increments and returns to loop
		
	SKIP:
		addi $a1, $a1, 1 #increment address of string
		j WHILE #jump back into loop
		
		
	QUIT:
		div $s6, $s5 #hashval / M
		mfhi $v1 #move remainder to v1
		
		jr $ra
		
		

