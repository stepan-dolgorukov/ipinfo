#include <cstdint>
#include "../include/ipinfo/ipinfo.hpp"


void
example(std::string &&ip,
        std::string &&lang);


void
example_ex(std::string &&ip,
           std::string &&lang);


int
main(void)
{
    // IPv4
    ::example("8.8.8.8", "English");
    ::example_ex("8.8.8.8", "English");

    // IPv6
    ::example("2001:4860:4860::8888", "Russian");
    ::example_ex("2001:4860:4860::8888", "Russian");

    return 0;
}


void
example(std::string &&ip,
        std::string &&lang)
{
    ipinfo::informer informer{};
    informer.set_ip(ip);
    informer.set_lang(lang);
    informer.run();

    std::printf("IP: %s\n", informer.get_ip().c_str());
    std::printf("IP type: %s\n", informer.get_ip_type().c_str());
    std::printf("Continent: %s\n", informer.get_continent().c_str());
    std::printf("Continent code: %s\n", informer.get_continent_code().c_str());
    std::printf("County: %s\n", informer.get_country().c_str());
    std::printf("Country code: %s\n", informer.get_country_code().c_str());
    std::printf("Country capital: %s\n", informer.get_country_capital().c_str());
    std::printf("Country phone code: %s\n", informer.get_country_ph_code().c_str());
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

    return;
}


