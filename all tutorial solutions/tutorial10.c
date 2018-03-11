1. 	   the initial values are stored in the data
	   the function variables and declarations are stored in the stack
	   the heap stores dynamically allocated memory
	   the code stores the compiled program 

2a.
	   VSZ - size in virtual memory
	   RSS - resident set size, size in ram physical memory
	   TTY - controlling terminal 
	   stat - proccess state 
	   start - starting time or date of the proccess when it was created 
	   time - cumulative CPU_time
	   command - the command with all its arguements
b.	   program's execution status R = running, S = Sleep, T = stopped
c.     30383   7624  3828 pts/77   S+   Aug23 336:28 top
	   6 1/2 hours jesus
d. 	   some proccesses don't have an attatched terminal, some left running in background
       ignore's SIGHUP and the proccess that created them exit leaving them with no terminal
f.     the first proccess is machine's start so july08

3a.    env command or can echo $path       
b.     1. get the complete path name for the directory
	   2. use stat to get the info for the file/directory
	   3. check the permissions for the group/owner/other
	   4. check if its a file executable

4.     4 possible outputs 
	   1. Hello
	   	  Gan bei
	   	  prost
	   	  Goodbye
	   	  Goodbye
	   2. Hello
	      prost
	      Gan bei
	      Goodbye
	      Goodbye
	   3. Hello
	      Prost
	      Goodbye
	      Gan bei
	      Goodbye
	   4. Hello
	   	  Gan bei
	   	  Goodbye
	   	  Prost
	   	  Goodbye

5.	   fork would fail if there is not enough memory, or the proccess table is full or there aren't enough resources to create the subprocceses
	   process creation limit from user
	   proccess table is full
	   not enough memory to create a pagetable for the proccess

6a.    execve returns a value if it receives a non executable file or an invalid command, if it cannot run the program it will return a value   
b.     it changes the errorno global value which can allow us to print an error message or can put if(errno){
			perror("fatal"); exit(0);
		}	   

c. 	   proccess.c  dcc - Wall -Werror -o proc 	//checks the proccess id to check where proccess comes from
	   int main(void){
	      printf("%d\n",getpid());
	      return 0;
	   }

	   int main(int argc, char *argv[]){
	      if(fork == 0){
	      	//in the child we want to execute the ./proc and see the resulting pid and see if its the same or new 
	      	char *args[2], *envp[1];
	      	envp[0] = NULL;
	      	args[0] = "./proc";
	      	args[1] = NULL;
	      	execve(args[0],args,envp);
	      	perror("Execution Failed\n");
	      	exit(0);
	      }else{
	      	printf("Parnet Pid %d\n",);
	      }
	      retrun 0;
	   }
