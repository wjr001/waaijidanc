
#include <iostream>
#include <winsock2.h> //该头文件需在windows.h之前
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include <json/json.h>
#pragma execution_character_set("utf-8")
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)


bool HttpGetReq(char* vocabulary);
bool analysis(char* vocabulary);

int main()
{
	analysis((char*)"windows");
}
