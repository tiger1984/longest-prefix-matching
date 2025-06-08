#include "RouteCommon.h"
// Convert an integer IPv4 address to string format
void intToIp(int ip, char *ipStr) {
    sprintf(ipStr, "%u.%u.%u.%u", 
            (ip >> 24) & 0xFF, 
            (ip >> 16) & 0xFF, 
            (ip >> 8) & 0xFF, 
            ip & 0xFF);
}

// convert a string IPv4 address to integer format
int ipToInt(const char *ip) {
    unsigned int octets[4];
    sscanf(ip, "%u.%u.%u.%u", &octets[0], &octets[1], &octets[2], &octets[3]);
    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
}

// Convert an IPv4 address and prefix length to binary string
bool ipv4ToBinary(const char *ip, int prefixLength, char *binary) {
    unsigned int octets[4];
    sscanf(ip, "%u.%u.%u.%u", &octets[0], &octets[1], &octets[2], &octets[3]);
    int bitIndex = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            if (bitIndex < prefixLength) {
                binary[bitIndex++] = (octets[i] & (1 << j)) ? '1' : '0';
            }
        }
    }
    binary[bitIndex] = '\0';
    return true;
}

// Convert a binary string to string IPv4 address
bool binaryToIpv4String(const char *binary, char *ip) {
    unsigned int octets[4] = {0};
    for (int i = 0; i < 32; i++) {
        if (binary[i] == '1') {
            octets[i / 8] |= (1 << (7 - (i % 8)));
        }
    }
    sprintf(ip, "%u.%u.%u.%u", octets[0], octets[1], octets[2], octets[3]);
    return true;
}
