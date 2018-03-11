# COMP1521 Practice Prac Exam #1
# int everyKth(int *src, int n, int k, int*dest)

   .text
   .globl everyKth

# params: src=$a0, n=$a1, k=$a2, dest=$a3
everyKth:
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
Loop:
   bge $s0, $a1, exit
   rem $t0, $s0, $a2
   beq $t0, 0, addto
   add $s0, $s0, 1
   j Loop
addto:
   mul $t0, $s0, 4
   add $t0, $t0, $a0
   lw $t0, ($t0)
   mul $t1, $s1, 4
   add $t1, $t1, $a3
   sw $t0, ($t1)
   add $s0, $s0, 1
   add $s1, $s1, 1
   j Loop
exit:
   move $v0, $s1
   # add code for your everyKth function here

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

