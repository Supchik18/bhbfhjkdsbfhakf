include <string>
#include <iostream>
using namespace std;

extern "C" __declspec(dllexport) bool Found(char main[], char sub[])
{
	string mainstr(main);
	string substr(sub);

	if (mainstr.find(substr) !=  string::npos) 
	{
		return true;
	}
	else 
	{ 
		return false; 
	}
}