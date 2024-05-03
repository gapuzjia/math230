# register chart
#------------------------------------------------------------
# $a1 : string 1 address
# $a2 : string 2 address
# $a3 : new string address
# $t0 : byte of character to be processed in string1
# $t1 : byte of character to be processed in string2
# $t3 : counter for newString
# $t4 : boolean for conditional statements
# $t5 : holds 10
# $t6 : holds 13
# $s0 : flag for string1 done (1 if reached end of string1, 0 if not)
# $s1 : flag for string2 done (1 if reached end of string2, 0 if not)

.data
string1: .space 30
string2: .space 30
newString: .space 60

prompt1: .asciiz "Enter your first string with no spaces: "
prompt2: .asciiz "Enter your second string with no spaces: "

message3: .asciiz "You entered the following:\n"
message4: .asciiz "Creating new string from your specified inputs...\n"
	

.text
main:

	#put values into registers
	addi $t0, $zero, 0
	addi $t1, $zero, 0
	addi $t2, $zero, 0
	addi $t3, $zero, 0
	addi $t5, $zero 10
	addi $t6, $zero 13
	addi $s0, $zero, 0
	addi $s1, $zero, 0
	la $a3, newString
	
	li $v0, 4 #service 4 is to print prompt for string1
	la $a0, prompt1
	syscall 
	
	li $v0, 8 #service 8 is to read a string
	la $a0, string1 #put the address into the $a0 register
	li $a1, 30 #load desired number of char to read in
	syscall
	
	li $v0, 4 #service 4 is to print prompt for string2
	la $a0, prompt2 #put the address into the $a0 register
	syscall
	
	li $v0, 8 #service 8 is to read a string
	la $a0, string2 #put the address into the $a0 register
	li $a1, 30 #load desired number of char to read in
	syscall
	
	li $v0, 4 #service 4 is to print message
	la $a0, message3 #put the address into the $a0 register
	syscall
	
	li $v0, 4 #service 4 is to print string1
	la $a0, string1 #put the address into the $a0 register
	syscall
	
	li $v0, 4 #service 4 is to print string2
	la $a0, string2 #put the address into the $a0 register
	syscall
	
	la $a1, string1 #put string 1's address into $a0
	la $a2, string2 #put string 2's address into $a1

	
 # STRING1LOOP contains SETLOWERCASE1 and SETTOZERO1
 # which sets the current char of string1 to lowercase or zero, respectively
 # SETLOWERCASE1 also handles the case if the current char is a digit, which is ignored and the loop resumes
 # if the current char in the string is a null character (finished traversing and replacing as needed), 
 # it jumps to STRING2LOOP
STRING1LOOP:
	lb $t0, 0($a1) #load current char of string 1
	beq $t0, $0, STRING2LOOP #if current char in string 1 is a zero (null char), jump to STRING2LOOP
	beq $t0, $t5, SETTOZERO1 #is the current char = 10? (a LF), if true jump to SETTOZERO
	beq $t0, $t6, SETTOZERO1 #is the current char = 13? (a CR), if true jump to SETTOZERO
	slti $t4, $t0, 97 #is $t0 < 97?
	bne $t4, $0, SETLOWERCASE1 #if true, jump to SET LOWERCASE1
	addi $a1, $a1, 1 #update the address of the current char
	j STRING1LOOP
	
SETLOWERCASE1:
	addi $a1, $a1, 1
	slti $t4, $t0, 64 #is $t0 < 64?
	bne $t4, $zero, STRING1LOOP #if yes, then the char is a number, ignore and jump back into loop
	addi $t0, $t0, 32 #add 32 to current char (make lowercase)
	sb $t0, -1($a1) #replace previous char with lowercase since we already incremented
	j STRING1LOOP #jump back into loop
	
