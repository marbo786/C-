/*
Insertion Sort:
we start from the second element and compare it with the first element and 
put it in a proper place. 
Then we perform this process for the subsequent elements.

We compare each element with all its previous elements 
and put or insert the element in its proper position. 
*/
#include<iostream>
using namespace std;

const int n=7;
int arr[n]={83,10,20,5,23,38,11};

void display()
{
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}
}

void insertionSort()
{
   int i, key, j;
   int suitableKeyIndex;
   for (i = 1; i < n; i++)
   {
   	
		cout<<endl<<"Round "<<i;
       key = arr[i];
       j = i;
 
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
	   while (j > 0 && arr[j-1] > key)
       {
       		cout<<"\n\tPass "<<j<<" :";
           arr[j] = arr[j-1];
           j --;
           display();
       }
       arr[j] = key;
       cout<<"\t\tResult:";
	   display();
	   cout<<"\n_______________________________________________________________"<<endl;
   }
}
int main()
{
	cout<<"Unsorted Array: ";
	display();
	insertionSort();
	cout<<"\n\nSorted Array: ";
	display();
}
