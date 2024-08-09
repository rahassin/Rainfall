#include <stdio.h>
#include <stdlib.h>

int run(void) 
{
	fwrite("Good... Wait what?\n", 1, 19, stdout);
	return system("/bin/sh");
}

int main(int argc, char **argv)
{
	char str[80];

	gets(str);
	return (0);
}