SETTOZERO1:
	sb $zero, 0($a1) #replace current char with lowercase
	addi $a1, $a1, 1 #update the address of the current char
	j STRING1LOOP


 # STRING2LOOP contains SETLOWERCASE2 and SETTOZERO2
 # which sets the current char of string2 to lowercase or zero, respectively
 # SETLOWERCASE2 also handles the case if the current char is a digit, which is ignored and the loop resumes
 # if the current char in the string is a null character (finished traversing and replacing as needed), 
 # it jumps to MINGLE
STRING2LOOP:
	lb $t0, 0($a2) #load current char of string 1
	beq $t0, $0, MINGLE #if current char in string 1 is a zero (null char), jump to STRING1DONE
	beq $t0, $t5, SETTOZERO2 #is the current char = 10? (a LF), if true jump to SETTOZERO
	beq $t0, $t6, SETTOZERO2 #is the current char = 13? (a CR), if true jump to SETTOZERO
	slti $t4, $t0, 97 #is $t0 < $97?
	bne $t4, $0, SETLOWERCASE2 #if true, jump to SET LOWERCASE
	addi $a2, $a2, 1 #update the address of the current char
	j STRING2LOOP

	
SETLOWERCASE2:
	addi $a2, $a2, 1
	slti $t4, $t0, 64 #is $t0 < 64?
	bne $t4, $zero, STRING1LOOP #if yes, then the char is a number, ignore and jump back into loop
	addi $t0, $t0, 32 #add 32 to current char (make lowercase)
	sb $t0, -1($a2) #replace previous char with lowercase since we already incremented
	j STRING2LOOP #jump back into loop

SETTOZERO2:
	sb $zero, 0($a2) #replace current char with lowercase
	addi $a2, $a2, 1
	j STRING2LOOP
	#code falls through since a CR or LF was reached

# MINGLE alternates between putting characters from string1 and string2 into newString
MINGLE:
	la $a1, string1 #reset $a1 to beginning of string1
	la $a2, string2 #reset $a2 to beginning of string2


# STRING1DONE and STRING2DONE are the conditions of the while loop
# flags $s0 and $s1 are checked to see if both strings' characters have been added to the string
STRING1DONE:
	bne $s0, $zero, STRING2DONE #is string1 done? if yes, check string 2
	j ADD1 #if not, jump to ADD

STRING2DONE:
	bne $s1, $zero, EXIT #if string 2 is also done, both strings are done, therefore EXIT
	
	
ADD1:
	lb $t0, 0($a1) #load current char of string 1 into $t0
	lb $t1, 0($a2) #load current char of string 2 into $t1
	
	bne $t0, $zero, ADDSTRING1 #if current char for string 1 is not null, jump to ADDSTRING1
	addi $s0, $zero, 1 #if current char for string1 is null, set boolean for string1 done to true (1)
	j ADDSTRING2
	
ADDSTRING1:
	sb $t0, 0($a3) #store current char in new string
	add $a1, $a1, 1 #increment address for string 1
	add $a3, $a3, 1 #increment address for newstring
	
	bne $t1, $zero, ADDSTRING2 #if current char for string 2 is not null, jump to ADDSTRING2
	addi $s1, $zero, 1 #if current char for string2 is null, set boolean for string2 done to true (1)
	

ADDSTRING2:
	bne $t1, $zero, ADD2 #if current char for string 2 is not null, jump to ADD2
	addi $s1, $zero, 1 #if current char for string2 is null, set boolean for string2 done to true (1)
	
ADD2:
	bne $s1, $zero, STRING1DONE #if string 2 is done, jump back up to STRING1DONE
	sb $t1, 0($a3) #store current char in new string
	add $a2, $a2, 1 #increment address of string 2
	add $a3, $a3, 1 #increment address for newstring
	j STRING1DONE #jump back to beginning of loop



EXIT:
	sb $zero, 0($a3) # manually add the null character to the end of newString
	li $v0, 4 #service 4 is to print a string
	la $a0, message4 #put the address into the $a0 register
	syscall
	
	
	li $v0, 4 #service 4 is to print a string
	la $a0, newString #put the address into the $a0 register
	syscall
	
	li $v0, 10 #exit gracefully
	syscall



		
	
	
	
	
	
	
	
	
	
	
	
