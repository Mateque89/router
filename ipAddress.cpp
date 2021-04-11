#include <iostream>
#include <arpa/inet.h>
#include <string>
#include "utility.h"
#include "ipAddress.h"

using namespace std;

string ipAddress::formatSubnet(uint16_t bits)
{
    uint64_t ip = ~((1 << (32 - bits)) - 1);
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    string result = "";
    for (int i = 3; i >= 0; i--)
    {
        result.append(to_string(bytes[i]));
        if (i != 0)
            result.append(".");
    }
    return result;
}

ipAddress::ipAddress(string Iaddr, string Imask)
{
    ip = Iaddr;
    mask = stoi(Imask);
}
string ipAddress::calculateBroadcast()
{
    vector<string> arrIP = tokenize(ip, ".");
    vector<string> arrMask = tokenize(formatSubnet(mask), ".");
    string result = "";

    for (int i = 0; i < 4; i++)
    {
        uint16_t byte = stoi(arrIP[i]) | (stoi(arrMask[i]) ^ 255);
        result.append(to_string(byte));
        if (i != 3)
            result.append(".");
    }
    return result;
}
string ipAddress::calculateNetwork()
{
    vector<string> arrIP = tokenize(ip, ".");
    vector<string> arrMask = tokenize(formatSubnet(mask), ".");
    string result = "";

    for (int i = 0; i < 4; i++)
    {
        uint16_t byte = stoi(arrIP[i]) & stoi(arrMask[i]);
        result.append(to_string(byte));
        if (i != 3)
            result.append(".");
    }
    return result;
}
string ipAddress::calculateCidr()
{
    return ip.append("/").append(to_string(mask));
}
string ipAddress::calculateNetworkToCidr()
{
    string nt = calculateNetwork();
    return nt.append("/").append(to_string(mask));
}