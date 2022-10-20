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
bool imgPross(const char* item, int input_thresh=60);
string changeToLow(string str);
string changeToUp(string str);

void output()
{
	imgPross("chi_sim");
	ifstream text;
	text.open("text.txt", ios::in);
	string chi[2];
	string chiCom[64];
	int num_chiCom = 0;
	chi[1] = "0";
	//text >> chi[0];
	system("cls");
	string temp;
	bool term1 = true;
	bool term2 = false;
	bool textEOF = true;
	while (!text.eof())
	{
		text >> chi[0];
		chiCom[num_chiCom] = chi[0];
		term1 = false;
		if (chi[0].length() > 2)
		{
			term1 = ((chi[0])[2] >= 65 && (chi[0])[2] <= 90) || (((chi[0])[2] >= 97 && (chi[0])[2] <= 122) && ((((chi[0])[0] == 65))|| ((chi[0])[0] == 66) || ((chi[0])[0] == 67) || ((chi[0])[0] == 68)) && ((chi[0].length() > 1) && ((chi[0])[1] == 46)));
		}
		term2 = ((changeToUp(chi[0]).compare("A")) == 0) || ((changeToUp(chi[0]).compare("A.")) == 0) || ((changeToUp(chi[0]).compare("B")) == 0) || ((changeToUp(chi[0]).compare("B.")) == 0) || ((changeToUp(chi[0]).compare("C")) == 0) || ((changeToUp(chi[0]).compare("C.")) == 0) || ((changeToUp(chi[0]).compare("D")) == 0) || ((changeToUp(chi[0]).compare("D.")) == 0);
		if (term1||term2)
		{
			term1 = true;
			term2 = false;
			if (((chi[1])[1] >= 65 && (chi[1])[1] <= 90) || ((chi[1])[1] >= 97 && (chi[1])[1] <= 122))
			{
				analysis((char*)chi[1].c_str());
				cout << "\n";
				textEOF = false;
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					term1 = (chi[0])[1] >= 65 && (chi[0])[1] <= 90 || ((chi[0])[1] >= 97 && (chi[0])[1] <= 122);
					term2 = ((changeToUp(chi[1]).compare("A")) == 0) || ((changeToUp(chi[1]).find("A.")) != string::npos) || ((changeToUp(chi[1]).compare("B")) == 0) || ((changeToUp(chi[1]).find("B.")) != string::npos) || ((changeToUp(chi[1]).compare("C")) == 0) || ((changeToUp(chi[1]).find("C.")) != string::npos) || ((changeToUp(chi[1]).compare("D")) == 0) || ((changeToUp(chi[1]).find("D.")) != string::npos);
					if (term1 && term2)
					{
						cout << chi[1] << " ";
						analysis((char*)chi[0].c_str());
						cout << "\n";
						textEOF = false;
					}
					if ((chi[0].length() > 2))
					{
						if ((((chi[0])[2] >= 65 && (chi[0])[2] <= 90) || ((chi[0])[2] >= 97 && (chi[0])[2] <= 122)) && (((changeToUp(chi[0]))[0] == 65) || ((changeToUp(chi[0]))[0] == 66) || (changeToUp(chi[0])[0] == 67) || (changeToUp(chi[0])[0] == 68)) && ((chi[0])[1] == 46))
						{
							cout << (chi[0])[0] << ". ";
							temp = chi[0];
							temp.erase(0, 2);
							analysis((char*)temp.c_str());
							cout << "\n";
							textEOF = false;
						}
					}
					chi[1] = chi[0];
					text >> chi[0];
					if (text.eof())
					{
						break;
					}
				}

			}
			break;
		}
		chi[1] = chi[0];
		num_chiCom++;
	}
	int eng_num = 0;
	if (textEOF)
	{
		string eng;
		text.close();
		imgPross("eng", 45);
		system("cls");
		ifstream text;
		text.open("text.txt", ios::in);
		term1 = true;
		term2 = false;
		while (!text.eof())
		{
			text >> eng;
			if (eng[1] >= 65 && eng[1] <= 90 || eng[1] >= 97 && eng[1] <= 122)
			{
				analysis((char*)eng.c_str());
				cout << "\n";
			}
		}
	}
}