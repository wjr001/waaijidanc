#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <direct.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)

//bool HttpGetReq(char* vocabulary);
bool analysis(char* vocabulary);
//bool imgPross(const char* item, int input_thresh=75);
string changeToLow(string str);
void output();

int main()
{
	//system("chcp 65001"); 
	//output();
	cout << "请确认您的手机已启用USB调试并已正确连接且已进入测试页面\n";
	system("adb devices");
	while (true)
	{
		system("pause");
		system("adb shell screencap /sdcard/orgImg.png");
		system("adb pull /sdcard/orgImg.png");
		output();
	}
	return 0;
}
