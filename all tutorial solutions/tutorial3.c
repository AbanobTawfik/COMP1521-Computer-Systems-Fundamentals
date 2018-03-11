1.
a.
 in the data section of the memory
 size = 4 bytes
 scope -> everywhere
 lifetime -> whole program

b.
 in the stack
 size = 4 bytes
 scope -> main function ONLY
 lifetime -> till main function ends

c. 
 in the stack
 size = 1 bytes
 scope ->main function ONLY
 lifetime -> till main function ends

d.
 in the stack
 size = 10 bytes
 scope ->main function ONLY
 life time -> till main function ends

e. 
 in the data section of the memory
 size = 4 bytes
 scope -> antyhing past the variable, so intf(), main function cannot use e 
 lifetime -> entire program

f.
 in the code section of memory
 size = ?
 scope -> anything after the function declaration (if it's declared above then it can be used throughout the entire program')
 lifetime -> for the entire program execution

g. 
 in the stack
 size -> 4 bytes
 scope -> inside f
 lifetime -> while f is executing

h. 
 in the stack
 size -> 8 bytes
 scope -> inside f
 lifetime -> while f is executing

i.
 in the stack
 size -> 4 bytes
 scope -> inside f
 lifetime -> while f is executing

j. 
 in the heap
 size -> 8 bytes
 scope ->inside f
 lifetime -> up until it is free'd'

 2.  you are free'ing what is inside current and trying to access it's next pointer, while it may work sometimes it is essentially accessing free'd date which leads to seg fault

 3. 16 bit values on machine max out at 32676, and the bit after is the sign bit so in turn it ends up changing the sign bit hence why a negative result
 	a way to solve this is by changing it to unsigned integers which will allow use of the sign bit hence giving 60000

 4. A 0x0013
 	-> 0000000000010011
 	-> 3+16 = 19

 	B 0x0444
 	-> 0000010001000100
 	-> 4 + 64 + 1024 = 1092

 	C 0x1234
 	-> 0001001000110100
 	-> 4 + 16+32 + 512 + 4096 = 4660

 	D 0xffff 
 	-> 1111111111111111
 	-> sign is negative so flip all other bits add 1
 	-> 0000 0000 0000 0000 + 1 = -1

 	E 0x8000
 	-> 1000000000000000
 	->sign is negative so flip all other bits add 1 and answer is the negative
 	->  0111 1111 1111 1111 +1 = -32768


5. A 1
   -> 0b0000000000000001
   -> 0o1
   -> 0x1
   
   B 100
   -> 0b0000000001100100
   -> 0o144
   -> 0x64

   C 1000
   -> 0b0000001111101000
   -> 0o1750
   -> 0x3e8
   D 10000
   -> 0b0010011100010000 
   -> 0o23420
   -> 0x2710
   
   E. cannot do it in 16 bits with twos compliment

   F. -5
   -> 0b0000000000000101 = 5
   -> 0b1111111111111010 +1 = -5
   -> 0b1111111111111011 = -5
   -> 0o177773
   -> 0xFFFB 8+3

   H. -100
   -> 0b0000000001100100 = 100
   -> 0b1111111110011011 + 1 = -100
   -> 0b11111111 1001 1100 = -100
   -> 0o177634
   -> 0xFF9C

   6. Hello\n
  
   7. A 0b00000000000001111011 = 1 + 2 + 8 + 16 + 32 + 64 = 123
   	  1 byte -> encoding since 7 signifcant bits
   	  encoded -> 01111011
   	  ascii char

      B 0b00000000000011101011 = 1 + 2 + 8 + 32 + 64 + 128 = 235
      2 byte ->encoding
      encoded -> 1100001110101011

      C 0b00000000010001000100 = 4 + 64 + 1024 = 1092
      2 byte -> encoding
      encoded -> 1101000110000100

      D 0b00000010001001100100 = 4+32+64+512 +8192 = 8804
      3 byte -> encoding
      encoded -> 111000101000100110100100

      E 0b 00011011010100110110 = 6 + 16 + 32 + 128 + 512 + 4096 + 8192 + 32768 + 65536 = 120118
      4 byte -> encoding
      encoded -> 11110000100110111001010010110110



#bytes	#bits	Byte 1		Byte 2		Byte 3		Byte 4
1		7		0xxxxxxx	-			-			-
2		11		110xxxxx	10xxxxxx	-			-
3		16		1110xxxx	10xxxxxx	10xxxxxx	-
4		21		11110xxx	10xxxxxx	10xxxxxx	10xxxxxx
1110 0010 10 000110 10 101011
0010 0001 1010 1011
2    1     A    B