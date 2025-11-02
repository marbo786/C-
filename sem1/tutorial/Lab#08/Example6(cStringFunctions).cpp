#include <iostream>
#include <cstring>
using namespace std;

int main()
{
     char str[20] = "BeginnersBook";
     cout<<"Length of string str1: "<<strlen(str)<<endl;
     cout<<"Sizeof str1: "<<sizeof(str)<<endl;
     
     char s1[20] = "BeginnersBook";
     char s2[20] = "BeginnersBook.COM";
     if (strcmp(s1, s2) ==0)
        cout<<"string 1 and string 2 are equal"<<endl;
	 else
        cout<<"string 1 and 2 are different"<<endl;
     
     /* below it is comparing first 8 characters of s1 and s2*/
    if (strncmp(s1, s2, 8) ==0)
        cout<<"string 1 and string 2 are equal"<<endl;
	else
        cout<<"string 1 and 2 are different"<<endl;
     
    char s11[10] = "Hello";
    char s22[10] = "World";
    strcat(s11,s22);
    cout<<"Output string after concatenation: "<<s11<<endl;
	
	char str1[10] = "Welcome";
    char str2[10] = "Here";
    strncat(str1,str2, 3);
    cout<<"Concatenation using strncat: "<<str1<<endl; 
	
	char ss1[40] = "string 1";
     char ss2[40] = "string 2 : I’m gonna copied into s1";
     /* this function has copied s2 into s1*/
     strcpy(ss1,ss2);
     cout<<endl<<"ss1= "<<ss1;
	return 0;
}
