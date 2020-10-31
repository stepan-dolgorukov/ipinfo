
#include "../../include/ipinfo/ipinfo.hpp"
#include "../../include/ipinfo/ipinfo_util.hpp"
#include "../../include/ipinfo/ipinfo_print.hpp"
#include "../../include/ipinfo/ipinfo_parse.hpp"
#include "../../include/ipinfo/ipinfo_request.hpp"


namespace ipinfo
{
    void \
        get_info(ipinfo::info_t &info, \
                 const std::string &ip, \
                 const std::string &lang, \
                 ipinfo::error_t &error)
    {
        std::map<const std::string, \
                 std::string> full_urls{};

        std::map<const std::string, \
                 std::string> answers{};

        ipinfo::clear_info(info);
        ipinfo::set_error(error, \
                          ipinfo::ui8{0u}, \
                          std::string{"No error"}, \
                          std::string{0});

        for (const auto &host : ipinfo::avail_hosts)
        {
            ipinfo::get_full_url(host, ip, lang, full_urls[host], error);
            ipinfo::get_data(full_urls.at(host), answers[host], error);
            ipinfo::parse_data(host, answers.at(host), info, error);
        }

        return;
    }


    void \
        print_info(const ipinfo::info_t &info)
    {
        ipinfo::print_node<std::string>(info.ip);
        ipinfo::print_node<std::string>(info.ip_type);

        ipinfo::print_node<std::string>(info.continent);
        ipinfo::print_node<std::string>(info.continent_code);

        ipinfo::print_node<std::string>(info.country);
        ipinfo::print_node<std::string>(info.country_code);
        ipinfo::print_node<std::string>(info.country_capital);
        ipinfo::print_node<std::string>(info.country_phone);
        ipinfo::print_node<std::string>(info.country_neighbors);

        ipinfo::print_node<std::string>(info.region);
        ipinfo::print_node<std::string>(info.region_code);

        ipinfo::print_node<std::string>(info.city);
        ipinfo::print_node<std::string>(info.city_district);
        ipinfo::print_node<std::string>(info.zip_code);

        ipinfo::print_node<ipinfo::dbl>(info.latitude);
        ipinfo::print_node<ipinfo::dbl>(info.longitude);

        ipinfo::print_node<std::string>(info.city_timezone);
        ipinfo::print_node<std::string>(info.timezone);
        ipinfo::print_node<ipinfo::i32>(info.gmt_offset);
        ipinfo::print_node<ipinfo::i32>(info.dst_offset);
        ipinfo::print_node<std::string>(info.timezone_gmt);

        ipinfo::print_node<std::string>(info.isp);
        ipinfo::print_node<std::string>(info.as);
        ipinfo::print_node<std::string>(info.organization);

        ipinfo::print_node<std::string>(info.reverse_dns);
        ipinfo::print_node<ipinfo::bl>(info.is_hosting);
        ipinfo::print_node<ipinfo::bl>(info.is_proxy);
        ipinfo::print_node<ipinfo::bl>(info.is_mobile);

        ipinfo::print_node<std::string>(info.currency);
        ipinfo::print_node<std::string>(info.currency_code);
        ipinfo::print_node<std::string>(info.currency_symbol);
        ipinfo::print_node<ipinfo::dbl>(info.currency_rates);
        ipinfo::print_node<std::string>(info.currency_plural);

        return;
    }
}