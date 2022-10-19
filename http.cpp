#include <iostream>
#include <winsock2.h> //该头文件需在windows.h之前
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include"vld.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6387)

bool HttpGetReq(char* vocabulary)
{
    //1.初始化套接字库
    WORD socket_version = MAKEWORD(2, 2); //套接字版本
    WSADATA wsaData;
    int flag_init_socket = WSAStartup(socket_version, &wsaData);//
    if (flag_init_socket != 0)
    {
        cout << "初始化套接字失败" << endl;
        WSACleanup();
        return false;
    }

    //2.连接socket
    //AF_INET 指的是IPV4协议 //sock_stream 是有保障的(即能保证数据正确传送到对方)面向连接的SOCKET与tcp协议相对应
    //IPPROTO_TCP:传输层采用的协议类型
    //socket参数含义：1.网络层协议 2.传输数据的方式 3.传输层的协议类型
    SOCKET m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//
    const char* host_url = "dict.iciba.com";
    struct hostent* host_info;
    host_info = gethostbyname(host_url);//
    //host_info为空 说明没有该消息
    if (host_info == nullptr)
    {
        cout << "该主机url失败！" << endl;
        closesocket(m_socket);
        WSACleanup();
        return false;
    }

    //设置服务器SocketAddr类型--即包括ip地址和端口号
    //设置必要socket地址信息  服务器地址 端口号
    //其中端口号对应相应服务 --：80--》http服务 https://blog.csdn.net/qq_25184739/article/details/70653216
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(80); //80端口表示http端口
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host_info->h_addr); //请求服务器的地址 由host_info获取
    //cout << host_info->h_addr;
    //3.连接到服务器
    int flag_connect_socket = connect(m_socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));//
    if (flag_connect_socket != 0)
    {
        cout << "connect to server fail!" << endl;
        closesocket(m_socket);
        WSACleanup();
        return false;
    }

    //4.发送GET请求 
    //设置get请求报文
    //const char* req_header = "GET /HTTP/1.1\r\n"; //请求头
    //const char* total_req_header = "Host:www.baidu.com\r\nConnection: close\r\n\r\n";
    //const char* all_req_header = "GET /index.php?a=a&b=b HTTP/1.1\r\nHost:192.168.31.220\r\nConnection: close\r\n\r\n";
    const char* pre_all_req_header = "GET /dictionary/word/suggestion?word=";
    const char* after_all_req_header = "&nums=5&ck=709a0db45332167b0e2ce1868b84773e&timestamp=1665899263151&client=6&uid=123123&key=1000006&is_need_mean=1&signature=1742c201331e640b3fb83ea681ea0fcb HTTP/1.1\r\n"
        "Host: dict.iciba.com\r\n"
        "Accept: application/json, text/plain, */*\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.47\r\n"
        "Origin: http://www.iciba.com\r\n"
        "Referer: http://www.iciba.com/\r\n"
        "Accept-Encoding: deflate\r\n"
        "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6\r\n"
        "Connection: close\r\n\r\n";
    char* all_req_header = (char*)malloc(4096);//
    sprintf_s(all_req_header, 4096, "%s%s%s", pre_all_req_header, vocabulary, after_all_req_header);
    //cout<<all_req_header;
    if (send(m_socket, all_req_header, strlen(all_req_header), 0) > 0)
    {
        free(all_req_header);
        //5.接收服务器响应的数据
        char* recvBuffer = (char*)malloc(40960);
        BOOL bOptVal = TRUE;
        int recvDataLength = recv(m_socket, recvBuffer, 40960, 0);
        while (recvDataLength > 0)
        {
            ofstream recvData; //接受到的数据//
            recvData.open("recvData.tmp", ios::out | ios::trunc);
            ofstream finalData; //最终需要的数据（json）
            finalData.open("finalData.json", ios::out | ios::trunc);
            long i = 0;
            while (i < recvDataLength && recvBuffer[i] != 123)
            {
                recvData << recvBuffer[i];
                i++;
            }
            if (recvBuffer[i] == 123)
            {
                while (i < recvDataLength)
                {
                    recvData << recvBuffer[i];
                    finalData << recvBuffer[i];
                    i++;
                }
            }
            //temp << "传回的数据为:\n" << endl;

            /*
            long i = 0;
            char tp= recvBuffer[i];
            while ((tp >= 32) || tp == '\n' || tp == '\r' )
            {
                cout << recvBuffer[i];
                i += 1;
                tp = recvBuffer[i];
            }
            */
            recvData.close();
            finalData.close();
            free(recvBuffer);
            break;
        }

    }
    else
    {
        cout << "发送失败";
        closesocket(m_socket);
        WSACleanup();
        return false;
    }
    //6.关闭连接
    closesocket(m_socket);
    WSACleanup();
    return true;
}