#include <cctype>
#include <cmath>
#include <cstdint>
#include <locale>

#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

namespace ipinfo
{
    template<typename T> static void
    clear_node(ipinfo::__data_node<T> &info_node);
}


void
ipinfo::__utiler::set_error(ipinfo::__error_t &error,
                            const std::uint8_t code,
                            const std::string &&desc,
                            const std::string &&func)
{
    error.code = code;
    error.desc = desc;
    error.func = func;
    return;
}


template<typename T> void
ipinfo::clear_node(__data_node<T> &info_node)
{

    for (const auto &host : ipinfo::avail_hosts)
    {
        auto &content{info_node.content.at(host)};
        content.val = {};
        content.str_val = {};
        content.is_parsed = false;
    }

    return;
}


template<> void
ipinfo::clear_node(__data_node<std::string> &info_node)
{

    for (const auto &host : ipinfo::avail_hosts)
    {
        auto &content{info_node.content.at(host)};
        content.val.clear();
        content.str_val.clear();
        content.is_parsed = false;
    }

    return;
}


void
ipinfo::__utiler::clear_info(ipinfo::__info_t &info)
{
    ipinfo::clear_node(info.ip);
    ipinfo::clear_node(info.ip_type);
    ipinfo::clear_node(info.reverse_dns);

    ipinfo::clear_node(info.continent);
    ipinfo::clear_node(info.continent_code);

    ipinfo::clear_node(info.country);
    ipinfo::clear_node(info.continent_code);
    ipinfo::clear_node(info.country_capital);
    ipinfo::clear_node(info.country_ph_code);
    ipinfo::clear_node(info.country_neighbors);

    ipinfo::clear_node(info.region);
    ipinfo::clear_node(info.region_code);

    ipinfo::clear_node(info.city);
    ipinfo::clear_node(info.city_district);
    ipinfo::clear_node(info.city_timezone);

    ipinfo::clear_node(info.zip_code);

    ipinfo::clear_node(info.latitude);
    ipinfo::clear_node(info.longitude);

    ipinfo::clear_node(info.gmt_offset);
    ipinfo::clear_node(info.dst_offset);
    ipinfo::clear_node(info.timezone_gmt);

    ipinfo::clear_node(info.isp);
    ipinfo::clear_node(info.as);
    ipinfo::clear_node(info.org);

    ipinfo::clear_node(info.is_hosting);
    ipinfo::clear_node(info.is_proxy);
    ipinfo::clear_node(info.is_mobile);

    ipinfo::clear_node(info.currency);
    ipinfo::clear_node(info.currency_code);
    ipinfo::clear_node(info.currency_symbol);
    ipinfo::clear_node(info.currency_rates);
    ipinfo::clear_node(info.currency_plural);

    return;
}


double
ipinfo::__utiler::round_double(const double val,
                               const std::uint8_t places)
{
    const auto n{std::pow(10u, places)};
    const auto rounded_val{(std::round(val * n)) / (n)};

    return rounded_val;
}


bool
ipinfo::__utiler::is_host_correct(const std::string &host,
                                  ipinfo::__error_t &error)
{
    if (!(host.empty()))
    {
        for (const auto &avail_host : ipinfo::avail_hosts)
        {
            if (avail_host == host)
            {
                return true;
            }
        }
    }

    return false;
}


bool
ipinfo::__utiler::is_language_correct(const std::string &host,
                                      const std::string &language,
                                      ipinfo::__error_t &error)
{
    if (!(language.empty()) && __utiler::is_host_correct(host, error))
    {
        for (const auto &value_pair : ipinfo::avail_langs.at(host))
        {
            if (value_pair.first == language)
            {
                return true;
            }
        }
    }

    return false;
}


std::string
ipinfo::__utiler::str_to_lower_case(const std::string &s)
{
    std::string lc_s{s};
    std::locale loc{};

    for (auto &c : lc_s)
    {
        c = std::tolower(c, loc);
    }

    return lc_s;
}
