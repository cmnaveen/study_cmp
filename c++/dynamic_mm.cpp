#include<iostream>

using namespace std;

int main()
{
double *pval = NULL;
pval = new double; //request memory for the val
*pval = 3483.75;

cout << "val : "<<*pval<<endl;
delete pval;
return 0;

}
