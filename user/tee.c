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


	char data[256];
	int bytesToRead;
	int output;
	struct stat st;
	int offset;

	while((bytesToRead = read(0, data, sizeof(data))) > 0){
		
		// Writing to the terminal
		write(1, data, bytesToRead);
		
		// Writing to multiple files
		for(int i = 1; i < argc; i++){

			if(strcmp(argv[i], "-a") == 0){
				i++;
				output = open(argv[i], O_CREATE | O_RDWR);
				
				fstat(output, &st);
				offset = st.size;
				
				seek(output, offset);
			} else {
				// Opening file. Create if it doesn't exists, empty it, and write to it
				output = open(argv[i], O_CREATE | O_WRONLY | O_TRUNC);	
			}
			write(output, data, bytesToRead);
			// Writing to a file
			if(bytesToRead > 0 && data[bytesToRead - 1] != '\n'){
				// Writing a new line to the file and to the terminal if the user used stdin
				write(output, "\n", 1);
				write(1, "\n", 1);
			}
			close(output);
		}
	}

	return 0;
}
