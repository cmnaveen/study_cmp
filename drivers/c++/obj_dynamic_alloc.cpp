#include<iostream>
using namespace std;

class box
{
public:
box(){
cout << "constructor called " <<endl;
}
~box(){
cout <<"distructor called" <<endl;
}
};
int main()
{
box *myboxarray = new box[5];

delete [] myboxarray; // delete array 

return 0;

}
