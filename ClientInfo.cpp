#include "Types.h"

ClientInfo::ClientInfo(sockaddr_in _data, SOCKET _socket, std::thread _thread)// : thread(std::ref(_thread))
{
	data = _data;
	socket = _socket;
}