# COMP1521 Practice Prac Exam #1
# (int dp, int n) dotProd(int *a1, int n1, int *a2, int n2)

   .text
   .globl dotProd

# params: a1=$a0, n1=$a1, a2=$a2, n2=$a3
dotProd:
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
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...
   li $s0, 0                  #sum in here sum = 0
   li $s3, 0                  #loop counter

   checkL:
   ble $a1, $a3, l1
   ble $a3, $a1, l2

   l1:
      la $s1, ($a1)
      j entrance
   l2:
      la $s1, ($a3)
      j entrance

   entrance:
      bge $s3, $s1, exit
      #workout offset for array 1 and 2
      mul $t0, $s3, 4

      add $t1, $t0, $a0
      lw $t1, ($t1)

      add $t2, $t0, $a2
      lw $t2, ($t2)

      mul $t3, $t1, $t2
      add $s0, $s0, $t3 

      add $s3, $s3, 1
      j entrance

   # add code for your dotProd function here

# epilogue
   exit:
   # if you saved more than two $s? registers
   # add the code to restore them here
   move $v0, $s0
   move $v1, $s1

   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

