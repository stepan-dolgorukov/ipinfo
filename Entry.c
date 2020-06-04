#include <stdio.h>
#include <wininet.h>
#include "Request.h"


int main(void)
{
	const char* pUrl = "api.myip.com";
	char reqBuffer[1024] = {};
	BOOL sendResult = SendRequest(pUrl, reqBuffer, sizeof(reqBuffer) * sizeof(char));
	if (sendResult)
	{
		IPINFO stIpInfo = {};
		BOOL parseResult = parseRequestBuffer(reqBuffer, &stIpInfo);
		if (parseResult)
		{
			printf("%s\n%s\n%s\n", 
				stIpInfo.ip, 
				stIpInfo.country,
				stIpInfo.countryCode);
		}
	}
	return 0;
}