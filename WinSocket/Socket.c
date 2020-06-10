#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h> // linking: Ws2_32
#include "Socket.h"
#include "../cJSON/cJSON.h"


bool parseJSON(const char* reqBuffer, IPINFO* pIpInfo)
{
	BOOL retResult = true; // if value is 1 that's o'k
	cJSON* pData = cJSON_Parse(reqBuffer);
	if (pData != NULL)
	{
		const cJSON* status = cJSON_GetObjectItemCaseSensitive(pData, "status");
		if (status->valuestring != NULL && strcmp(status->valuestring, "success") == 0)
		{
			const char 
				*continent = cJSON_GetObjectItemCaseSensitive(pData, "continent")->valuestring,
				*continentCode = cJSON_GetObjectItemCaseSensitive(pData, "continentCode")->valuestring,
				*country = cJSON_GetObjectItemCaseSensitive(pData, "country")->valuestring,
				*countryCode = cJSON_GetObjectItemCaseSensitive(pData, "countryCode")->valuestring,
				*region = cJSON_GetObjectItemCaseSensitive(pData, "region")->valuestring,
				*regionName = cJSON_GetObjectItemCaseSensitive(pData, "regionName")->valuestring,
				*city = cJSON_GetObjectItemCaseSensitive(pData, "city")->valuestring,
				*district = cJSON_GetObjectItemCaseSensitive(pData, "district")->valuestring,
				*zip = cJSON_GetObjectItemCaseSensitive(pData, "zip")->valuestring;
			
			const double
				lat = cJSON_GetObjectItemCaseSensitive(pData, "lat")->valuedouble,
				lon = cJSON_GetObjectItemCaseSensitive(pData, "lon")->valuedouble;

			const char* timezone = cJSON_GetObjectItemCaseSensitive(pData, "timezone")->valuestring;
			const u_int offset = cJSON_GetObjectItemCaseSensitive(pData, "offset")->valueint;

			const char
				*currency = cJSON_GetObjectItemCaseSensitive(pData, "currency")->valuestring,
				*isp = cJSON_GetObjectItemCaseSensitive(pData, "isp")->valuestring,
				*org = cJSON_GetObjectItemCaseSensitive(pData, "org")->valuestring,
				*as = cJSON_GetObjectItemCaseSensitive(pData, "as")->valuestring,
				*asName = cJSON_GetObjectItemCaseSensitive(pData, "asname")->valuestring,
				*reverse = cJSON_GetObjectItemCaseSensitive(pData, "reverse")->valuestring;
			
			const u_int
				mobile = cJSON_GetObjectItemCaseSensitive(pData, "mobile")->valueint,
				proxy = cJSON_GetObjectItemCaseSensitive(pData, "proxy")->valueint,
				hosting = cJSON_GetObjectItemCaseSensitive(pData, "hosting")->valueint;
			
			const char* query = cJSON_GetObjectItemCaseSensitive(pData, "query")->valuestring;

			strcpy(pIpInfo->continent, continent);
			strcpy(pIpInfo->continentCode, continentCode);
			strcpy(pIpInfo->country, country);
			strcpy(pIpInfo->countryCode, countryCode);
			strcpy(pIpInfo->region, region);
			strcpy(pIpInfo->regionName, regionName);
			strcpy(pIpInfo->city, city);
			strcpy(pIpInfo->district, district);
			strcpy(pIpInfo->zip, zip);
			pIpInfo->lat = lat;
			pIpInfo->lon = lon;
			strcpy(pIpInfo->timezone, timezone);
			pIpInfo->offset = offset;
			strcpy(pIpInfo->currency, currency);
			strcpy(pIpInfo->isp, isp);
			strcpy(pIpInfo->org, org);
			strcpy(pIpInfo->as, as);
			strcpy(pIpInfo->asName, asName);
			strcpy(pIpInfo->reverse, reverse);
			pIpInfo->mobile = mobile;
			pIpInfo->proxy = proxy;
			pIpInfo->hosting = hosting;
			strcpy(pIpInfo->query, query);
		}
	}

	else
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Parsing error before: %s\n", error_ptr);
			retResult = false;
		}

		else
		{
			fprintf(stderr, "Unexpected parsing error.\n");
		}
		
	}
	cJSON_Delete(pData);
	return retResult;
}


bool sendRequest(
    const char* url, 
    const char* params,
    char* reqBuffer, 
    size_t reqBufferSize)
{
	bool retValue = false;
    WSADATA stWsaData = {};
    if (!WSAStartup(MAKEWORD(2, 2), &stWsaData))
    {
        SOCKET hSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (hSocket != INVALID_SOCKET)
        {   
            PHOSTENT pHost = gethostbyname(url);

            SOCKADDR_IN stSockAddr = {};
            stSockAddr.sin_family = AF_INET;
            stSockAddr.sin_port = htons(80);
            stSockAddr.sin_addr.S_un.S_addr = *(u_long*)pHost->h_addr_list[0]; // cast char* into u_long* and dereference that

            if (!connect(hSocket, (SOCKADDR*)&stSockAddr, sizeof(stSockAddr)))
            {
				// GET /json/?fields=66846719 HTTP/1.1\nUser-Agent: User Agent\nHost: ip-api.com\nConnection: close\n\n";
                char headers[256] = "GET /";
				strcat(headers, params);
				strcat(headers, " ");
				strcat(headers, "HTTP/1.1\nUser-Agent: User Agent\nHost: ");
				strcat(headers, url);
				strcat(headers, "\nConnection: close\n\n");

                if (send(hSocket, headers, strlen(headers), 0))
                {
                    char buffer[1024] = {};
                    if (recv(hSocket, buffer, sizeof(buffer), 0) > 0)
                    {
                        char* jsonText = strstr(buffer, "{"); // remove headers from server answer, we need only json
                        if (jsonText != NULL)
                        {
                            strcpy(reqBuffer, jsonText);
							retValue = true;
                        }
                    }
                }
            }
        }
        closesocket(hSocket);
    }

    WSACleanup();
	return retValue;
}
