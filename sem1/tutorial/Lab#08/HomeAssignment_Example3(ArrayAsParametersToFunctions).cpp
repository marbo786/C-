//Arrays as Parameters to Functions

#include<iostream>
using namespace std;

const int ARRAY_SIZE = 10;

void initializeArray(int x[],int sizeX);
void fillArray(int x[],int sizeX);
void printArray(const int x[],int sizeX);
int sumArray(const int x[],int sizeX);
int indexLargestElement(const int x[],int sizeX);
void copyArray(int list1[], int src, int list2[], int tar, int numOfElements);

int main()
{

	int listA[ARRAY_SIZE] = {0}; //Declare the array listA of 10 components and initialize each component to 0.
	
	int listB[ARRAY_SIZE]; //Declare the array listB of 10 components.
	cout << "Line 1: listA elements: "; //Line 1
	
	//Output the elements of listA using the function printArray
	printArray(listA, ARRAY_SIZE); //Line 2
	cout << endl; //Line 3
	
	//Initialize listB using the function initializeArray
	initializeArray(listB, ARRAY_SIZE); //Line 4
	cout << "Line 5: listB elements: "; //Line 5
	
	//Output the elements of listB
	printArray(listB, ARRAY_SIZE); //Line 6
	cout << endl << endl; //Line 7
	
	cout << "Line 8: Enter " << ARRAY_SIZE<< " integers: "; //Line 8
	//Input data into listA using the function fillArray
	fillArray(listA, ARRAY_SIZE); //Line 9
	cout << endl; //Line 10
	
	cout << "Line 11: After filling listA, "<< "the elements are:" << endl; //Line 11
	//Output the elements of listA
	printArray(listA, ARRAY_SIZE); //Line 12
	cout << endl << endl; //Line 13
	
	//Find and output the sum of the elements of listA
	cout << "Line 14: The sum of the elements of listA is: "	<< sumArray(listA, ARRAY_SIZE) << endl<< endl; //Line 14
	
	
	//Find and output the position of the largest element in listA
	cout << "Line 15: The position of the largest element in listA is: "<< indexLargestElement(listA, ARRAY_SIZE) << endl; //Line 15
	
	//Find and output the largest element in listA
	cout << "Line 16: The largest element in listA is: "<< listA[indexLargestElement(listA, ARRAY_SIZE)] << endl << endl; //Line 16

	//Copy the elements of listA into listB using the function copyArray
	copyArray(listA, 0, listB, 0, ARRAY_SIZE); //Line 17
	cout << "Line 18: After copying the elements of listA into listB," << endl;
	cout << " listB elements are: "; //Line 18
	//Output the elements of listB
	printArray(listB, ARRAY_SIZE); //Line 19
	cout << endl; //Line 20
	
	return 0;
}





//Function to initialize an int array to 0.
//The array to be initialized and its size are passed
//as parameters. The parameter listSize specifies the
//number of elements to be initialized.
void initializeArray(int list[], int listSize)
{
	int index;
	for (index = 0; index < listSize; index++)
		list[index] = 0;
}


//Function to read and store the data into an int array.
//The array to store the data and its size are passed as
//parameters. The parameter listSize specifies the number
//of elements to be read.
void fillArray(int list[], int listSize)
{
	int index;
	for (index = 0; index < listSize; index++)
		cin >> list[index];
}


//Function to print the elements of an int array.
//The array to be printed and the number of elements
//are passed as parameters. The parameter listSize
//specifies the number of elements to be printed.
void printArray(const int list[], int listSize)
{
	int index;
	for (index = 0; index < listSize; index++)
		cout << list[index] << " ";
}




//Function to find and return the sum of the
//elements of an int array. The parameter listSize
//specifies the number of elements to be added.
int sumArray(const int list[], int listSize)
{
	int index;
	int sum = 0;
	for (index = 0; index < listSize; index++)
		sum = sum + list[index];
	return sum;
}



//Function to find and return the index of the first
//largest element in an int array. The parameter listSize
//specifies the number of elements in the array.
int indexLargestElement(const int list[], int listSize)
{
	int index;
	int maxIndex = 0; //assume the first element is the largest
	for (index = 1; index < listSize; index++)
		if (list[maxIndex] < list[index])
			maxIndex = index;
	return maxIndex;
}

//Function to copy some or all of the elements of one array
//into another array. Starting at the position specified
//by src, the elements of list1 are copied into list2
//starting at the position specified by tar. The parameter
//numOfElements specifies the number of elements of list1 to
//be copied into list2. Starting at the position specified
//by tar, the list2 must have enough components to copy the
//elements of list1. The following call copies all of the
//elements of list1 into the corresponding positions in
//list2: copyArray(list1, 0, list2, 0, numOfElements);
void copyArray(int list1[], int src, int list2[],
int tar, int numOfElements)
{
	for (int index = src; index < src + numOfElements; index++)
	{
		list2[index] = list1[tar];
		tar++;
	}
}
