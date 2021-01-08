#include <cctype>
#include <cmath>
#include <cstdint>
#include <locale>
#include <algorithm>

#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

namespace ipinfo
{
    template<typename T> static void
    clear_node(__data_node<T> &node);
}

void
ipinfo::__utiler::set_error(ipinfo::error &error,
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
ipinfo::clear_node(__data_node<T> &node)
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        auto &content{node.content.at(host)};

        content.val = {};
        content.is_parsed = false;
    }

    return;
}

template<> void
ipinfo::clear_node(__data_node<std::string> &node)
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        auto &content{node.content.at(host)};

        content.val.clear();
        content.is_parsed = false;
    }

    return;
}

void
ipinfo::__utiler::clear_info(ipinfo::__info &info)
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
                               const std::uint8_t places) const
{
    const auto n{std::pow(10u, places)};
    const auto rounded_val{(std::round(val * n)) / (n)};

    return rounded_val;
}

bool
ipinfo::__utiler::is_host_supported(const std::string &host)
{
    if (!(host.empty()))
    {
        for (const auto &curr_host: ipinfo::avail_hosts)
        {
            if (curr_host == host)
            {
                return true;
            }
        }
    }

    return false;
}

bool
ipinfo::__utiler::is_host_supported(const std::uint8_t host_id)
{
    return (host_id < avail_hosts.size());
}

bool
ipinfo::__utiler::is_lang_correct(const std::string &lang,
                                  const std::string &host)
{
    if (is_host_supported(host))
    {
        for (auto &&[_,__lang] : ipinfo::hosts_avail_langs_codes.at(host))
        {
            if (__lang == lang)
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
    std::string lc_s{};
    std::locale loc{};

    for (const auto &c : s)
    {
        lc_s += std::tolower(c, loc);
    }

    return lc_s;
}

bool
ipinfo::__utiler::is_host_excluded(
                    const std::string &host,
                    const std::vector<std::string> &excl_hosts)
{
    const auto &find_res{std::find(excl_hosts.begin(),
                                   excl_hosts.end(),
                                   host)};

    return (find_res != excl_hosts.end());
}
