#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

struct SuperHero
{
	string name;
	string superPower;
	int age;
};

void superHeroArrays()
{
	string superNames[10] = {"superman", "batman", "aquaman" };
	string superPowers[10] = {"strength", "money", "speak to fish" };
	int superAge[10] = {35, 35, 50};
	
	SuperHero mySuperHeroes[10];

	SuperHero superman;
	superman.age = 35;
	superman.superPower = "strength";
	superman.name = "Superman";
	mySuperHeroes[0] = superman;

	SuperHero batman;
	batman.age = 35;
	batman.name = "Batman";
	batman.superPower = "Money";
	mySuperHeroes[1] = batman;
	
	
	

	int nameLength = 10;

	for (int i =0; i < nameLength; i++)
	{
		cout << "Hero Name:" << superNames[i];
		cout << " Hero Power:" << superPowers[i];
		cout << " Hero Age:" << superAge[i];
		cout << endl;

	}


}


int main()
{
	SuperHero myHeroes[10];
	int heroLength = 10;
	bool isQuit = false;
	int heroIndex = 0;
	while (!isQuit)
	{
		SuperHero tempHero;
		cout << "Name? ";
		//cin >> tempHero.name;
		getline(cin, tempHero.name);
		//cin.ignore(256, '\n');
		cout << endl << "Super Power?";
		//cin >> tempHero.superPower;
		getline(cin, tempHero.superPower);
		//cin.ignore(256, '\n');
		cout << endl << "Age?";
		cin >> tempHero.age;
		myHeroes[heroIndex] = tempHero;
		heroIndex++;
		if (tempHero.name == "q" || tempHero.superPower == "q")
		{
			isQuit = true;
		}
		else
		{
			for (int i = 0; i < heroIndex; i++)
			{
				cout << "Name:" << myHeroes[i].name;
				cout << "Power:" << myHeroes[i].superPower;
				cout << "Age:" << myHeroes[i].age;
				cout << endl;
			}
		}
	}
	_getch();

	return 0;
}
