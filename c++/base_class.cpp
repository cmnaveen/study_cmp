#include<iostream>
using namespace std;

class circle // specify a class
{
	private:
		double radius; // class data member
	public:
		void setRadius(double r);
		double getArea(); // member fun 


};

void circle :: setRadius(double r)
{
	radius = r;
}


double circle :: getArea()
{

	return 3.14*radius*radius;
}
int main()
{
	circle c1; // define object of class circle
	c1.setRadius(2.5);
	cout << c1.getArea(); //display area of circle object
	return 0;
}
