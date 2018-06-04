#include<stdio.h>
char *fun(char *p)
{

	if(*p)
	fun(p+1);
//	fun(p++); // core dump
	printf("%c",*p);
}
int main()
{
	char s[20]="hello";
	fun(s);
printf("\n");
	return 0;
}
