#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
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
	Mat img = imread("./1.png",0);
	if (img.empty())
	{
		cout << "图片加载失败";
	}
	imshow("test", img);
	waitKey(0);
	Mat poss_img;
	threshold(img, poss_img, 60,255, THRESH_BINARY);
	imshow("test", poss_img);
	waitKey(0);
	analysis((char*)"china");
	return 0;

}
