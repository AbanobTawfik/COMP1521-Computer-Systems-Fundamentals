# COMP1521 Lab 04 ... Simple MIPS assembler


### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function

   .data   
   .align 2
main_ret_save:
   .word 4
   #creating a word to store the input from user, result will be stored in the return from the factorial function
input:
   .word 4

   .text
   .globl main

main:
	#STORING THE RETURN FROM THE MAIN FUNCTION IN THE RETURN ADRESS
   sw   $ra, main_ret_save

#  ... your code for main() goes here

   # prompt message for picking a number
   li $v0, 4
   #loads message 1 into a0
   la $a0, msg1    # n:
   #prints a0
   syscall

   # ask user for input
   li $v0, 5
   syscall
   #store the value in the word input that we declared
   sw $v0, input

   #loading the register a0 which is arguement register to pass through factorial function
   lw $a0, input
   #call to jump and link to factorial function (aka fatorial() in c)
   jal fac
   #store the result from the function which is fact_ret_save in register v0
   sw $v0, fac_ret_save

   # displaying result message 
   li $v0, 4
   la $a0, msg2    #n!: 
   syscall

   # displaying integer from factorial return save
   li $v0, 1
   lw $a0, fac_ret_save   # n! in decimal (value of n!)
   syscall

   #print a new line
   li $v0, 4
   la $a0, eol
   syscall

   #end of main
   lw   $ra, main_ret_save
   jr   $ra           # return

### fac() function

   .data
   .align 2
fac_ret_save:
   .space 4

   .text

fac:

#store in the return adress fac_ret_save 
   sw   $ra, fac_ret_save

#  ... your code for fac() goes here
   #store 8 bits in the stack for 2 stack registers (saved registers)
   subu $sp, $sp, 8
   #store the stack pointer which will have our return value into the return adress
   sw $ra, ($sp)
   #store the saved point 4 bytes across the stack from the previous stack pointer (local register used for factorial function)
   sw $s0, 4($sp)
   #base case
   li $v0, 1
   #if the arguement is = 0 then the function is complete when we pass in a0 which will be reduced by 1 each time compare to 0
   beq $a0, 0, complete

   #move into the saved pointer the arguement passed in if its not = 0
   move $s0, $a0
   #subtract 1 and store this in the arguement register
   sub $a0, $a0, 1
   #recursively call the factorial function till base case is reached
   jal fac

   #once base case is reached it will multiply the save register s0 with the value returned from v0 when recursion is unwinding sort of like
   #f(f(f(f(f(f(x)))))) in c
   mul $v0, $s0, $v0

   complete:
   #load our values from the stack 
   lw   $ra, ($sp)
   lw $s0, 4($sp)
   ##restore the 8 bits to the stack we subtracted with subu to reinitialise the stack
   addu $sp, $sp, 8
   jr   $ra            # return ($v0)
