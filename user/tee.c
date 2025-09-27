#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/*
 * fd 0 = standard input (keyboard, pipe, etc)
 * fd 1 = standard output (terminal)
 */

int main(int argc, char *argv[]){

	char data[16];
	int bytesToRead;

	// Opening file. Create if it doesn't exists and write to it
	int output = open("test.txt", O_CREATE | O_WRONLY);
	if(output < 0){
		printf("Error in opening file\n");
	}


	while((bytesToRead = read(0, data, sizeof(data))) > 0){
		
		// Writing to the terminal
		write(1, data, bytesToRead);

		// Writing to a file
		write(output, data, bytesToRead);

	}

	close(output);

	return 0;

}
