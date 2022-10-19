#include <iostream>
#include <winsock2.h> //��ͷ�ļ�����windows.h֮ǰ
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
    //1.��ʼ���׽��ֿ�
    WORD socket_version = MAKEWORD(2, 2); //�׽��ְ汾
    WSADATA wsaData;
    int flag_init_socket = WSAStartup(socket_version, &wsaData);//
    if (flag_init_socket != 0)
    {
        cout << "��ʼ���׽���ʧ��" << endl;
        WSACleanup();
        return false;
    }

    //2.����socket
    //AF_INET ָ����IPV4Э�� //sock_stream ���б��ϵ�(���ܱ�֤������ȷ���͵��Է�)�������ӵ�SOCKET��tcpЭ�����Ӧ
    //IPPROTO_TCP:�������õ�Э������
    //socket�������壺1.�����Э�� 2.�������ݵķ�ʽ 3.������Э������
    SOCKET m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//
    const char* host_url = "dict.iciba.com";
    struct hostent* host_info;
    host_info = gethostbyname(host_url);//
    //host_infoΪ�� ˵��û�и���Ϣ
    if (host_info == nullptr)
    {
        cout << "������urlʧ�ܣ�" << endl;
        closesocket(m_socket);
        WSACleanup();
        return false;
    }

    //���÷�����SocketAddr����--������ip��ַ�Ͷ˿ں�
    //���ñ�Ҫsocket��ַ��Ϣ  ��������ַ �˿ں�
    //���ж˿ںŶ�Ӧ��Ӧ���� --��80--��http���� https://blog.csdn.net/qq_25184739/article/details/70653216
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(80); //80�˿ڱ�ʾhttp�˿�
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host_info->h_addr); //����������ĵ�ַ ��host_info��ȡ
    //cout << host_info->h_addr;
    //3.���ӵ�������
    int flag_connect_socket = connect(m_socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));//
    if (flag_connect_socket != 0)
    {
        cout << "connect to server fail!" << endl;
        closesocket(m_socket);
        WSACleanup();
        return false;
    }

    //4.����GET���� 
    //����get������
    //const char* req_header = "GET /HTTP/1.1\r\n"; //����ͷ
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
        //5.���շ�������Ӧ������
        char* recvBuffer = (char*)malloc(40960);
        BOOL bOptVal = TRUE;
        int recvDataLength = recv(m_socket, recvBuffer, 40960, 0);
        while (recvDataLength > 0)
        {
            ofstream recvData; //���ܵ�������//
            recvData.open("recvData.tmp", ios::out | ios::trunc);
            ofstream finalData; //������Ҫ�����ݣ�json��
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
            //temp << "���ص�����Ϊ:\n" << endl;

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
        cout << "����ʧ��";
        closesocket(m_socket);
        WSACleanup();
        return false;
    }
    //6.�ر�����
    closesocket(m_socket);
    WSACleanup();
    return true;
}