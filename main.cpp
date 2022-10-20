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
	char* fileDir = (char*)malloc(260);
	getcwd(fileDir, 260);
	char* out = (char*)malloc(256);
	sprintf_s(out, 256, "%s/platform-tools/adb.exe devices", fileDir);
	system(out);
	while (true)
	{
		system("pause");
		sprintf_s(out, 256, "%s/platform-tools/adb.exe shell screencap /sdcard/orgImg.png", fileDir);
		system(out);
		sprintf_s(out, 256, "%s/platform-tools/adb.exe pull /sdcard/orgImg.png", fileDir);
		system(out);
		output();
	}
	free(out);
	free(fileDir);
	return 0;
}
