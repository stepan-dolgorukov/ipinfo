#include <stdio.h>
#include <wininet.h>
#include "Request.h"


char* strcut(char* str, unsigned int start, unsigned int end)
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
	unsigned int curPairIndex = 0;
	for (unsigned i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		array[i].start = -1;
		array[i].end = - 1;
	}

	for (unsigned i = 0; reqBuffer[i]; i++)
	{
		// ascii: 34 - "
		if (reqBuffer[i] == 34)
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
		strings[i] = strcut(reqBuffer, array[i].start + 1, array[i].end - 1);
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


BOOL SendRequest(
	const char* url, 
	char* reqBuffer, 
	size_t reqBufferSize)
{
	BOOL retResult = 0;
	HINTERNET hInet = InternetOpenA("User Agent",
		INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInet != NULL)
	{
		HINTERNET hInetSession = InternetConnectA(hInet,
		url, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL,
		INTERNET_SERVICE_HTTP, 0, 0);
		if (hInetSession != NULL)
		{
			HINTERNET hInetSessionRequest = HttpOpenRequestA(hInetSession,
				"GET", "/", "HTTP/1.1", NULL, NULL,
				INTERNET_FLAG_RELOAD, 0);
			if (hInetSessionRequest != NULL)
			{
				BOOL sendResult = HttpSendRequestA(hInetSessionRequest,
					NULL, 0, NULL, 0);
				if (sendResult)
				{
					DWORD dwReadBytes = 0;
					BOOL readResult = InternetReadFile(hInetSessionRequest, reqBuffer,
						reqBufferSize - 1, &dwReadBytes);
					if (readResult)
					{
						reqBuffer[dwReadBytes] = 0;
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