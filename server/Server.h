#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
//#include <process.h>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <thread>

#define BUF_SIZE  65536

class Server
{
private:
	std::map<std::string, std::string> programTable;
	WSADATA winSockApi;
	SOCKET serverSocket;
	SOCKADDR_IN serverAdr;
	void errorHandle(const std::string message);
	void requestHandle(SOCKET client);
	void excute(const std::string &fileName);
	void init();
public:
	Server() ;
	~Server();
	void run();
};


/*
	�⺻���� ����

	1. path.txt ���Ͽ� ��ɾ�� ��θ� ������ ���� ����д�.
	[chrome](C:programfiles ~~ .exe)
	[~~](~~)
	2. main �Լ��� �����Ѵ�.
	3. Ŭ���̾�Ʈ���� ��û�� �Ѵ�.
*/