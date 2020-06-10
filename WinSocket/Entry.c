#include <stdio.h>
#include <stdbool.h>
#include "Socket.h"


int main(void)
{
    char reqBuffer[1024] = {};
    if (sendRequest("ip-api.com", "json/?fields=66846719", reqBuffer, sizeof(reqBuffer) * sizeof(char)))
    {
        IPINFO stIpInfo = {};
		if (parseJSON(reqBuffer, &stIpInfo))
		{
            printf("Continent name: %s\n", stIpInfo.continent);
			printf("Two-letter continent code: %s\n",  stIpInfo.continentCode);
			printf("Country name: %s\n", stIpInfo.country);
			printf("Two-letter country code ISO 3166-1 alpha-2: %s\n", stIpInfo.countryCode);
			printf("Region/state short code (FIPS or ISO): %s\n", stIpInfo.region);
			printf("Region/state: %s\n", stIpInfo.regionName);
			printf("City: %s\n", stIpInfo.city);
			printf("District (subdivision of city): %s\n", stIpInfo.district);
			printf("Zip code: %s\n", stIpInfo.zip);
			printf("Latitude: %.4f\n", stIpInfo.lat);
			printf("Longitude: %.4f\n", stIpInfo.lon);
			printf("Timezone: %s\n", stIpInfo.timezone);
			printf("Timezone UTC DST offset in seconds: %u\n", stIpInfo.offset);
			printf("National currency: %s\n", stIpInfo.currency);
			printf("ISP name: %s\n", stIpInfo.isp);
			printf("Organization name: %s\n", stIpInfo.org);
			printf("AS number and organization: %s\n", stIpInfo.as);
			printf("AS name (RIR): %s\n", stIpInfo.asName);
			printf("Reverse DNS of the IP: %s\n", stIpInfo.reverse);
			printf("Mobile (cellular) connection: %u\n", stIpInfo.mobile);
			printf("Proxy, VPN or Tor exit address: %u\n", stIpInfo.proxy);
			printf("Hosting, colocated or data center: %u\n", stIpInfo.hosting);
			printf("IP used for the query: %s\n", stIpInfo.query);
        }

        else fprintf(stderr, "Couldn't parse a returned JSON object.\n");
    }

    else fprintf(stderr, "Couldn't connect success to the server.\n");
    return 0;
}