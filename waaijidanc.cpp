#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include"vld.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)


//bool HttpGetReq(char* vocabulary);
bool analysis(char* vocabulary);

int main()
{
	system("chcp 65001");
	for (int i = 0; i < 10000; i++)
	{
		analysis((char*)"china");
	}
	
	return 0;

}
