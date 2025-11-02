#include<iostream>
using namespace std;

// Iterative Bubble Sort
void bubbleSort(int arr[], int n)
{
  for (int i = 0; i < n-1; i++)      

     // Last i elements are already in place   
     for (int j = 0; j < n-i-1; j++)
     {
         if(arr[j] > arr[j+1])
             swap(arr[j], arr[j+1]);
     }
}
void swap(int &a, int &b){
	
	int temp;
	temp  = a;
	a = b;
	b = temp;
}

void printArray(int a[], int s)
{
	for (int i=0; i<s; i++){
		cout<<a[i]<<" ";
	}
}

int main(){
	const int size = 5;
	int array[size]={45, 22, 34, 12, 4};
	cout<<"Before Sorting: ";
	printArray(array,size);
	bubbleSort(array, size);
	cout<<endl<<"After Sorting: ";
	printArray(array,size);
}

