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
bool imgPross(const char* item);
string changeToLow(string str);

int main()
{
	//system("chcp 65001"); 
	imgPross("chi_sim");
	ifstream text;
	text.open("text.txt", ios::in);
	string chi[2];
	string chiCom[64];
	int num_chiCom = 0;
	text >> chi[0];
	while (!text.eof())
	{
		chiCom[num_chiCom] = chi[0];
		chi[1] = chi[0];
		text >> chi[0];
		if (((chi[0].compare("A"))==0)|| ((chi[0].compare("A.")) == 0))
		{
			if (((chi[1])[0]>=65 && (chi[1])[0]<=90)||((chi[1])[0]>=97 && (chi[1])[0]<=122))
			{
				analysis((char*)chi[1].c_str());
			}
			else
			{
				for (int i = 0; i < 8; i++)
				{
					chi[1] = chi[0];
					text >> chi[0];
					if (i%2==0)
					{
						cout<<"\n\n" << chi[1]<<" ";
						analysis((char*)chi[0].c_str());
					}
				}
			}
			break;
		}
		num_chiCom++;
	}
	if (text.eof())
	{
		string eng;
		text.close();
		imgPross("eng");
		ifstream text;
		text.open("text.txt", ios::in);
		while (!text.eof())
		{
			text >> eng;
			for (int i = 0; i <= num_chiCom; i++)
			{
				bool a = (chiCom[i])[0] >= 65 && (chiCom[i])[0] <= 90 || (chiCom[i])[0] >= 97;
				bool b = (changeToLow(eng)).compare(changeToLow(chiCom[i]));
				if (a  && b)
				{
					analysis((char*)eng.c_str());
					break;
				}
			}
		}
	}
	text.close();
	/*
	while (!text.eof())
	{
		text >> textTemp;
		
	}
	*/
	return 0;

}
