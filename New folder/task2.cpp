#include <iostream>
using namespace std;

int main()
{
	char alph;
	cout << "Enter an alphabet: ";
	cin >> alph;
	if (alph == 'a' || alph == 'e' || alph == 'i' || alph == 'o' || alph == 'u')

		cout << "Vowel";
	else
		cout << "Consonant";
	return 0;
}