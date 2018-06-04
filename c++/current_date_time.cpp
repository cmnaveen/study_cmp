#include<iostream>
using namespace std;
int main()
{
// current date/time based on current system 

time_t now = time(0);

//convert now to string form 
char *dt = ctime (&now);
cout << "the local date and time is: "<<dt <<endl;

//convert now to tm struct for UTC

tm *gmtm = gmtime(&now);
dt = asctime(gmtm);

cout << "the UTC date and time is: "<< dt << endl;
//time_t now = time(0);
cout << "Number of sec since January 1,1970:" << now << endl;
tm *ltm = localtime(&now);
// print various components of tm structure.
cout << "Year: "<< 1900 + ltm->tm_year << endl;
cout << "Month: "<< 1 + ltm->tm_mon<< endl;
cout << "Day: "<< ltm->tm_mday << endl;
cout << "Time: "<< 1 + ltm->tm_hour << ":";
cout << 1 + ltm->tm_min << ":";
cout << 1 + ltm->tm_sec << endl;

}
