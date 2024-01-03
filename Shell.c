#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80  /* The max length of length command */
#define MAX_ARGS 42 /* Maximum number tokens + 1 for NULL terminating */
#define HISTORY_SIZE 10 /* Maximum commands store in history*/



typedef struct{
	char* command;
	pid_t pid;
} history_command;

history_command history[HISTORY_SIZE];
int counter_history = 0;

void add_to_history(char *userInput , pid_t pid){

	if (counter_history >= HISTORY_SIZE) {
		// Free the memory of the oldest command
		if (history[0].command != NULL) {
			free(history[0].command);
		}
		// Shift commands in the history buffer to make room for the new command
		for (int i = 1; i < HISTORY_SIZE; i++) {
			history[i - 1] = history[i];
		}
		// Decrement counter_history because we have removed the oldest command
		counter_history--;
  	}
	
	// Allocate memory for a copy of the command
	history[counter_history].command = strdup(userInput);
	
	if (history[counter_history].command == NULL) {
        perror("Error duplicating command");
        exit(1);
    }

	history[counter_history].pid = pid;
	counter_history++;
	
}

void print_history(){

	printf("ID     PID     Command\n");
	for(int i =  counter_history -1; i >=0; i--){
		printf("%d     %d     %s\n", counter_history - i, history[i].pid, history[i].command);	
	}
}

void execution(char *command){
	// Creating tokens for inputs
 		char *token = strtok(command, " \n");
		char *args[MAX_LINE/2 + 1]; /* an array of character strings */
 		int argc = 0 ;
 		
 		while(token !=NULL && argc < MAX_ARGS){
 			args[argc] = token;
 			argc++;
 			token = strtok(NULL," \n");
			
 		}
 		//Adding NULL as the last argument in args array
 		args[argc] = NULL;

 		pid_t pid = fork();
 
 		if(pid < 0 ){
 			perror("Fork Failed");
 			exit(1);
 		}
 		else if (pid ==0){  // Child Created Successfully
 			// Executing the command in child process
 			if(execvp(args[0],args) == -1){
 				perror("Invalid command");
 				exit(1);
 			}
 			
 		}
 		else {  // Parent Process
 		// Parent process code
 			int child_status;
 			waitpid(pid, &child_status, 0);
 		}
}

int main(void){
	char *args[MAX_LINE/2 + 1]; /* an array of character strings */
	int should_run =1; // flag to determine when to exit program
	
	
	while(should_run){
	printf("CSCI3120>");
	fflush(stdout);
	char userInput[81]; // One extra character for Null terminatioating or New Line Character
	char *token;

		if(fgets(userInput, sizeof(userInput), stdin) != NULL){
			if(strcmp(userInput, "exit\n") == 0){
				printf("Exited the program .\n");
				should_run= 0;
				
			}else if(strcmp(userInput, "history\n") == 0){
				print_history();
				
			}
			else if(strcmp(userInput,"!!\n") == 0){
					if(counter_history > 0){
						printf("Command which got executed, is  %s\n",history[counter_history -1 ].command);
						char *executedCommand = strdup(history[counter_history - 1].command);
						add_to_history(executedCommand,getpid());
						execution(executedCommand);
					}else{
						printf("No command in history!\n");
					}

			}else if(userInput[0] == '!'){
					int commandIndex = atoi(userInput + 1);
					if(counter_history > 0 && commandIndex <= counter_history){
						printf("Command which got executed, is  %s\n",history[counter_history - commandIndex].command);
						char *executedCommand = strdup(history[counter_history - commandIndex].command);
						add_to_history(executedCommand,getpid());
						execution(executedCommand);
					} else {
						printf("Such a command is NOT in history!\n");
					}
			}else{
				char *commandCopy = strdup(userInput);
				if (commandCopy == NULL) {
            		perror("Error duplicating command");
            		exit(1);
        		}
				execution(commandCopy);
				add_to_history(userInput,getpid());

				// Free the allocated memory
        		free(commandCopy);		
			}
		}
		else{ 
			printf("Error reading User Input.\n");
		}
	}
		
	return 0;			
		
}


		

