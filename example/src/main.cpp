#include <cstdio>
#include "../include/ipinfo/ipinfo.hpp"


int main(void)
{
    ipinfo::informer informer{};
    informer.set_ip("8.8.8.8");
    informer.set_lang("English");
    informer.run();

    if (!(informer.get_status()))
    {
        std::fprintf(stderr, "%s\n", "Request status isn't success");
        std::fprintf(stderr, "Error message: %s\n", informer.get_error_msg().c_str());
        return 1;
    }

    std::printf("IP: %s\n", informer.get_ip().c_str());
    std::printf("IP type: %s\n", informer.get_ip_type().c_str());
    std::printf("Continent: %s\n", informer.get_continent().c_str());
    std::printf("Continent code: %s\n", informer.get_continent_code().c_str());
    std::printf("County: %s\n", informer.get_country().c_str());
    std::printf("Country code: %s\n", informer.get_country_code().c_str());
    std::printf("Country capital: %s\n", informer.get_country_capital().c_str());
    std::printf("Country phone code: %s\n", informer.get_country_phone_code().c_str());
    std::printf("Country neighbors: %s\n", informer.get_country_neighbors().c_str());
    std::printf("Region: %s\n", informer.get_region().c_str());
    std::printf("Region code: %s\n", informer.get_region_code().c_str());
    std::printf("City: %s\n", informer.get_city().c_str());
    std::printf("City district: %s\n", informer.get_city_district().c_str());
    std::printf("ZIP code: %s\n", informer.get_zip_code().c_str());
    std::printf("Latitude: %.3lf\n", informer.get_latitude());
    std::printf("Longitude: %.3lf\n", informer.get_longitude());
    std::printf("Timezone: %s\n", informer.get_timezone().c_str());
    std::printf("City timezone: %s\n", informer.get_city_timezone().c_str());
    std::printf("Timezone GMT: %s\n", informer.get_timezone_gmt().c_str());
    std::printf("GMT offset: %i\n", informer.get_gmt_offset());
    std::printf("DST offset: %i\n", informer.get_dst_offset());
    std::printf("ISP: %s\n", informer.get_isp().c_str());
    std::printf("AS: %s\n", informer.get_as().c_str());
    std::printf("Organization: %s\n", informer.get_org().c_str());
    std::printf("Reverse DNS lookup: %s\n", informer.get_reverse_dns().c_str());
    std::printf("Hosting, data center: %u\n", informer.get_hosting_status());
    std::printf("Proxy, VPN, Tor usage: %u\n", informer.get_proxy_status());
    std::printf("Mobile connection usage: %u\n", informer.get_mobile_status());
    std::printf("Currency: %s\n", informer.get_currency().c_str());
    std::printf("Currency code: %s\n", informer.get_currency_code().c_str());
    std::printf("Currency symbol: %s\n", informer.get_currency_symbol().c_str());
    std::printf("Currency exchange rate to USD: %.2lf\n", informer.get_currency_rates());
    std::printf("Currency plural: %s\n", informer.get_currency_plural().c_str());

    return 0;
}
