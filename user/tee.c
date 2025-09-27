#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/*
 * fd 0 = standard input (keyboard, pipe, etc)
 * fd 1 = standard output (terminal)
 */

int main(int argc, char *argv[]){

	for(int i = 0; i < argc; i++){
		printf("%d: %s\n", i, argv[i]);
	}


	char data[16];
	int bytesToRead;


	while((bytesToRead = read(0, data, sizeof(data))) > 0){
		
		// Writing to the terminal
		write(1, data, bytesToRead);

		// Writing to a file
		//write(output, data, bytesToRead);
		
		for(int i = 1; i < argc; i++){

			// Opening file. Create if it doesn't exists and write to it
			int output = open(argv[i], O_CREATE | O_WRONLY);
			
			if(output < 0){
				printf("Error in opening file\n");
			}

			// Writing to a file
			write(output, data, bytesToRead);
			close(output);
		}
	}
	//bytesToRead is still 0 so it doesn't go in the while loop the second time around
	// while loop first, then outside of it the for loop thats writing to the files
        
	// Handles multiple files
	
	
	//for(int i = 1; i < argc; i++){

		// Opening file. Create if it doesn't exists and write to it
	//	int output = open(argv[i], O_CREATE | O_WRONLY);
	//	if(output < 0){
	//		printf("Error in opening file\n");
	//	}

		// Writing to a file
	//	write(output, data, bytesToRead);
	//	close(output);
	//}

	//close(output);

	return 0;

}
