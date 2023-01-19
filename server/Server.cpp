#include "Server.h"

Server::Server()
{
	if (WSAStartup(MAKEWORD(2, 2), &winSockApi) != 0)
		errorHandle("윈도우 소켓 라이브러리 초기화 과정에서 문제가 발생했습니다.");
	init();
}
Server::~Server() 
{
	WSACleanup();
}
void Server::requestHandle(SOCKET client)
{
	char buf[BUF_SIZE];

	int length = recv(client, buf, BUF_SIZE, 0);
	buf[length] = '\0';
	int chk = 0;
	char* ptrBody = NULL;
	for (int i = 0; i < length-2; i++) {
		if (buf[i] == '\r' && buf[i + 1] == '\n') {
			if (chk == 1) {
				ptrBody = buf + i + 2;
				chk = 0;
				break;
			}
			i++;
			chk = 1;
		}
		else {
			chk = 0;
		}
	}
	if (ptrBody == NULL)
		errorHandle("요청 패킷에 문제가 있습니다.");
	std::string body(ptrBody);
	if (programTable.count(body) > 0)
		excute(body);
	closesocket(client);
}

void Server::init()
{
	// 소켓에 바인드하기 전 정보 입력하기
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAdr, 0, sizeof(serverAdr));
	serverAdr.sin_family = AF_INET;
	serverAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAdr.sin_port = htons(5000);

	// 파일 불러와서 map에 등록
	std::ifstream file;
	std::string line;
	file.open("test.txt");

	if (!file.is_open())
	{
		errorHandle("파일을 찾을 수 없습니다.");
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
		if (errChk)
		{
			errorHandle("파일 형식 에러: 올바르지 않은 규칙입니다.");
		}
		Server::programTable[program[0]] = program[1];
	}
	file.close();
}

void Server::run()
{
	

	

	if (bind(serverSocket, (SOCKADDR*)&serverAdr, sizeof(serverAdr)) == SOCKET_ERROR)
		errorHandle("bind() error");
	// 위에까지 바인드
	if (listen(serverSocket, 5) == SOCKET_ERROR) // listen함수의 두번째 인자인 backlog는 연결을 유지할 클라이언트 큐의 크기를 나타냄
		errorHandle("listen() error");
	// 메인 스레드에서 서버소켓 리스닝
	SOCKET clientSocket;
	SOCKADDR_IN clientAdr;
	int clientAdrSize;
	while (1)
	{
		clientAdrSize = sizeof(clientAdr);
		clientSocket= accept(serverSocket, (SOCKADDR*)&clientAdr, &clientAdrSize);
		if (inet_ntoa(clientAdr.sin_addr) != inet_ntoa(serverAdr.sin_addr))
			continue; // 외부 아이피에서 접근하면 차단
		printf("Connection Request : %s:%d\n", inet_ntoa(clientAdr.sin_addr), ntohs(clientAdr.sin_port));
		std::thread clientThread(&Server::requestHandle, this, clientSocket);
		clientThread.detach();
	}
}

void Server::excute(const std::string &fileName)
{
	system(programTable[fileName].c_str());
}


void Server::errorHandle(const std::string message)
{
	std::cerr << message << "\n";
	exit(1);
}