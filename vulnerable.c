/* vulnerable.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int func(FILE *input) {
	char buffer[19];
	fread(buffer, sizeof(char), 43, input);
	return 1;
}
int main(int argc, char *argv[]) {
	FILE *input;
	
	char *shell  = getenv("MYSHELL");
	if(shell){
		printf("%x\n", (unsigned int)shell);
	}

	input= fopen("badfile", "r");
	func(input);
	printf("Success\n");
	fclose(input);
	return 1;
}
