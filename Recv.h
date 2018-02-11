#include <winsock2.h>
#include <string>
#include <windows.h>
#include <stdint.h>

#pragma once

bool RecvChar(SOCKET sk, char* data, uint32_t _buffsize);
bool RecvString(SOCKET sk, std::string& data);
uint32_t RecvUint32(SOCKET sk);
uint32_t RecvReq(SOCKET sock);
