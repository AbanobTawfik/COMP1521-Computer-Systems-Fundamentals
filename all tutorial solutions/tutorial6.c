1. 
Version 1 minimises lines
lw $t0, x
lw $t1, y
lw $t2, z

mul $t3, $t0, $t0
mul $t4, $t1, $t1
mul $t5, $t0, $t1

add $t6, $t3, $t4
sub $t6, $t6, $t5
mul $t6, $t6, $t2

move $v0, $t6

version 2 minimises registers used

lw $t0, x
lw $t1, y
lw $t2, z

mul $t3, $t0, $t1
mul $t0, $t0, $t0
mul $t1, $t1, $t1
add $t0, $t0, $t1
sub $t0, $t0, $t3
mul $t0, $t0, $t2

move $v0, $t0 

2. 
$s0 = s
li $t0, 0

enterLoop:
	lb $(t1), $s0
	beqz $t1, exit
	beq $t1, ' ', exit
	add $s0, $s0, 1
	j enterLoop
exit:
	j $ra


3.
if:
	lw $t0, x
    lw $t1, y
    li $t2, 100
    div $t2, $t2, x
    beqz $t0, condition2
    blt $t1, $t0, s1
    j $s2
condition2:
	li $t5, 5
	bgt $t2, 5, s1
	j s2
s1:
 j $ra
s2:
 jr $ra

4. 	
switch:	
  	beq $s0, 1, case1r
	beq $s0, 2, exit
	beq $s0, 3, case3r
	beq $s0, 4, case4r
	beq $s0, 5, case5s
	beq $s0, 6, case6r
	li $s1, 0

case1r:
	li $s1, 5
	j exit
case3r:
	add $s1, $s0, 1
	j exit
case4r:
	mul $s1, $s0, $s0
	j exit
case5s:
	li $s1, 99
	j case6r
case6r:
	add $s1, $s1, 1
	j exit	
exit:
    j $ra

5.
   .data
array:
   .word  1, 4, 3, 7, 5, 8, 9, 2, 8, 6
size:
   .word 10

   .text
   la   $a0, array
   lw   $a1, size
   jal  max	
max:
#epilogue for storing values in the frame
   sub $sp, $sp, 4
   sw  $ra, $sp
   sub $sp, $sp, 4
   sw  $s0, $sp
   sub $sp, $sp, 4
   sw  $s1, $sp
   sub $sp, $sp, 4
   sw  $s2, $sp

   li $t0, 0
   lw $s0, ($a0)
   lw $s1, ($a1)

   lw $s2, ($a1)
   findMax:
   bge $t0, $s1, exit
   add $t1, $s0, $t0
   lw $t1, ($t1)
   bgt $t1, $s1, updateMax
   add $t0, $t0, 1
   j findMax

updateMax:
   sw $t1,($s2)
   add $t0, $t0, 1
   j findMax 

exit:
   move $v0, $s2
   add $sp, $sp, 4
   lw  $ra, $sp   
   add $sp, $sp, 4
   lw  $s0, $sp
   add $sp, $sp, 4
   lw  $s1, $sp
   add $sp, $sp, 4
   lw  $s2, $sp

   jr $ra

 prod:
 	#epilogue for storing values in the frame
   sub $sp, $sp, 4
   sw  $ra, $sp
   sub $sp, $sp, 4
   sw  $s0, $sp
   sub $sp, $sp, 4
   sw  $s1, $sp
   sub $sp, $sp, 4
   sw  $s2, $sp

   lw $t0, ($a0)
   mul $t0, $t0, $a1
   mul $t0, $t0, $a2
   mul $t0, $t0, $a3
   lw $t1, 4($ra)
   mul $v0, $t0, $t1

   add $sp, $sp, 4
   lw  $ra, $sp   
   add $sp, $sp, 4
   lw  $s0, $sp
   add $sp, $sp, 4
   lw  $s1, $sp
   add $sp, $sp, 4
   lw  $s2, $sp
   j $ra

   store arguements onto stack and use htem from the stack