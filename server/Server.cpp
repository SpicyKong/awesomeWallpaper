#include "Server.h"

Server::Server() 
{

}
Server::~Server() 
{

}

unsigned WINAPI Server::requestHandle(void* arg)
{
	SOCKET client = (SOCKET)arg;
	char buf[BUF_SIZE];
	char method[BUF_SMALL];
	char ct[BUF_SMALL];
	char fileName[BUF_SMALL];

	int length = recv(client, buf, BUF_SIZE, 0);
	std::cout << length << "\n";
	buf[length] = '\0';
	std::cout << buf << "\n";
	closesocket(client);
	return 0;
}
void Server::errorHandle(const std::string message)
{

}

void Server::init()
{
	// 파일 불러오기
	try
	{
		std::ifstream file;
		std::string line;
		file.open("test.txt");

		if (!file.is_open())
		{
			file.close();
			throw "파일 에러: 파일을 찾을 수 없습니다.";
		}

		while (!file.eof())
		{
			std::getline(file, line);
			std::string program[2];
			int idx = 0, chk = 0;
			bool errChk = 0;
			while (errChk == 0 && idx < (signed)line.length())
			{
				if (chk % 2) {
					if (line[idx] == '>')
						chk++;
					else if (line[idx] != '<')
						program[chk / 2] += line[idx];
					else
						errChk = 1;
				}
				else {
					if (line[idx] == '<')
						chk++;
					else if (line[idx] != '>')
						program[chk / 2] += line[idx];
					else
						errChk = 1;
				}
				++idx;
			}
			if (errChk) {
				file.close();
				throw "파일 형식 에러: 올바르지 않은 규칙입니다.";
			}
			programTable[program[0]] = program[1];
		}
		file.close();
	}
	catch (const char* err)
	{
		std::cout << err << "\n";
	}
}

void Server::run()
{
	

	if (WSAStartup(MAKEWORD(2, 2), &winSockApi) != 0)
		errorHandle("윈도우 소켓 라이브러리 초기화 과정에서 문제가 발생했습니다.");

	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAdr, 0, sizeof(serverAdr));
	serverAdr.sin_family = AF_INET;
	serverAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAdr.sin_port = htons(atoi("5000"));

	if (bind(serverSocket, (SOCKADDR*)&serverAdr, sizeof(serverAdr)) == SOCKET_ERROR)
		errorHandle("bind() error");
	if (listen(serverSocket, 5) == SOCKET_ERROR) // listen함수의 두번째 인자인 backlog는 연결을 유지할 클라이언트 큐의 크기를 나타내는 듯
		errorHandle("listen() error");

	while (1)
	{
		clientAdrSize = sizeof(clientAdr);
		clientSocket= accept(serverSocket, (SOCKADDR*)&clientAdr, &clientAdrSize);
		printf("Connection Request : %s:%d\n",
			inet_ntoa(clientAdr.sin_addr), ntohs(clientAdr.sin_port));
		//hThread = (HANDLE)_beginthreadex(NULL, 0, requestHandle, (void*)this, 0, (unsigned*)&dwThreadId);
		hThread = (HANDLE)_beginthreadex(NULL, 0, Server::requestHandle, (void*)clientSocket, 0, (unsigned*)&dwThreadId);
		// 콜백함수로 클래스의 메소드는 사용을 못한다고 한다.
	}
}

void Server::excute(const std::string &fileName)
{

}
