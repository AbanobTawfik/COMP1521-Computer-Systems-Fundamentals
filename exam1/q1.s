# COMP1521 Practice Prac Exam #1
# int rmOdd(int *src, int n, int*dest)

   .text
   .globl rmOdd

# params: src=$a0, n=$a1, dest=$a2
rmOdd:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...
 li $s0, 0                              #load into register s0 counter for our loop to scan through array
  li $s1, 0                              #load into register s1 counter for updating our destination array

  j enterLoop
  
  enterLoop:
  #entrance for our loop contains condition to exit
  sub $t9, $a1, 1
  bgt $s0, $t9, exit                #if i>n exit
  j mainLoop                     #jump to main part of the loop

  mainLoop:
  li $t4, 2
  #calculate value at array index
  mul $t1, $s0, 4                     #offset for our first array is in register t0
  add $t2, $a0, $t1                  #add offset to our array 
  lw $t5, ($t2)                     #retrieve value from that
  and $t3, $t5, 1
  beq $t3,0,addarray
  add $s0, $s0, 1                #add 1 to counter
  j enterLoop

  addarray:
  #add the value to the array
  mul $t1, $s1, 4
  add $t2, $a2, $t1
  sw $t5, ($t2)
  add $s1, $s1, 1                      #add 1 to counter
  add $s0, $s0, 1                #add 1 to counter
  j enterLoop
  
  
  exit:
    move $v0, $s1
   # add code for your rmOdd function here

# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

