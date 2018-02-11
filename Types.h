#include <winsock2.h>
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <conio.h>
#include <thread>
#include <typeinfo>

#pragma once
#pragma comment (lib, "Ws2_32.lib")

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define PORT 20055
#define sunb sin_addr.S_un.S_un_b

enum Requests : uint32_t
{
	GetNodesList = 0,
	TakeBlock = 1,
	TakeTransaction = 2
};

class ClientInfo
{
public:
	sockaddr_in data;
	SOCKET socket;
	std::thread thread;
	ClientInfo(sockaddr_in _data, SOCKET _socket, std::thread _thread);
};

struct block
{
	std::string HASH_PREV, HASH_MRKL_ROOT, HASH_BLOCK;
	std::vector <std::string> MRKL_TRANSACTIONS;
	long long NONCE;
	time_t time;
	clock_t timer;
};