#include<iostream>
using namespace std;

// Iterative Bubble Sort
void bubbleSort(int arr[], int n)
{   
	//base case / termination condition
	if(n == 1)
		return;
	else{
		// After the first pass of bubble sorting, the largest element is moved (or bubbled) to the end.
	    for (int j = 0; j < n-1; j++)
	    {
	        if(arr[j] > arr[j+1])
	            swap(arr[j], arr[j+1]);
		}
		// Largest element is fixed,
    	// recursion for remaining array
		bubbleSort(arr,n-1);

}

}
	     
void swap(int &a, int &b){
	
	int temp;
	temp  =a;
	a=b;
	b=temp;
}

void printArray(int a[], int s)
{
	for (int i=0; i<s; i++){
		cout<<a[i]<<" ";
	}
}

int main(){
	const int size = 5;
	int array[size]={45, 34, 22, 12, 49};
	cout<<"Before Sorting: ";
	printArray(array,size);
	bubbleSort(array, size);
	cout<<endl<<"After Sorting: ";
	printArray(array,size);
}

