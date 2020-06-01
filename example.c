// author: DolgorukovGTA
#include <stdio.h>
#include "wininet.h"


typedef struct
{
	// max: 255.255.255.255 (3 + 1 + 3 + 1 + 3 + 1 + 3)
	// 4 + 4 + 4 + 3 = 12 + 3 = 15
	char
		ip[16],
		country[40],
		countryCode[3];
} IPINFO;


char* cut(char* str, unsigned start, unsigned end)
{
	if (!strlen(str) || start >= end)
	{
		return NULL;
	}

	size_t strSize = end - start + 2;
	char* retStr = (char*)calloc(strSize, sizeof(char));
	memset(retStr, strSize, '\0');

	for (int i = 0; i < strSize - 1; i++)
	{
		retStr[i] = str[i + start];
	}

	return retStr;
}


BOOL parseRequestBuffer(char* reqBuffer, IPINFO* stInfo)
{
	if (!strlen(reqBuffer))
	{
		return 0;
	}

	typedef struct
	{
		int start, end;
	} pair;

	pair array[6] = {0};
	unsigned curPairIndex = 0;
	for (unsigned i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		array[i].start = -1;
		array[i].end = - 1;
	}

	for (unsigned i = 0; reqBuffer[i]; i++)
	{
		if (reqBuffer[i] == '"')
		{
			if (array[curPairIndex].start == -1)
			{
				array[curPairIndex].start = i;
			}
			else
			{
				array[curPairIndex].end = i;
				++curPairIndex;
			}
		}
	}

	char* strings[6] = {0};
	for (unsigned i = 0; i < sizeof(array) / sizeof(pair); i++)
	{
		strings[i] = cut(reqBuffer, array[i].start + 1, array[i].end - 1);
	}

	strcpy(stInfo->ip, strings[1]);
	strcpy(stInfo->country, strings[3]);
	strcpy(stInfo->countryCode, strings[5]);

	for (unsigned i = 0; i < sizeof(strings) / sizeof(strings[0]); i++)
	{
		free(strings[i]);
	}

	return 1;
}


BOOL SendRequest(const char* url, char* reqBuffer, size_t reqBufferSize)
{
	BOOL retResult = 0;
	HINTERNET hInet = InternetOpen("",
		INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInet)
	{
		HINTERNET hInetSession = InternetConnect(hInet,
		url, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL,
		INTERNET_SERVICE_HTTP, 0, 0);
		if (hInetSession)
		{
			HINTERNET hInetSessionRequest = HttpOpenRequest(hInetSession,
				"GET", "index.php", NULL, NULL, NULL,
				INTERNET_FLAG_RELOAD, 0);
			if (hInetSessionRequest)
			{
				BOOL sendResult = HttpSendRequest(hInetSessionRequest,
					NULL, 0, NULL, 0);
				if (sendResult)
				{
					DWORD dwReadBytes = 0;
					BOOL readResult = InternetReadFile(hInetSessionRequest, reqBuffer,
						reqBufferSize - 1, &dwReadBytes);
					if (readResult)
					{
						retResult = 1;
					}
				}
			}
			InternetCloseHandle(hInetSessionRequest);
		}
		InternetCloseHandle(hInetSession);
	}
	InternetCloseHandle(hInet);
	return retResult;
}


int main(void)
{
	char reqBuffer[256] = {0}; // {"ip":"194.35.233.242","country":"United Kingdom","cc":"GB"}
	BOOL sendResult = SendRequest("api.myip.com", reqBuffer, sizeof(reqBuffer) * sizeof(char));
	if (sendResult)
	{
		IPINFO stInfo = {0};
		BOOL parseResult = parseRequestBuffer(reqBuffer, &stInfo);
		if (parseResult)
		{
			printf("IP: %s\nCountry: %s\nCC: %s\n",
				stInfo.ip, stInfo.country, stInfo.countryCode);
		}
	}
	return 0;
}
