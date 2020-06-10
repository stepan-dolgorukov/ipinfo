#pragma once


typedef struct
{
	char countryCode[3];
	char continentCode[3];
	unsigned int mobile, proxy, hosting, offset;
	char currency[4];
	double lat, lon;
	char timezone[8];
	char region[8];
	char zip[16];
	char query[16];
	char continent[20];
	char regionName[32];
	char city[32];
	char district[32];
	char reverse[32];
	char isp[64];
	char org[64];
	char as[64];
	char asName[64];
	char country[64];
} IPINFO;


bool sendRequest(const char* url, const char* params, char* reqBuffer, size_t reqBufferSize);
bool parseJSON(const char* reqBuffer, IPINFO* stInfo);