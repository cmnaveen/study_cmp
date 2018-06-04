#include<iostream>
using namespace std;

class add {

	public: 
		// constructor 
		add(int i=0)
		{
			total = i;
		}

		// interface to outside world 
		void addNum(int num)
		{

			total += num;
		}
		int getTotal()
		{
			return total;

		}
	private:
		// hidden data from outside world
		int total;
};

int main()
{
	add a;
	a.addNum(10);
	a.addNum(20);
	a.addNum(30);

	cout << "total" << a.getTotal() <<endl;
	return 0;
}

