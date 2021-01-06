#include <cstdint>
#include <cstdlib>
#include <ipinfo/ipinfo.hpp>

namespace ipinfo_test
{
    static void
    show_info(const std::string &ip,
               const std::string &lang,
               const std::uint8_t conn_num);

    static void
    show_info_ex(const std::string &ip,
                  const std::string &lang,
                  const std::uint8_t conn_num);
}

int
main(const int argc,
     const char * const argv[])
{
    if (4u > static_cast<unsigned int>(argc))
    {
        std::printf("%s\n", "./ipinfo_test <ip> <lang> <conn_num>");
        return 1;
    }

    ipinfo_test::show_info(
        argv[1u],
        argv[2u],
        static_cast<std::uint8_t>(std::atoi(argv[3u]))
    );

    ipinfo_test::show_info_ex(
        argv[1u],
        argv[2u],
        static_cast<std::uint8_t>(std::atoi(argv[3u]))
    );

    return 0;
}

void
ipinfo_test::show_info(const std::string &ip,
                        const std::string &lang,
                        const std::uint8_t conn_num)
{
    ipinfo::informer informer(ip, lang, conn_num);
    ipinfo::error    error{};

    informer.run();

    std::printf("Errors amount: %lu\n", informer.get_errors_num());

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
ipinfo_test::show_info_ex(const std::string &ip,
                           const std::string &lang,
                           const std::uint8_t conn_num)
{
    ipinfo::informer    informer(ip, lang, conn_num);
    ipinfo::error       error{};

    ipinfo::user_node<std::string>  curr_str_cont{};
    ipinfo::user_node<double>       curr_dbl_cont{};
    ipinfo::user_node<std::int32_t> curr_i32_cont{};
    ipinfo::user_node<bool>         curr_bool_cont{};

    informer.run();

    std::printf("Errors amount: %lu\n", informer.get_errors_num());

    curr_str_cont = informer.get_ip_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_ip_type_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_continent_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont= informer.get_continent_code_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_country_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_country_code_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_country_capital_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_country_ph_code_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_country_neighbors_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_region_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_region_code_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_city_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_city_district_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_zip_code_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_dbl_cont = informer.get_latitude_ex();
    std::printf("%s: %.2f; parsed: %u; host: %s\n", curr_dbl_cont.desc.c_str(),
                                                    curr_dbl_cont.val,
                                                    curr_dbl_cont.is_parsed,
                                                    curr_dbl_cont.host.c_str());

    curr_dbl_cont = informer.get_longitude_ex();
    std::printf("%s: %.2f; parsed: %u; host: %s\n", curr_dbl_cont.desc.c_str(),
                                                    curr_dbl_cont.val,
                                                    curr_dbl_cont.is_parsed,
                                                    curr_dbl_cont.host.c_str());

    curr_str_cont = informer.get_timezone_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_city_timezone_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_timezone_gmt_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_i32_cont = informer.get_gmt_offset_ex();
    std::printf("%s: %i; parsed: %u; host: %s\n", curr_i32_cont.desc.c_str(),
                                                  curr_i32_cont.val,
                                                  curr_i32_cont.is_parsed,
                                                  curr_i32_cont.host.c_str());

    curr_i32_cont = informer.get_dst_offset_ex();
    std::printf("%s: %i; parsed: %u; host: %s\n", curr_i32_cont.desc.c_str(),
                                                  curr_i32_cont.val,
                                                  curr_i32_cont.is_parsed,
                                                  curr_i32_cont.host.c_str());

    curr_str_cont = informer.get_isp_ex();
    std::printf("ISP: %s; parsed: %u; host: %s\n", curr_str_cont.val.c_str(),
                                                   curr_str_cont.is_parsed,
                                                   curr_str_cont.host.c_str());

    curr_str_cont = informer.get_as_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_org_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_reverse_dns_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_bool_cont = informer.get_proxy_status_ex();
    std::printf("%s: %u; parsed: %u; host: %s\n", curr_bool_cont.desc.c_str(),
                                                  curr_bool_cont.val,
                                                  curr_bool_cont.is_parsed,
                                                  curr_bool_cont.host.c_str());

    curr_bool_cont = informer.get_mobile_status_ex();
    std::printf("%s: %u; parsed: %u; host: %s\n", curr_bool_cont.desc.c_str(),
                                                  curr_bool_cont.val,
                                                  curr_bool_cont.is_parsed,
                                                  curr_bool_cont.host.c_str());

    curr_str_cont = informer.get_currency_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_currency_code_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_str_cont = informer.get_currency_symbol_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    curr_dbl_cont = informer.get_currency_rates_ex();
    std::printf("%s: %0.2lf; parsed: %u; host: %s\n", curr_dbl_cont.desc.c_str(),
                                                      curr_dbl_cont.val,
                                                      curr_dbl_cont.is_parsed,
                                                      curr_dbl_cont.host.c_str());

    curr_str_cont = informer.get_currency_plural_ex();
    std::printf("%s: %s; parsed: %u; host: %s\n", curr_str_cont.desc.c_str(),
                                                  curr_str_cont.val.c_str(),
                                                  curr_str_cont.is_parsed,
                                                  curr_str_cont.host.c_str());

    return;
}
