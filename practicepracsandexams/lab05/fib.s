# MIPS assembler to compute Fibonacci numbers

   .data
msg1:
   .asciiz "n = "
msg2:
   .asciiz "fib(n) = "
errormsg:
	.asciiz "n must be > 0 "	
   .text

# int main(void)
# {
#    int n;
#    printf("n = ");
#    scanf("%d", &n);
#    if (n >= 1)
#       printf("fib(n) = %d\n", fib(n));
#    else {
#       printf("n must be > 0\n");
#       exit(1);
#    }
#    return 0;
# }

   .globl main
main:
   # prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   # function body
   la   $a0, msg1       # printf("n = ");
   li   $v0, 4
   syscall

   li   $v0, 5          # scanf("%d", &n);
   syscall
   move $a0, $v0

   # ... add code to check (n >= 1)
   # ... print an error message, if needed
   # ... and return a suitable value from main()
   ble $a0, 0, error    #if(n<1) error();

   jal  fib             # $s0 = fib(n);
   nop
   move $s0, $v0

   la   $a0, msg2       # printf((fib(n) = ");
   li   $v0, 4
   syscall

   move $a0, $s0        # printf("%d", $s0);
   li   $v0, 1
   syscall

   li   $a0, '\n'       # printf("\n");
   li   $v0, 11
   syscall

   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra

# int fib(int n)
# {
#    if (n < 1)
#       return 0;
#    else if (n == 1)
#       return 1;
#    else
#       return fib(n-1) + fib(n-2);
# }

fib:
   # prologue
   # ... add a suitable prologue
   bgt $a0, 1, recursion ##if n is greater than 1 perform the recursion this will also cover both cases of n<1 and n = 1 due to next line
   move $v0, $a0		 ##else return is = n (1,0 have return 1,0 respectively)
   jr $ra				 ##return

   recursion:
   sub $sp, $sp, 12 	##allocating storage on stack for 3 different returns
   sw $ra, ($sp)   	##store the return address in the sack
   sw $s0, 4($sp)   	##store the value n in the stack 		
   move $s0, $a0		##move a0 into s0 to keep track of n

   addi $a0, $a0, -1	#n = n - 1
   jal fib   			#recursively call f(n-1)
   sw $v0, 8($sp)		#store the return in the stack

   addi $a0, $s0, -2    #n = n - 2
   jal fib          	#recursively call f(n-2)
   lw $t0, 8($sp)		#load into a temporary register the return from f(n-1) to use for addition
   add $v0, $t0, $v0	#f(n-1) + f(n-2) stored into v0

   # epilogue
   # ... add a suitable epilogue
   lw $s0, 4($sp)  		#restore values from the stack into registers
   lw $ra, ($sp)
   add $sp, $sp, 12		#restoring the stack to it's original state
   jr $ra				#return

   #printing error message when integer inserted is less than or equal to 1
   Error:
   la $a0, errormsg #printf("%s",errormsg)
   li $v0, 4
   syscall
   jr $ra