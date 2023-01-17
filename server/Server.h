#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <process.h>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#define BUF_SIZE  12048
#define BUF_SMALL  100

class Server
{
private:
	std::map<std::string, std::string> programTable;
	int clientAdrSize;

	void errorHandle(const std::string message);
	void excute(const std::string &fileName);
	void init();
public:
	WSADATA winSockApi;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAdr, clientAdr;
	HANDLE hThread;
	DWORD dwThreadId;
	Server();
	~Server();
	static unsigned WINAPI requestHandle(void* arg);
	void run();
	void restart();
};


/*
	�⺻���� ����

	1. path.txt ���Ͽ� ��ɾ�� ��θ� ������ ���� ����д�.
	[chrome](C:programfiles ~~ .exe)
	[~~](~~)
	2. main �Լ��� �����Ѵ�.
	3. Ŭ���̾�Ʈ���� ��û�� �Ѵ�.
*/