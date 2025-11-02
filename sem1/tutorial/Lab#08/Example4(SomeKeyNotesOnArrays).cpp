//Partial Initialization of arrays during declaration
//Some random situations

//1
int list[10] = {0};
//declares list to be an array of 10 components and initializes all of the components to 0.


//2
int list[10] = {8, 5, 12};
//declares list to be an array of 10 components and initializes list[0] to 8, list[1]
//to 5, list[2] to 12, and all other components to 0.

//3
int list[] = {5, 6, 3};
//declares list to be an array of three components and initializes list[0] to 5,
//list[1] to 6, and list[2] to 3.

//4
int list[10] = {2, 5, 6, , 8}; //illegal

//Some Restrictions
//1
int myList[5] = {0, 4, 8, 12, 16}; //Line 1
int yourList[5]; //Line 2

yourList = myList; //illegal

//In fact, this statement will generate a syntax error. C++ does not allow aggregate
//operations on an array. 
//An aggregate operation on an array is any operation that
//manipulates the entire array as a single unit.
//To copy one array into another array, you must copy it component-wise—that is, one
//component at a time. This can be done using a loop, such as the following:

for (int index = 0; index < 5; index ++)
yourList[index] = myList[index]; //allowed


//2
cin >> yourList; //illegal

for (int index = 0; index < 5; index ++) //allowed
	cin >> yourList[index];
