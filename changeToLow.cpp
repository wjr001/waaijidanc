#include<iostream>
#include<string>

using namespace std;

string changeToLow(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}