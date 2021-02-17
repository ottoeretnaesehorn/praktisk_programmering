#include <stdio.h>
#include <unistd.h>

int main() 
{
	char *name; 
	name = getlogin();

	printf("Hello, %s!\n", name);
	
	return 0; 
}
