#include<iostream>
using namespace std;
void insertionSort(int *array, int size){
   int key, j;
   for(int i = 1; i<size; i++) {
      key = array[i];//take value
      j = i;
      while(j > 0 && array[j-1]>key) {
         array[j] = array[j-1];
         j--;
      }
      array[j] = key; //insert in right place
   }
}
int main(){
   int n;
   n = 5;
   int arr[5] = {67, 44, 82, 17, 20}; // initialize the array
                  44 67 82 17 20
                  44 67 82 17 20
                  44 67 82 17 20 = 44 67 17 82 20 
   cout << "Array before Sorting: ";
   for(int i = 0; i<n; i++)
      cout << arr[i] << " ";
   cout << endl;
   insertionSort(arr, n);
   cout << "Array after Sorting: ";
   for(int i = 0; i<n; i++)
      cout << arr[i] << " ";
   cout << endl;
}
