typedef struct
{
	char 
		ip[16], 
		country[40], 
		countryCode[3];
} IPINFO;


BOOL parseRequestBuffer(char* reqBuffer, IPINFO* stInfo);
BOOL SendRequest(const char* url, char* reqBuffer, size_t reqBufferSize);