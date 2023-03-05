#include<unistd.h>
#include<stdio.h>
int main()
{
	int fd = access("./ls", X_OK);
	printf("%d\n", fd); 
}