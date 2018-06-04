#include<iostream>
#include<string.h>
using namespace std;

void print(struct books book);

struct books
{

char title[30];
char author[30];
int bookID;
};


int main()
{
struct books book1; //declear book1 of type book
//struct books book2; //declear book2 of type book

strcpy(book1.title, "learn cpp");
strcpy(book1.author,"naveen");
book1.bookID = 1234;


print(book1);

return 0;
}

void print(struct books book)
{

cout <<"book title: "<<book.title<<endl;
cout <<"book author:"<<book.author<<endl;
cout <<"book ID:"<<book.bookID<<endl;

}
