#ifndef ROUTE_COMMON_H
#define ROUTE_COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPV4_BITS 32

// Convert an integer IPv4 address to string format
void intToIp(int ip, char *ipStr);

// convert a string IPv4 address to integer format
int ipToInt(const char *ip);

// Convert an IPv4 address and prefix length to binary string
bool ipv4ToBinary(const char *ip, int prefixLength, char *binary);

// Convert a binary string to string IPv4 address
bool binaryToIpv4String(const char *binary, char *ip);
#endif // ROUTE_COMMON_H