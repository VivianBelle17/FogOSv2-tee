#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]){


	/*for(int i = 1; i < argc; i++){	

		// Writing to the terminal
		write(1, *(argv + i), sizeof(*(argv + 1)));
	}*/

	char data[16];
	int bytesToRead;

	while((bytesToRead = read(0, data, sizeof(data))) > 0){
		write(1, data, bytesToRead);
	}


	return 0;

}
