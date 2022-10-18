#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)


bool HttpGetReq(char* vocabulary);
bool analysis(char* vocabulary);

int main()
{
	analysis((char*)"windows");
}
