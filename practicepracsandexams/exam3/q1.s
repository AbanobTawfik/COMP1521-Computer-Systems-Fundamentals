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

   # add code for your lowerfy function here
   li $s0, 0
   li $s1, 0
   enterenterLoop:
      #find offset of the char array
      add $t0, $s0, $a0
      add $t2, $s0, $a1
      lb $t1, ($t0)
      add $s0, $s0, 1
      j enterLoop
   enterLoop:
      beq $t1, 0, exit
      j loop

   loop:
      bge, $t1, 'A', condition1
      j loopfunction

   condition1:
      ble, $t1, 'Z',lowerit
      j loopfunction

   lowerit:
      sub, $t1, $t1, 'A'
      add, $t1, $t1, 'a'
      add, $s1, $s1, 1
      j loopfunction
   loopfunction:
      sb $t1, ($t2)
      j enterenterLoop
exit:
#null terminate the end of our destination
   sb $t1, ($t2)
# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   move $v0, $s1
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

