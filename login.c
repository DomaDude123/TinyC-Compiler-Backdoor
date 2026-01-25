#include <string.h>
#include <stdio.h>
static int do_login(const char *username){
	if (!strcmp(username, "root"))
		return 0;
	return 1; 
	}
int main(int argc, char *argv[]){
	if (argc != 2)
		return 1;
	if (!do_login(argv[1])) {
		printf("Login successful\n");
		return 0;
	}
	printf("Login failed\n");
	return 1; 
}
