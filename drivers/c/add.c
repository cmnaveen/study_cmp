#include<stdio.h>
int add(int x,int y)
{
	while(y!=0)
	{
		int carry = x & y;

		x = x ^ y;
printf("\n-----------------%d\n",x);
		y = carry << 1;
printf("\n-----------------%d\n",y);
	}
	return x;
}
int main()
{
	int x=15,y=32;
	printf("%d",add(x,y));
	return 0;


}
