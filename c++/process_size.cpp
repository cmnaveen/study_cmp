#include <iostream>
extern int etext, edata, end;
using namespace std;
int main( ){
	cout << "Adr etext: " << hex << (&etext) << "\t ";
	cout << "Adr edata: " << hex << (&edata) << "\t ";
	cout << "Adr end: " << hex << (&end ) << "\n";

	char *s1 = "hello"; //in initialized data segmenta 
	static int a=1; //in initialized data segment 
	static int b; //in uninitialized data segment
	char s2[] = "hello"; //in the stack area.
	int * c = new int; 

	cout << hex << (int*)(s1) << endl;
	cout << hex << (int*)(&a) << endl;
	cout << hex << (int*)(&b) << endl;
	cout << hex << (int*)(s2) << endl;
	cout << hex << (int*)(c) << endl;
	delete c;
	return 0;
}

