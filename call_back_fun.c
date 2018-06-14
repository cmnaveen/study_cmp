#include<stdio.h>
int fun(int (*callback_fun)(void))
{

    printf("inside parent function\n");
    callback_fun();

}

int test()
{

    printf("inside callback_fun function\n");

}

int main()
{

    fun(&test);
    printf("main function end\n");

    return 0;
}
