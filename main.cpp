#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <direct.h>
using namespace std;
//#include"vld.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)

//bool HttpGetReq(char* vocabulary);
bool analysis(char* vocabulary);
bool imgPross(const char* item);

int main()
{
	//system("chcp 65001"); 
	imgPross("eng");
	ifstream text;
	text.open("text.txt", ios::in);
	string eng[2];
	text >> eng[0];
	while (!text.eof())
	{
		eng[1] = eng[0];
		text >> eng[0];
		if (((eng[0].compare("A"))==0)|| ((eng[0].compare("A.")) == 0))
		{
			if (isalpha((eng[1])[0]))
			{
				analysis((char*)eng[1].c_str());
			}
			break;
		}
	}
	
	
	/*
	while (!text.eof())
	{
		text >> textTemp;
		
	}
	*/
	return 0;

}
