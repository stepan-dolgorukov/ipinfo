#include <iostream>
#include "../include/ipinfo/ipinfo.hpp"


int main(void)
{
    ipinfo::informer informer{};
    informer.set_ip("8.8.8.8");
    informer.set_lang("English");
    informer.run();

    if (!(informer.get_status()))
    {
        std::cerr << "Request status isn't success" << std::endl;
        return 1;
    }

    std::cout << informer.get_ip() << std::endl;
    std::cout << informer.get_ip_type() << std::endl;
    std::cout << informer.get_continent() << std::endl;
    std::cout << informer.get_continent_code() << std::endl;
    std::cout << informer.get_country() << std::endl;
    std::cout << informer.get_country_code() << std::endl;
    std::cout << informer.get_country_capital() << std::endl;
    std::cout << informer.get_country_phone_code() << std::endl;
    std::cout << informer.get_country_neighbors() << std::endl;
    std::cout << informer.get_region_code() << std::endl;
    std::cout << informer.get_city() << std::endl;
    std::cout << informer.get_city_district() << std::endl;
    std::cout << informer.get_zip_code() << std::endl;
    std::cout << informer.get_latitude() << std::endl;
    std::cout << informer.get_longitude() << std::endl;
    std::cout << informer.get_timezone() << std::endl;
    std::cout << informer.get_city_timezone() << std::endl;
    std::cout << informer.get_gmt_offset() << std::endl;
    std::cout << informer.get_dst_offset() << std::endl;
    std::cout << informer.get_timezone_gmt() << std::endl;
    std::cout << informer.get_isp() << std::endl;
    std::cout << informer.get_as() << std::endl;
    std::cout << informer.get_org() << std::endl;
    std::cout << informer.get_reverse_dns() << std::endl;
    std::cout << informer.get_hosting_status() << std::endl;
    std::cout << informer.get_proxy_status() << std::endl;
    std::cout << informer.get_mobile_status() << std::endl;
    std::cout << informer.get_currency() << std::endl;
    std::cout << informer.get_currency_code() << std::endl;
    std::cout << informer.get_currency_symbol() << std::endl;
    std::cout << informer.get_currency_code() << std::endl;
    std::cout << informer.get_currency_rates() << std::endl;
    std::cout << informer.get_currency_plural() << std::endl;

    return 0;
}
