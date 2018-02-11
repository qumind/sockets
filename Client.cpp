#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int client()
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	char *sendbuf = "give";
	char recvbuf[DEFAULT_BUFLEN] = { 0 };
	char BLOCK[900];
	int iResult;
	int recvbuflen = 14;

	// Validate the parameter

	// Initialize Winsock
	scanf("%s", BLOCK);
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		_getch();
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("178.74.227.157", DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		_getch();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			_getch();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		_getch();
		return 1;
	}

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		_getch();
		return 1;
	}

	char *blockLen, string[3] = "";
	blockLen = _itoa(strlen(BLOCK), string, 10);
	iResult = send(ConnectSocket, blockLen, (int)strlen(blockLen), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		_getch();
		return 1;
	}
	iResult = send(ConnectSocket, BLOCK, (int)strlen(BLOCK), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		_getch();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		_getch();
		return 1;
	}

	// Receive until the peer closes the connection
	do
	{

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf_s("Bytes received: %d\n", iResult);
			printf_s("%s\n", recvbuf);

		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
			system("pause");
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			system("pause");
		}

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	system("pause");
	return 0;
}