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
   addi $sp, $sp, -4
   sw 	$s2, ($sp)
   addi $sp, $sp, -4
   sw	$s3, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...

   # add code for your everyKth function here
   li $s0, 0
   li $s1, 0
   lw $s2, ($a0)
   lw $s3, ($a3)
   sub $a1, $a1, 1
   j enterLoop
   enterLoop:
   		bgt $s0, $a1, exit
   		j loop

   loop:
   		rem $t0, $s0, $a2
   		beq $t0, 0,loopfunction
   		add $s0, $s0, 1
   		j enterLoop
   loopfunction:
   		mul $t1, $s0, 4
   		add $t1, $a0, $t1
   		lw $t3, ($t1)

   		mul $t2, $s1, 4
   		add $t2, $a3, $t2

   		sw $t3, ($t2)
   		add $s0, $s0, 1
   		add $s1, $s1, 1
   		j enterLoop
exit:
# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   move $v0, $s1
   lw   $s3, ($sp)
   addi $sp, $sp, 4
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

