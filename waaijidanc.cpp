#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <direct.h>
using namespace std;
#include<opencv2/opencv.hpp>
using namespace cv;
//#include"vld.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)

//bool HttpGetReq(char* vocabulary);
bool analysis(char* vocabulary);

int main()
{
	//system("chcp 65001"); 
	Mat img = imread("./2.png",0);
	if (img.empty())
	{
		cout << "图片加载失败";
	}
	//imshow("test", img);
	//waitKey(0);
	Mat poss_img;
	threshold(img, poss_img, 80,255, THRESH_BINARY);
	//imshow("test", poss_img);
	//waitKey(0);
	imwrite("after_pros.png", poss_img);
	char* fileDir = (char*)malloc(260);
	getcwd(fileDir, 260);
	char* output = (char*)malloc(1024);
	sprintf_s(output, 1024, "tesseract %s/after_pros.png %s/test -l eng", fileDir, fileDir);
	cout << output;
	system(output);
	free(fileDir);
	free(output);
	analysis((char*)"miX");
	return 0;

}