void
example_ex(std::string &&ip,
           std::string &&lang)
{
    ipinfo::informer informer{};
    informer.set_ip(ip);
    informer.set_lang(lang);
    informer.run();

    ipinfo::user_node<std::string>  curr_string_cont{};
    ipinfo::user_node<double>       curr_double_cont{};
    ipinfo::user_node<std::int32_t> curr_int32_cont{};
    ipinfo::user_node<bool>         curr_bool_cont{};

    curr_string_cont = informer.get_ip_ex();
    std::printf("IP: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                  curr_string_cont.is_parsed,
                                                  curr_string_cont.host.c_str());

    curr_string_cont = informer.get_ip_type_ex();
    std::printf("IP type: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                       curr_string_cont.is_parsed,
                                                       curr_string_cont.host.c_str());

    curr_string_cont = informer.get_continent_ex();
    std::printf("Continent: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                         curr_string_cont.is_parsed,
                                                         curr_string_cont.host.c_str());

    curr_string_cont= informer.get_continent_code_ex();
    std::printf("Continent code: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                              curr_string_cont.is_parsed,
                                                              curr_string_cont.host.c_str());

    curr_string_cont = informer.get_country_ex();
    std::printf("Country: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                       curr_string_cont.is_parsed,
                                                       curr_string_cont.host.c_str());

    curr_string_cont = informer.get_country_code_ex();
    std::printf("Country code: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                            curr_string_cont.is_parsed,
                                                            curr_string_cont.host.c_str());

    curr_string_cont = informer.get_country_capital_ex();
    std::printf("Country capital: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                               curr_string_cont.is_parsed,
                                                               curr_string_cont.host.c_str());

    curr_string_cont = informer.get_country_ph_code_ex();
    std::printf("Country phone code: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                                  curr_string_cont.is_parsed,
                                                                  curr_string_cont.host.c_str());

    curr_string_cont = informer.get_country_neighbors_ex();
    std::printf("Country neighbors: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                                 curr_string_cont.is_parsed,
                                                                 curr_string_cont.host.c_str());

    curr_string_cont = informer.get_region_ex();
    std::printf("Region: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                      curr_string_cont.is_parsed,
                                                      curr_string_cont.host.c_str());

    curr_string_cont = informer.get_region_code_ex();
    std::printf("Region code: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                           curr_string_cont.is_parsed,
                                                           curr_string_cont.host.c_str());

    curr_string_cont = informer.get_city_ex();
    std::printf("City: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                    curr_string_cont.is_parsed,
                                                    curr_string_cont.host.c_str());

    curr_string_cont = informer.get_city_district_ex();
    std::printf("City district: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                             curr_string_cont.is_parsed,
                                                             curr_string_cont.host.c_str());

    curr_string_cont = informer.get_zip_code_ex();
    std::printf("ZIP code: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                        curr_string_cont.is_parsed,
                                                        curr_string_cont.host.c_str());

    curr_double_cont = informer.get_latitude_ex();
    std::printf("Latitude: %.2f; parsed: %u; host: %s\n", curr_double_cont.val,
                                                          curr_double_cont.is_parsed,
                                                          curr_double_cont.host.c_str());

    curr_double_cont = informer.get_longitude_ex();
    std::printf("Longitude: %.2f; parsed: %u; host: %s\n", curr_double_cont.val,
                                                           curr_double_cont.is_parsed,
                                                           curr_double_cont.host.c_str());

    curr_string_cont = informer.get_timezone_ex();
    std::printf("Timezone: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                        curr_string_cont.is_parsed,
                                                        curr_string_cont.host.c_str());

    curr_string_cont = informer.get_city_timezone_ex();
    std::printf("City timezone: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                             curr_string_cont.is_parsed,
                                                             curr_string_cont.host.c_str());

    curr_string_cont = informer.get_timezone_gmt_ex();
    std::printf("Timezone GMT: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                            curr_string_cont.is_parsed,
                                                            curr_string_cont.host.c_str());

    curr_int32_cont = informer.get_gmt_offset_ex();
    std::printf("GMT offset: %i; parsed: %u; host: %s\n", curr_int32_cont.val,
                                                          curr_int32_cont.is_parsed,
                                                          curr_int32_cont.host.c_str());

    curr_int32_cont = informer.get_dst_offset_ex();
    std::printf("DST offset: %i; parsed: %u; host: %s\n", curr_int32_cont.val,
                                                          curr_int32_cont.is_parsed,
                                                          curr_int32_cont.host.c_str());

    curr_string_cont = informer.get_isp_ex();
    std::printf("ISP: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                   curr_string_cont.is_parsed,
                                                   curr_string_cont.host.c_str());

    curr_string_cont = informer.get_as_ex();
    std::printf("AS: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                  curr_string_cont.is_parsed,
                                                  curr_string_cont.host.c_str());

    curr_string_cont = informer.get_org_ex();
    std::printf("Organization: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                            curr_string_cont.is_parsed,
                                                            curr_string_cont.host.c_str());

    curr_string_cont = informer.get_reverse_dns_ex();
    std::printf("Reverse DNS lookup: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                                  curr_string_cont.is_parsed,
                                                                  curr_string_cont.host.c_str());

    curr_string_cont = informer.get_reverse_dns_ex();
    std::printf("Reverse DNS lookup: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                                  curr_string_cont.is_parsed,
                                                                  curr_string_cont.host.c_str());

    curr_bool_cont = informer.get_hosting_status_ex();
    std::printf("Hosting, data center: %u; parsed: %u; host: %s\n", curr_bool_cont.val,
                                                                    curr_bool_cont.is_parsed,
                                                                    curr_bool_cont.host.c_str());

    curr_bool_cont = informer.get_proxy_status_ex();
    std::printf("Proxy, VPN, Tor usage: %u; parsed: %u; host: %s\n", curr_bool_cont.val,
                                                                     curr_bool_cont.is_parsed,
                                                                     curr_bool_cont.host.c_str());

    curr_bool_cont = informer.get_mobile_status_ex();
    std::printf("Mobile connection usage: %u; parsed: %u; host: %s\n", curr_bool_cont.val,
                                                                       curr_bool_cont.is_parsed,
                                                                       curr_bool_cont.host.c_str());

    curr_string_cont = informer.get_currency_ex();
    std::printf("Currency: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                                  curr_string_cont.is_parsed,
                                                                  curr_string_cont.host.c_str());

    curr_string_cont = informer.get_currency_code_ex();
    std::printf("Currency code: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                             curr_string_cont.is_parsed,
                                                             curr_string_cont.host.c_str());

    curr_string_cont = informer.get_currency_symbol_ex();
    std::printf("Currency symbol: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                               curr_string_cont.is_parsed,
                                                               curr_string_cont.host.c_str());

    curr_double_cont = informer.get_currency_rates_ex();
    std::printf("Currency exchange rate to USD: %0.2lf; parsed: %u; host: %s\n", curr_double_cont.val,
                                                                                 curr_double_cont.is_parsed,
                                                                                 curr_double_cont.host.c_str());

    curr_string_cont = informer.get_currency_plural_ex();
    std::printf("Currency plural: %s; parsed: %u; host: %s\n", curr_string_cont.val.c_str(),
                                                               curr_string_cont.is_parsed,
                                                               curr_string_cont.host.c_str());

    return;
}
