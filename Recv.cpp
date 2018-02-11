#include "Recv.h"
#include "Types.h"

bool RecvChar(SOCKET sk, char* data, uint32_t _buffsize)
{
	uint32_t _size = 0;
	if (recv(sk, (char*)&_size, 4, 0) < 0)
	{
		printf_s("Error in RecvString(): %d\n", WSAGetLastError());
		return false;
	}
	char* _buff = new char[_size];
	memset(data, 0, _buffsize);
	memcpy(data, _buff, MIN(_size, _buffsize));
	return true;
}

bool RecvString(SOCKET sk, std::string& data)
{
	uint32_t _size;
	if (recv(sk, (char*)&_size, 4, 0) < 0)
	{
		printf_s("Error in RecvString(): %d\n", WSAGetLastError());
		return false;
	}
	char* _buff = new char[_size];
	data = std::string(_buff);
	return true;
}

uint32_t RecvUint32(SOCKET sk)
{
	uint32_t res;
	if (recv(sk, (char*)&res, 4, 0) < 0)
	{
		printf_s("Error receiving data: %d\n", WSAGetLastError());
		return -1;
	}
	return res;
}

uint32_t RecvReq(SOCKET sock)
{
	uint32_t request = 0;
	if (recv(sock, (char*)request, 4, 0) < 0)
	{
		printf("Error in RecvReq(): %d\n", WSAGetLastError());
		return 0;
	}
	else
		return request;
}
