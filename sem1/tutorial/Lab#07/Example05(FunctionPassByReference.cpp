/*Design program that takes a course score (a value between 0 and 100) and determines a student's course grade. This program has three functions: main, getScore, and printGrade, as follows:
1. main
	a.	Declare a variable for Course Score
	b.	Call getScore function by refernce
	c.	Call printGrade function
2. getScore
	a.	Must return void
	b.	Prompt the user for the input.
	c.	Get course score as input.
	d.	Print the course score.
3. printGrade
	a.	Calculate the course grade.
	b.	Print the course grade.
	
*/

#include <iostream>
using namespace std;
void getScore(int& score);
void printGrade(int score);

int main()
{
	int courseScore;
	cout <<"Based on the course score, \n"
	<< "this program computes the "
	<< "course grade." << endl<<endl; 
	getScore(courseScore);
	printGrade(courseScore); 
	return 0;
}

void getScore(int& score)
{
	cout << "Enter course score:(1-100) "; 
	cin >> score; 
	cout << "Course score is "
	<< score << endl; 
}

void printGrade(int cScore)
{
	cout <<endl<< "Your grade for the course is "; 
	if (cScore >= 90) 
	cout << "A." << endl;
	else if (cScore >= 80)
	cout << "B." << endl;
	else if(cScore >= 70)
	cout << "C." << endl;
	else if (cScore >= 60)
	cout << "D." << endl;
	else
	cout << "F." << endl;
}



