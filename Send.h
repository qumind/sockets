#include <winsock2.h>
#include <string>
#include <windows.h>
#include <stdint.h>
#include "Types.h"

#pragma once

bool SendChar(SOCKET sk, char* data);
bool SendString(SOCKET sk, std::string data);
bool SendUint32(SOCKET sk, uint32_t data);
bool SendLL(SOCKET sk, long long data);
bool SendBlock(SOCKET s, block blk);

