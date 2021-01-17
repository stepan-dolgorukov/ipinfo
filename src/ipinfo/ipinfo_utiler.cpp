#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cctype>
#include <cmath>
#include <cstdint>
#include <locale>
#include <algorithm>

template<template<typename ...> class T, typename sub_T> void
ipinfo::service::utiler::__clear_node(T<sub_T> &node) const
{
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        auto &content{node.cont.at(host)};

        content.val = {};
        content.is_parsed = false;
    }

    return;
}

void
ipinfo::service::utiler::clear_info(ipinfo::service::types::info &info)
{
    this->__clear_node(info.ip);
    this->__clear_node(info.ip_type);
    this->__clear_node(info.reverse_dns);
    this->__clear_node(info.continent);
    this->__clear_node(info.continent_code);
    this->__clear_node(info.country);
    this->__clear_node(info.continent_code);
    this->__clear_node(info.country_capital);
    this->__clear_node(info.country_ph_code);
    this->__clear_node(info.country_neighbors);
    this->__clear_node(info.region);
    this->__clear_node(info.region_code);
    this->__clear_node(info.city);
    this->__clear_node(info.city_district);
    this->__clear_node(info.city_timezone);
    this->__clear_node(info.zip_code);
    this->__clear_node(info.latitude);
    this->__clear_node(info.longitude);
    this->__clear_node(info.gmt_offset);
    this->__clear_node(info.dst_offset);
    this->__clear_node(info.timezone_gmt);
    this->__clear_node(info.isp);
    this->__clear_node(info.as);
    this->__clear_node(info.org);
    this->__clear_node(info.is_hosting);
    this->__clear_node(info.is_proxy);
    this->__clear_node(info.is_mobile);
    this->__clear_node(info.currency);
    this->__clear_node(info.currency_code);
    this->__clear_node(info.currency_symbol);
    this->__clear_node(info.currency_rates);
    this->__clear_node(info.currency_plural);

    return;
}

double
ipinfo::service::utiler::round_val(
        const double v,
        const std::uint8_t places) const
{
    const auto n{std::pow(10u, places)};
    return {std::round(v * n) / (n)};
}

bool
ipinfo::service::utiler::is_host_supported(const std::string &host)
{
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    return (avl_hosts.end() != std::find(avl_hosts.begin(),
                                         avl_hosts.end(),
                                         host));
}

bool
ipinfo::service::utiler::is_host_supported(const std::uint8_t host_id)
{
    return (host_id < ipinfo::constants::AVAILABLE_HOSTS.size());
}

bool
ipinfo::service::utiler::is_lang_supported(
        const std::string &lang,
        const std::string &host)
{
    if (this->is_host_supported(host))
    {
        const auto &host_avl_langs{ipinfo::constants::HOSTS_AVAILABLE_LANGS.at(host)};

        // !!!
        for (auto &&[__lang, _] : host_avl_langs)
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
ipinfo::service::utiler::to_lower_case(const std::string &s)
{
    std::string lc_s{};

    for (const auto &c : s)
    {
        lc_s += std::tolower(c, {});
    }

    return lc_s;
}

bool
ipinfo::service::utiler::is_host_excluded(
        const std::string &host,
        const std::vector<std::string> &excl_hosts)
{
    const auto &find_res{std::find(excl_hosts.begin(),
                                   excl_hosts.end(),
                                   host)};

    return (find_res != excl_hosts.end());
}
