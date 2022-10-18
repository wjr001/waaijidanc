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


bool analysis(char* vocabulary) {
	//获取词汇解释
	if (!HttpGetReq(vocabulary))
	{
		system("pause");
		exit(1);
	}

	//读取json文件
	ifstream jsonFile;
	jsonFile.open("finalData.json", ios::in);
	string jsonData;
	string jsonReadTemp;
	while (!jsonFile.eof())
	{
		jsonData = jsonData + " " + jsonReadTemp;
		jsonFile >> jsonReadTemp;
	}
	//cout << jsonData;
	jsonFile.close();

	//开始解析
	Json::Value jsonValue;
	Json::Reader jsonReader;
	system("chcp 65001");
	if (jsonReader.parse(jsonData, jsonValue))
	{
		Json::Value jsonMssage = jsonValue["message"][0];
		int i1 = 0;
		int i2 = 0;
		cout << "\n" << vocabulary;
		while (true)
		{
			Json::Value jsonMeans1 = jsonMssage["means"][i1];
			if (jsonMeans1["part"].asString().empty())
			{
				break;
			}
			Json::Value jsonMeans2 = jsonMeans1["means"];
			cout << "\n" << jsonMeans1["part"].asString() << " ";
			while (true)
			{
				if (jsonMeans2[i2].asString().empty())
				{
					i2 = 0;
					break;
				}
				else
				{
					cout << jsonMeans2[i2].asString() << "; ";
				}
				i2++;
			}
			i1++;
		}
		return true;
	}
	else
	{
		cout << "解析json失败";
		return false;
	}

}