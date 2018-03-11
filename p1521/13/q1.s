# COMP1521 Practice Prac Exam #1
# int lowerfy(char *src, char *dest)

   .text
   .globl lowerfy

# params: src=$a0, dest=$a1
lowerfy:
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
   li $s0, 0
   li $s1, 0 
   # add code for your lowerfy function here
   Loop:
      add $t0, $s0, $a0
      add $t1, $s0, $a1
      lb $t0, ($t0)
      beqz $t0, exit
      bge $t0, 'A', lower1
      sb $t0, ($t1)
      add $s0, $s0, 1

   j Loop

   lower1:
         ble $t0, 'Z', lower2
         sb $t0, ($t1)
         add $s0, $s0, 1
         j Loop
   lower2:   
      add $t0, $t0, 'a'
      sub $t0, $t0, 'A'
      sb $t0, ($t1)
      add $s0, $s0, 1
      add $s1, $s1, 1
      j Loop

   exit:
      sb $t0, ($t1)
      move $v0, $s1
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

