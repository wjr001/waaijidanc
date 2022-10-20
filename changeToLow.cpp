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

string changeToUp(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		str[i] = toupper(str[i]);
	}
	return str;
}