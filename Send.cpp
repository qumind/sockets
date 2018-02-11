#include "Types.h"

bool SendChar(SOCKET sk, char* data)
{
	uint32_t _size;
	_size = strlen(data);
	if (send(sk, (char*)&_size, 4, 0) < 0)
	{
		printf_s("Error in SendString(): %d\n", WSAGetLastError());
		return false;
	}
	if (send(sk, data, _size, 0) < 0)
	{
		printf_s("Error in SendString(): %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool SendString(SOCKET sk, std::string data)
{
	uint32_t _size = data.size();
	if (send(sk, (char*)&_size, 4, 0) < 0)
	{
		printf_s("Error in SendString(): %d\n", WSAGetLastError());
		return false;
	}
	if (send(sk, data.c_str(), _size, 0) < 0)
	{
		printf_s("Error in SendString(): %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool SendUint32(SOCKET sk, uint32_t data)
{
	if (send(sk, (char*)&data, 4, 0) < 0)
	{
		printf_s("Error in SendString(): %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool SendLL(SOCKET sk, long long data)
{
	if (send(sk, (char*)&data, 8, 0) < 0)
	{
		printf_s("Error in SendLL(): %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool SendBlock(SOCKET s, block& blk)
{
	if (!SendString(s, blk.HASH_PREV) || !SendString(s, blk.HASH_MRKL_ROOT) || !SendString(s, blk.HASH_BLOCK))
	{
		printf_s("Error sending block data %d\n", WSAGetLastError());
		return false;
	}
	if (!SendUint32(s, blk.MRKL_TRANSACTIONS.size()))
	{
		printf_s("Error sending counter of transactions: %d\n", WSAGetLastError());
		return false;
	}

	if (send(s, (char*)blk.NONCE, 8, 0) < 0)
	{
		printf_s("Error receiving nonce: %d/n", WSAGetLastError());
		return false;
	}
	if (send(s, (char*)blk.time, 8, 0) < 0)
	{
		printf_s("Error receiving time: %d/n", WSAGetLastError());
		return false;
	}
	if (send(s, (char*)blk.timer, 8, 0) < 0)
	{
		printf_s("Error receiving timer: %d/n", WSAGetLastError());
		return false;
	}
	return true;
}
