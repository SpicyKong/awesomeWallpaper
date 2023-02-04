#include "Server.h"

Server::Server()
{
	if (WSAStartup(MAKEWORD(2, 2), &winSockApi) != 0)
		errorHandle("������ ���� ���̺귯�� �ʱ�ȭ �������� ������ �߻��߽��ϴ�.");
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
		errorHandle("��û ��Ŷ�� ������ �ֽ��ϴ�.");
	std::string body(ptrBody);
	if (programTable.count(body) > 0)
		excute(body);
	closesocket(client);
}

void Server::init()
{
	// ���Ͽ� ���ε��ϱ� �� ���� �Է��ϱ�
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAdr, 0, sizeof(serverAdr));
	serverAdr.sin_family = AF_INET;
	serverAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAdr.sin_port = htons(5000);

	// ���� �ҷ��ͼ� map�� ���
	std::ifstream file;
	std::string line;
	file.open("test.txt");

	if (!file.is_open())
	{
		errorHandle("������ ã�� �� �����ϴ�.");
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
			errorHandle("���� ���� ����: �ùٸ��� ���� ��Ģ�Դϴ�.");
		}
		Server::programTable[program[0]] = program[1];
	}
	file.close();
}

void Server::run()
{
	

	

	if (bind(serverSocket, (SOCKADDR*)&serverAdr, sizeof(serverAdr)) == SOCKET_ERROR)
		errorHandle("bind() error");
	// �������� ���ε�
	if (listen(serverSocket, 5) == SOCKET_ERROR) // listen�Լ��� �ι�° ������ backlog�� ������ ������ Ŭ���̾�Ʈ ť�� ũ�⸦ ��Ÿ��
		errorHandle("listen() error");
	// ���� �����忡�� �������� ������
	SOCKET clientSocket;
	SOCKADDR_IN clientAdr;
	int clientAdrSize;
	while (1)
	{
		clientAdrSize = sizeof(clientAdr);
		clientSocket= accept(serverSocket, (SOCKADDR*)&clientAdr, &clientAdrSize);
		if (inet_ntoa(clientAdr.sin_addr) != inet_ntoa(serverAdr.sin_addr))
			continue; // �ܺ� �����ǿ��� �����ϸ� ����
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