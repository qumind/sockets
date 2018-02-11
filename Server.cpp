#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Types.h"
#include "Recv.h"
#include "Send.h"

#pragma comment (lib, "Ws2_32.lib")

#define PORT 20055
#define sunb sin_addr.S_un.S_un_b

std::vector<char*> nodeList;
std::vector<char*> transactionStack;
char alwaysUpServ[15] = { 0 };
char Block[512] = { 0 };
std::vector<ClientInfo> ClientInfoVec;

block BLOCK;

bool ReadConfigFile()
{
	FILE* configFile = fopen("server.config", "r");
	if (configFile == 0)
	{
		printf("Error reading .config file\n");
		return 0;
	}
	fscanf_s(configFile, "%s", alwaysUpServ);
	fclose(configFile);
	return 1;
}

void ClientService(SOCKET _sk, int iterator)
{
	uint32_t reqw = RecvReq(_sk);
	uint32_t size = 0;
	char* trans = nullptr;
	switch (reqw)
	{
	case Requests::GetNodesList:
		for (int i = 0; i < nodeList.size() - 1; i++)
		{
			SendChar(_sk, nodeList[i]);
		}
		break;
	case Requests::TakeTransaction:
		if (!RecvUint32(_sk))
		{
			printf("Error receiving transaction size: %d\n", WSAGetLastError());
		}
		if (!RecvChar(_sk, trans, size))
		{
			printf("Error receiving transaction: %d\n", WSAGetLastError());
		}
		transactionStack.push_back(trans);
		ZeroMemory(trans, size);
		break;
	case Requests::TakeBlock:
		if (!RecvString(_sk, BLOCK.HASH_PREV) || !RecvString(_sk, BLOCK.HASH_MRKL_ROOT) || !RecvString(_sk, BLOCK.HASH_BLOCK))
			printf_s("Error receiving block data: %d\n", WSAGetLastError());
		uint32_t countT;
		std::string buf;
		if (countT = RecvUint32(_sk) != -1)
		{
			printf_s("Error receiving counter: %d\n", WSAGetLastError());
			break;
		}
		for (int _i = 0; _i < countT; _i++)
		{
			if (!RecvString(_sk, buf))
			{
				printf_s("Error receiving transaction: %d\n", WSAGetLastError());
				break;
			}
			else
			{
				BLOCK.MRKL_TRANSACTIONS.push_back(buf);
			}
		}
		if (recv(_sk, (char*)BLOCK.NONCE, 8, 0) < 0)
		{
			printf_s("Error receiving nonce: %d/n", WSAGetLastError());
			break;
		}
		if (recv(_sk, (char*)BLOCK.time, 8, 0) < 0)
		{
			printf_s("Error receiving time: %d/n", WSAGetLastError());
			break;
		}
		if (recv(_sk, (char*)BLOCK.timer, 8, 0) < 0)
		{
			printf_s("Error receiving timer: %d/n", WSAGetLastError());
			break;
		}
		break;
	}
}

bool WriteTransaction()
{
	transactionStack.clear();
	return true;
}

void ipOut(sockaddr_in info)
{
	printf_s("%d.%d.%d.%d", info.sunb.s_b1, info.sunb.s_b2, info.sunb.s_b3, info.sunb.s_b4);
}

int main()
{
	SOCKET serverSocket;
	SOCKET client;
	WSAData wsaData;
	sockaddr_in serverAddr, getAddr;
	int Status;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = 0;

	ReadConfigFile();

	getAddr.sin_family = AF_INET;
	getAddr.sin_port = htons(PORT);
	getAddr.sin_addr.s_addr = inet_addr(alwaysUpServ);
	
	if (WSAStartup(0x202, &wsaData))
	{
		printf_s("Error in WSAStartup(): %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	
	if (client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) == INVALID_SOCKET)
	{
		printf_s("Error creating socket: %d\n", WSAGetLastError());
		return 0;
	}

	if (connect(client, (sockaddr*)&getAddr, sizeof(getAddr)) < 0)
	{
		printf_s("Error connection to always up server: %d\n", WSAGetLastError());
		return 0;
	}

	if (!SendUint32(client, Requests::GetNodesList))
	{
		printf_s("Error sending request %d\n", WSAGetLastError());
		return 0;
	}
	uint32_t count;
	char buf[15];

	if (count = RecvUint32(client) == -1)
	{
		printf_s("Error receiving count of nodes %d\n", WSAGetLastError());
		return 0;
	}

	for (int _i = 0; _i < count; _i++)
	{
		if (!RecvChar(client, buf, 15))
		{
			printf_s("Error receiving addres %d\n", WSAGetLastError());
			return 0;
		}
		nodeList.push_back(buf);
		ZeroMemory(buf, 15);
	}

	closesocket(client);
	serverSocket = socket(serverAddr.sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		printf_s("Error in socket(): %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	printf_s("Socket created\n");
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(sockaddr)) > 0)
	{
		printf("Error in bind(): %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	printf_s("Socket binded\n");
	if (listen(serverSocket, SOMAXCONN) > 0)
	{
		printf_s("Error in listen(): %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	int len = sizeof(sockaddr);
	int i = 0;
	while (true)
	{
		sockaddr_in info;
		SOCKET clientSocket = accept(serverSocket, (sockaddr*)&info, &len);
		if (clientSocket == INVALID_SOCKET)
		{
			printf_s("Error in accept %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
		}
		else
		{
			printf_s("Accepted connection: %d.%d.%d.%d", info.sunb.s_b1, info.sunb.s_b2, info.sunb.s_b3, info.sunb.s_b4);
			auto t = std::thread(ClientService, clientSocket, i);
			ClientInfoVec.push_back(ClientInfo(info, clientSocket, std::move(t)));
			ClientInfoVec[i].thread.detach();
			i++;
		}
	}
	ClientInfoVec.clear();
}