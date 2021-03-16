#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cctype>
#include <cmath>     // std::pow, std::round
#include <cstdint>   // std::uint8_t
#include <locale>    // std::tolower
#include <algorithm> // std::find

template<template<typename ...> class T, typename sub_T> void
ipinfo::srv::utiler::__clear_node(T<sub_T> &node) const
{
    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        auto &content{ node.cont.at(host) };

        content.val = {};
        content.is_parsed = false;
    }

    return;
}

void
ipinfo::srv::utiler::clear_info(ipinfo::srv::types::info &info) const
{
    __clear_node(info.ip);
    __clear_node(info.ip_type);
    __clear_node(info.reverse_dns);
    __clear_node(info.continent);
    __clear_node(info.continent_code);
    __clear_node(info.country);
    __clear_node(info.country_capital);
    __clear_node(info.country_ph_code);
    __clear_node(info.country_neighbors);
    __clear_node(info.region);
    __clear_node(info.region_code);
    __clear_node(info.city);
    __clear_node(info.city_district);
    __clear_node(info.city_timezone);
    __clear_node(info.zip_code);
    __clear_node(info.latitude);
    __clear_node(info.longitude);
    __clear_node(info.gmt_offset);
    __clear_node(info.dst_offset);
    __clear_node(info.timezone_gmt);
    __clear_node(info.isp);
    __clear_node(info.as);
    __clear_node(info.org);
    __clear_node(info.is_hosting);
    __clear_node(info.is_proxy);
    __clear_node(info.is_mobile);
    __clear_node(info.currency);
    __clear_node(info.currency_code);
    __clear_node(info.currency_symbol);
    __clear_node(info.currency_rates);
    __clear_node(info.currency_plural);

    return;
}

double
ipinfo::srv::utiler::round_val(
    const double value,
    const std::uint8_t places) const
{
    const auto n{ std::pow(10u, places) };
    return std::round(value * n) / n;
}

bool
ipinfo::srv::utiler::is_host_supported(const std::string &host) const
{
    const auto &avl_hosts{ constants::AVAILABLE_HOSTS };
    const auto res{ std::find(avl_hosts.begin(), avl_hosts.end(), host) };

    return (avl_hosts.end() != res);
}

bool
ipinfo::srv::utiler::is_host_supported(const std::uint8_t host_id) const
{
    return (host_id < constants::AVAILABLE_HOSTS.size());
}

bool
ipinfo::srv::utiler::is_lang_supported(const std::string &lang) const
{
    const auto &avl_langs{ constants::AVAILABLE_LANGS };
    const auto res{ std::find(avl_langs.begin(), avl_langs.end(), lang) };

    return (avl_langs.end() != res);
}

bool
ipinfo::srv::utiler::is_lang_supported(const std::uint8_t lang_id) const
{
    return (lang_id < constants::AVAILABLE_LANGS.size());
}

bool
ipinfo::srv::utiler::is_lang_supported(
    const std::string &lang,
    const std::string &host) const
{
    if (not is_host_supported(host))
    {
        return false;
    }

    const auto &host_avl_langs{ constants::HOSTS_AVAILABLE_LANGS.at(host) };
    return (host_avl_langs.end() != host_avl_langs.find(lang));
}


// !!!
std::string
ipinfo::srv::utiler::to_lower_case(const std::string &s) const
{
    std::string lc_s{ s };
    std::transform(lc_s.begin(), lc_s.end(), lc_s.begin(), ::tolower);

    return lc_s;
}
