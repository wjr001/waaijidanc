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
bool imgPross();

int main()
{
	//system("chcp 65001"); 
	imgPross();
	ifstream text;
	text.open("text.txt", ios::in);
	char* textTemp=(char*)malloc(64);
	text >> textTemp;
	while (!text.eof())
	{
		text >> textTemp;
		analysis((char*)textTemp);
	}
	
	return 0;

}
