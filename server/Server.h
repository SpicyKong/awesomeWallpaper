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
	기본적인 로직

	1. path.txt 파일에 명령어와 경로를 다음과 같이 적어둔다.
	[chrome](C:programfiles ~~ .exe)
	[~~](~~)
	2. main 함수를 실행한다.
	3. 클라이언트에서 요청을 한다.
*/