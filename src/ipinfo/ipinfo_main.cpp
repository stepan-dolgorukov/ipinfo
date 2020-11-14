#include <string>


#include "../../include/ipinfo/ipinfo_types.hpp"
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
        ipinfo::set_error(error, 0u, \
                          {"No error"},\
                          {__func__});

        for (const auto &host : ipinfo::avail_hosts)
        {
            ipinfo::get_full_url(host, ip, lang, full_urls[host], error);
            ipinfo::get_data(full_urls[host], answers[host], error);
            ipinfo::parse_data(host, answers[host], info, error);
        }

        return;
    }


    void \
        print_info(const ipinfo::info_t &info)
    {
        if (!(ipinfo::is_status_success(info)))
        {
            std::cout << ("All hosts have returned a negative ");
            std::cout << ("request status codes.") << std::endl;
            return;
        }

        ipinfo::print_node(info.ip);
        ipinfo::print_node(info.ip_type);

        ipinfo::print_node(info.continent);
        ipinfo::print_node(info.continent_code);

        ipinfo::print_node(info.country);
        ipinfo::print_node(info.country_code);
        ipinfo::print_node(info.country_capital);
        ipinfo::print_node(info.country_phone);
        ipinfo::print_node(info.country_neighbors);

        ipinfo::print_node(info.region);
        ipinfo::print_node(info.region_code);

        ipinfo::print_node(info.city);
        ipinfo::print_node(info.city_district);
        ipinfo::print_node(info.zip_code);

        ipinfo::print_node(info.latitude);
        ipinfo::print_node(info.longitude);

        ipinfo::print_node(info.city_timezone);
        ipinfo::print_node(info.timezone);
        ipinfo::print_node(info.gmt_offset);
        ipinfo::print_node(info.dst_offset);
        ipinfo::print_node(info.timezone_gmt);

        ipinfo::print_node(info.isp);
        ipinfo::print_node(info.as);
        ipinfo::print_node(info.organization);

        ipinfo::print_node(info.reverse_dns);
        ipinfo::print_node(info.is_hosting);
        ipinfo::print_node(info.is_proxy);
        ipinfo::print_node(info.is_mobile);

        ipinfo::print_node(info.currency);
        ipinfo::print_node(info.currency_code);
        ipinfo::print_node(info.currency_symbol);
        ipinfo::print_node(info.currency_rates);
        ipinfo::print_node(info.currency_plural);

        return;
    }
}
