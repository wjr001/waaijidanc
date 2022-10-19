#include <iostream>
#include <direct.h>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)

bool imgPross(const char* item)
{
	Mat img = imread("./orgImg.png", 0);
	if (img.empty())
	{
		cout << "Í¼Æ¬¼ÓÔØÊ§°Ü";
	}
	//imshow("test", img);
	//waitKey(0);
	Mat poss_img;
	threshold(img, poss_img, 90, 255, THRESH_BINARY);
	//imshow("test", poss_img);
	//waitKey(0);
	imwrite("after_pros.png", poss_img);
	char* fileDir = (char*)malloc(260);
	getcwd(fileDir, 260);
	char* output = (char*)malloc(1024);
	sprintf_s(output, 1024, "tesseract %s/after_pros.png %s/text -l %s", fileDir, fileDir,item);
	cout << output;
	system(output);
	free(fileDir);
	free(output);
	return true;
}