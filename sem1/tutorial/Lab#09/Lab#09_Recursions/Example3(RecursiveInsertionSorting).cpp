// Insertion sort in C++
#include <iostream>
using namespace std;

void insertionSort(int array[], int size) {
  	if(size<=1)
  		return;
  	
  	insertionSort(array,size-1);
	
	int key = array[size-1]; // array[]={7,9,11,8,10,6}
    int j = size-1;         //key is at size-1 and to compare the key to one index 
	                          //less we need to assign j = size-2

	    // Compare key with each element on the left of it until an element smaller than
    	// it is found.
    	// For descending order, change key<array[j] to key>array[j].
    while (key < array[j-1] && j > 0) {
    	array[j] = array[j-1];
    	--j;
   	}
    array[j] = key;

}

// Driver code
int main() {	
  int data[] = {11, 9, 7, 8, 10, 6};
 
  int size = sizeof(data) / sizeof(data[0]); 

  
  insertionSort(data, size);
}
