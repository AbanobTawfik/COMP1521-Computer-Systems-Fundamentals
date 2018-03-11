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
   li $s0, 0
   li $s1, 0	
Loop:
	bge $s0, $a1, exit
	#calculate offset for the array
	mul $t0, $s0, 4
	add $t0, $t0, $a0
	lw 	$t0, ($t0)
	rem $t1, $t0, 2
	beq $t1, 0, addtoarray
	add $s0, $s0, 1
	j Loop
addtoarray:
	mul $t1, $s1, 4
	add $t1, $t1, $a2
	sw $t0, ($t1)
	add $s1, $s1, 1
	add $s0, $s0, 1
	j Loop 	
   # add code for your rmOdd function here
exit:
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

