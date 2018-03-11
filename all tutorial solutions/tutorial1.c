1a. printf("%d\n",*p) -> 1235
 b. printf("%p\n",p)  -> 0x7654
 	p++ (integer adds 4 to address)
 c. printf("%p\n",p)  -> 0x7658

 2. abc123\n is output on a new line

 3. s1 is a global variable and can be used anywhere after it's declaration', will last throughout entire program life
    s2 is located in main hence it will last until main returns (entire program) life

 4. static means it cannot be used in other .c files, for x1 it means it is a global variable used in function
 	on the function it means it is a global variable but can only be accessed in this file no other .c code
 	on the variable x2 it affects the visibility, it means that it will only live inside the function but live through death, so it will be a global variable in function keep its value from previous calls

 5. a/b have no difference since it is a single statement brace's aren't required however for c/d 
 	c will print zero\nafter if x == 0, if x!=0 it will print nothing
 	d will print after\n no matter what since it has no braces the only statement effected by the if is the print "Zero\n"

 6. A. n = 3, a = 42, b = 64, c = 999
    B. n = 2, a = 42, b = 64, c = undefined error value 
    C. n = 2, a = 42, b = 64, c = undefined error value 
    D. n = 1, a = 42, b = undefined error value, c = undefined error value
    E. n = 9, a = undefined error value, b = undefined error value, c = undefined error value

 7. you can use fgets(), and then use isint to check if integer inputs then you can scan through the fgets and store into values as wanted using the space delimiter
    fake tokenizing

 8. A, -e flag will make it execute the c code given or all code igven will execute main function and print to stdout 
 	B, -S flag will produce an assembly file with assembly code from the given c code
 	C, -c flag will make -o file which still needs to be combined with library's combines the file into an -o file to be used in execution
 	D, will make a file ./a.out with the given files executable code

 9. A. the QUEUE_H ifndef define are guards which check for multiple definitions, it makes sure the #include file is included twice so we dont get duplicate symbol errors
       ifndef checks if QUEUE_H has been defined, and check it off as seen, #ifndef if it has been seen it skips the redfining up until the #endif 
    B.'
    #define MAXQ 6
    Queue make(){
    	Queue new = malloc(sizeof(struct Queuerep));
    	new->nitems = 0;
    	new->head = new->tail = 0;
    	new->items = malloc(sizeof(int)*MAXQ);
    	return neq
    }
    void delete(Queue q){
    	free(q->items);
    	free(q);
    }
    void addQueue(Queue q,int i){
    	assert(q->nitems<MAXQ);
    	if(q->nitems !=0)
    			q->tail = (q->tail+1)%MAXQ;
    	q->items[q->tail] = i;
    	q->nitems++;
    }
    int dropQueue(Queue q){
    	int drop = q->items[q->head];
    	if(q->nitems == 0)return -1;
    	q->head = (q->head+1)%MAXQ; 
    	return drop;
    }
    void showQueue(Queue q){
    	for(int i = 0;i<MAXQ;i++)printf("%d->",q->items[i]);
    		printf("\n");
    }

    C.
    #define MAXQ 6
    Queue make(){
    	Queue new = malloc(sizeof(struct Queuerep));
    	new->nitems = 0;
    	new->head = new->tail = 0;
    	new->items = malloc(sizeof(int)*MAXQ);
    	return neq
    }
    void delete(Queue q){
    	free(q->items);
    	free(q);
    }
    void addQueue(Queue q,int i){
    	assert(q->nitems<MAXQ);
    	if(q->nitems !=0)
    			q->tail = (q->tail+1);
    	q->items[q->tail] = i;
    	q->nitems++;
    }
    int dropQueue(Queue q){
    	int drop = q->items[q->head];
    	if(q->nitems == 0)return -1;
    	for(int i = 0;i<MAXQ;i++)q->items[i] = q->items[i+1];
    	q->tail--;
    	q->nitems--;
    	return drop;
    }
    void showQueue(Queue q){
    	for(int i = 0;i<MAXQ;i++)printf("%d->",q->items[i]);
    		printf("\n");
    }

   D. q->head will always be 0 and q->tail is always q->nitems - 1 so they can be thrown out infact even the MAXQ in the array doesn't need to be there can be defined with a malloc in the make

   