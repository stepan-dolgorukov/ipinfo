#include <cstdint>
#include <ipinfo/ipinfo.hpp>

namespace my_app
{
    void
    show_ip_info(const std::string &ip,
                 const std::string &lang);

    void
    show_ip_info_ex(const std::string &ip,
                    const std::string &lang);
}

int
main(void)
{
    my_app::show_ip_info("8.8.8.8", "english");
    my_app::show_ip_info_ex("2001:4860:4860::8888", "russian");

    return 0;
}

void
my_app::show_ip_info(const std::string &ip,
                     const std::string &lang)
{
    ipinfo::interface::informer informer{};
    ipinfo::types::error        error{};

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
my_app::show_ip_info_ex(const std::string &ip,
                        const std::string &lang)
{
    ipinfo::interface::informer informer(ip, lang, 0u);
    ipinfo::types::error        error{};

    informer.run();

    ipinfo::types::node<std::string>  curr_str_cont{};
    ipinfo::types::node<std::int32_t> curr_i32_cont{};
    ipinfo::types::node<double>       curr_dbl_cont{};
    ipinfo::types::node<bool>         curr_bool_cont{};

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
