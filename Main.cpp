#include <iostream>
#include <string>
#include <sstream>
#include "AdvisingDBAbstraction.h"

using namespace std;

int main()
{
	string path = "C:/Users/KALE/Desktop/AdvisingApp.sqlite";
	AdvisingDBAbstraction db(path);
	db.createMenu();

	system("PAUSE");
	return 0;
}