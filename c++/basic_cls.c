#include<iostream>
using namespace std;
class data
{
	public:
		double x;
		double y;

};


int main()
{
	data d1;
	data d2;
	double total = 0.0;

cin >>d1.x; // = 20;
cin >>d1.y;//= 40;
cin >>d2.y; // = 30; 
cin >>d2.x;// = 32;


	total = d1.x * d2.y;
	cout << "d1.x *d2.y:" <<total <<endl;

	total = d1.y * d2.x;
	cout << "d1.y* d2.x:" << total <<endl;

	return 0;
}
