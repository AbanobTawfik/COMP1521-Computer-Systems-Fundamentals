# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by Abanob Tawfik z5075490, August 2017

#################################################
#           Data used for the program	        #
#################################################
.data										
main_ret_save: .space 4						    
msg1:           								
.asciiz "# Iterations: "				    
msg2:						   					
.asciiz "=== After iteration "			    
msg3:						                    
.asciiz " ==="								
newline:										
.asciiz "\n"				                					
biton:											
.byte 1										
bitoff:											
.byte 0									

#################################################

.text
.globl main
main:
    sw   $ra, main_ret_save
    lb $t7, biton						#check variables to see if bit is 0 or 1
    lb $t8, bitoff
    la $a0, msg1	
    li $v0, 4	                        #printf("# Iterations: \n"); in c
    syscall

    li $v0, 5	                        #scanf("%d",&n) store result in v0
    syscall
    move $t0, $v0	                    #store the return from scanf into t0 register to use for loop

    jal EnterLoop

end_main:
    lw   $ra, main_ret_save
    jr   $ra
    li $v0, 10			                #return EXIT_SUCCESS
    syscall
###############################################
#		EXTRA								  #																												
#		FUNCTIONS							  #																									 
###############################################
EnterLoop:
    #prologue 
    sub $sp, $sp, 24                    #storing return address into the stack
    #loop counters
    sw $s4, 20($sp)
    sw $s3, 16($sp)
    sw $s2, 12($sp)
    #N and N-1
    sw $s1, 8($sp)
    sw $s0, 4($sp)
    #return address
    sw $ra, ($sp)

    la $a3, board 					    #storing the address of the boards into these registers (higher end registers to avoid overwrite issues)
    la $s8, newBoard

    li $s0, 0			                #s0 counter for iterations

    lw $s1, N  	                        #s1 = N

    lw $s2, N           
    sub $s2, $s2, 1	                    #s2 = N-1
    j loop1

loop1:
    bge $s0, $t0, exit                  #for(int n = 1;n<=maxiters;n++ )	
    addi $s0, $s0, 1 	                #n = n + 1
    li $s3, 0                           #i = -1 (counter) start -1 because you add 1 at the start already
    j loop2			

loop2:
    bge $s3, $s1, display	            #for(int i = 0; i<N;i++) when finished looping print board 
    move $a1, $s3		                #store i as an arguement for neighbours
    addi $s3, $s3, 1		            #i = i+1
    li $s4, 0                           #j = 0 (counter)
    j loop3

loop3:
    bge $s4, $s1, loop2	                #for(int j = 0;j<N;j++) when finished looping this go back to loop 2
    move $a2, $s4                       #store j as an arguement for neighbours 
    jal neighbours		                #perform function neighbours
    move $s7, $v0		                #move the result from neighbours into s7, s7 = nn

                                        ##getting index [i][j] for board
                                        #since it is a row major representation
                                        #index of board[i][j] = base adress of board + (rowindex*colsize + colindex)*datasize
                                        #t4 is the offset
    sub $s3, $s3, 1
    mul $t4, $s3, $s1
    add $s3, $s3, 1						
    add $t4, $t4, $s4


    add $t6, $a3, $t4				    #t6 contains address of the board at index i,j
    lb $t5, ($t6)					    #store into $t5, the content of board in memory t6

    lb $s5, biton                       #s5 contains bit - 1
    lb $s6, bitoff                      #s6 contains bit - 0

    beq $t5, $t7, verify                #if(byte = 1) go to checks
    beq $s7, 3, newboardone             #if(neighbours = 3 && byte = 0 ) i.e reproduction from dead cell turn bit on
    j newboardzero                      #else keep cell dead

verified:                        
                                        #if jumped to the verify condition incremenet the counter and jump to loop
    addi $s4, $s4, 1		            #j++
    j loop3				
    verify:
    blt $s7, 2, newboardzero	        #if(nn<2) ->set byte 0
    beq $s7, 2,  newboardone	        #if (nn = 2) ->set byte 1
    beq $s7, 3, newboardone		        #if (nn = 3 ) ->set byte 1
    bgt $s7, 3, newboardzero            #overpopulation if(n>3) ->set byte 0
    j verified               

newboardone:
    add $s8, $s8, $t4			        #s8 contains our newBoard address
    sb $s5, ($s8)			            #add offset to our board address
    sub $s8, $s8, $t4			        #store a 1 		into the address
    j verified				            #revert offset so unchanged

newboardzero:
    add $s8, $s8, $t4
    sb  $s6, ($s8)                      #same as newboardone except store a 0
    sub $s8, $s8, $t4
    j verified

exit:
    #prologue
    #restoring stack to original state
    lw $s4, 20($sp)
    lw $s3, 16($sp)
    lw $s2, 12($sp)
    lw $s1, 8($sp)
    lw $s0, 4($sp)
    lw $ra, ($sp)
    add $sp, $sp, 24
    j end_main


neighbours:
    #epilogue
    sub $sp, $sp, 16
    sw $ra, 12($sp)
    sw $s7, 8($sp)
    sw $s6, 4($sp)
    sw $s5, ($sp)
    li $s7, 0                           #s7 will contain our return value nn
    li $s5, -1                          #counter for loop 1 need to keep track of
    li $t1, 1			                #comparing counter with t1 upper limits
    j neighbourloopouter


