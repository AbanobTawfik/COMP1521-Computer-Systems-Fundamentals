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
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...
   li $s0, 0
   li $s1, 0
   blt $a1, $a3, len1
   move $v1, $a3
   j Loop
   len1:
   move $v1, $a1

   Loop:
      bge $s0, $v1, exit
      mul $t0, $s0, 4
      add $t1, $a2, $t0
      add $t0, $a0, $t0
      lw $t0, ($t0)
      lw $t1, ($t1)
      mul $t2, $t0, $t1
      add $s1, $s1, $t2

      add $s0, $s0, 1
      j Loop
   exit:
   move $v0, $s1
   # add code for your dotProd function here

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