neighbourloopouter:
    bgt $s5, $t1, exit2	                #for(int x = -1;x<=1;x++)       
    add $t2, $a1, $s5                   #t2 = i+x   

    addi $s5, $s5, 1
    li $s6, -1         	                #start counter for inner loop (y)		
    j neighbourloop

neighbourloop:
    bgt $s6, $t1, neighbourloopouter 	#for(int y = -1;y<=1;y++)

    add $t3, $a2, $s6		            #t3 = j+y 


    blt $t2, 0, continue				#if(i+x<0 || i+x>N-1) continue;
    bgt $t2, $s2, continue  


    blt $t3, 0, continue 				#if(j+y<0||j+y>N-1) continue
    bgt $t3, $s2, continue


    sub $s5, $s5, 1                     #if(x==0) -> check 1 (sub 1 add 1 since we increment in outer loop for x)
    beqz $s5, check1                    #if(x==0&&y==0)continue
    add $s5, $s5, 1

                                        
                                        #calculate address of board[i+x][j+y] ROW MAJOR
                                        #address = base address + (rowindex*colsize + colindex)* dataisze
    mul $t4, $t2, $s1                   #rowindex*colsize in t5
    add $t4, $t4, $t3                   #+ colindex (datasize is 1 becuse byte) so no need to mul again       


    add $t4, $a3, $t4                   #t4 contains the address of board[i+x][j+y]


    lb $t6, ($t4)                       #load the byte in the address t4 into t6
    beq $t6, $t7, incremenet	        #if(t6 = 1 a.k.a byte on) (t7 = 1) -> increment return
    addi $s6, $s6, 1                    #else add 1 to counter and jump to loop again
    j neighbourloop


continue:
    addi $s6, $s6, 1                    #add 1 to inner loop counter and jump to loop
    j neighbourloop

check1:
    add $s5, $s5, 1                     #if our x = 0 add 1 back to x to revert change (sub from before add wont execute if goes to here)
    beqz $s6, continue                  #if(y==0)->continue i.e condition total is (x==0&&y==0)->continue
    j check2                            #else check the value inside register

check2:
                                        #checking value inside the register
    mul $t4, $t2, $s1                   #rowindex*colsize in t4
    add $t4, $t4, $t3                   #+ colindex (datasize is 1 becuse byte) so no need to mul again                    

    add $t4, $a3, $t4                   #t4 contains the address of board[i+x][j+y]
    lb $t6, ($t4)		
    beq $t6, $t7, incremenet 	        #if t7 i.e value in board[i+x][j+y] = 1 incremenet our return
    j continue		                    #else jump to continue

incremenet:
    add $s7, $s7, 1                     #add 1 to our return then continue through loop
    j continue


exit2:
    #prologue
    move $v0, $s7                       #putting the return into v0
    #restoring stack to original 
    lw $s5, ($sp)
    lw $s6, 4($sp)
    lw $s7, 8($sp)
    lw $ra, 12($sp)	
    add $sp, $sp, 16
    jr $ra                              #jump back to the call after jal neighbours


display:
    li $t1, 0                           #counter for our loop


    la $a0, msg2
    li $v0, 4			                #printf("=== after iteration ")
    syscall

    move $a0, $s0
    li $v0, 1			                #printf(" %d "iterarion number)
    syscall

    la $a0, msg3
    li $v0, 4                           #printf(" ====")
    syscall 	
    j displayloop



displayloop:
    la $a0, newline                     #printf("\n")
    li $v0, 4              
    syscall	
    bge $t1, $s1, loop1                 #if(t1>N)->loop1 restart whole proccess



    add $t1, $t1, 1                     #increment counter and load the counter for inner loop 
    li $t2, 0

    j displayloop2                      #jump to inner loop


displayloop2:

    bge $t2, $s1, displayloop
    sub $t1, $t1, 1						#since counter is at 1 (add $t1 $t1 1 above) subtract 1 for calculation purpose
    
    mul $t3, $s1, $t1                   #t1 = row index, t2 = col index, S1 contains N
    add $t3, $t3, $t2					#t3 contains offset
                                        #offset = (rowindex*N + colindex))
    add $t4, $t3, $a3					#t4 contains address of old board (Base address of old board is a3)
    add $t5, $t3, $s8					#t5 contains address of new board (base address of new board is s8)
    add $t1, $t1, 1				 		#add 1 back to counter 1 to restore it to previous state

    lb $t6, ($t5)                       #t6 is the byte at the newboard with offset t3

    add $a3, $a3, $t3                   #since we are storing the byte of newboard + offset in oldboard + offset
                                        #add offset to old board
    sb $t6, ($a3)                       #store the byte into old board
                                        
    sub $a3, $a3, $t3                   #restore address of old board from the offset addition

    beq $t6, $t7, hash                  #if t6 = 1 a.k.a byte is on go to printhash
    beq $t6, $t8, dot                   #if t6 = 0 a.k.a byte is off go to printdot.

afterif:

    add $t2, $t2, 1	                    #add 1 to the inner loop counter and jump back to start of loop
    j displayloop2

hash:
    li $v0, 11
    la $a0, '#'                         #putchar('#')
    syscall
    j afterif

dot:
    li $v0, 11
    la $a0, '.'                         #putchar('.')
    syscall
    j afterif
