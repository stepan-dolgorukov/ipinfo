#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <string>
#include <cstdint>

#include <cjson/cJSON.h>

::cJSON *
ipinfo::srv::parser::__prepare(const std::string &json)
{
    ::cJSON * const data{ ::cJSON_Parse(json.c_str()) };

    if (not data)
    {
        std::string error_location{ "unknown" };
        const char * const json_error{ ::cJSON_GetErrorPtr() };

        // If we couldn't get an information about parsing error.

        if (not json_error or std::string{ json_error }.empty())
        {
            // if an execution is in this block, 'data' is
            // nullptr, thus we can return nullptr directly

            return nullptr;
        }

        error_location = json_error;
    }

    return data;
}

template<template<typename ...> class T> void
ipinfo::srv::parser::__fill_node(
    T<std::string> &node,
    const ::cJSON &item,
    const std::string &host)
{
    if (::cJSON_IsString(&item))
    {
        auto &content{ node.cont.at(host) };
        const char * const val{ item.valuestring };

        if (not val or std::string{ val }.empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = val;
        content.is_parsed = true;
    }
}

template<template<typename ...> class T> void
ipinfo::srv::parser::__fill_node(
    T<std::int32_t> &node,
    const ::cJSON &item,
    const std::string &host)
{
    auto &content{ node.cont.at(host) };

    if (::cJSON_IsString(&item))
    {
        const char * const val{ item.valuestring };

        if (not val or std::string{val}.empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = std::stoi(val);
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&item))
    {
        const auto &val{ item.valueint };

        content.val = val;
        content.is_parsed = true;
    }
}

template<template<typename ...> class T> void
ipinfo::srv::parser::__fill_node(
    T<double> &node,
    const ::cJSON &item,
    const std::string &host)
{
    auto &content{ node.cont.at(host) };

    if (::cJSON_IsString(&item))
    {
        const char * const val{ item.valuestring };

        if (not val ||
            std::string{val}.empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = std::stod(val);
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&item))
    {
        content.val = item.valuedouble;
        content.is_parsed = true;
    }
}

template<template<typename ...> class T> void
ipinfo::srv::parser::__fill_node(
    T<bool> &node,
    const ::cJSON &item,
    const std::string &host)
{
    auto &content{ node.cont.at(host) };

    if (::cJSON_IsString(&item))
    {
        const char * const val{ item.valuestring };

        if (not val or std::string{ val }.empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = ("true" == std::string{ val });
        content.is_parsed = true;
    }

    if (::cJSON_IsBool(&item))
    {
        content.val = item.valueint;
        content.is_parsed = true;
    }
}

template<template<typename ...> class T, typename sub_T> void
ipinfo::srv::parser::__catch_node(
    const ::cJSON &data,
    T<sub_T> &node,
    const std::string &host)
{
    const auto &node_name{ node.cont.at(host).json_name.c_str() };
    const ::cJSON * const item {
        ::cJSON_GetObjectItemCaseSensitive(&data, node_name)
    };

    __fill_node(node, *item, host);
}

void
ipinfo::srv::parser::parse(
    const std::string &json,
    ipinfo::srv::types::info &info,
    const std::string &host)
{
    ::cJSON * const data{ __prepare(json) };

    if (not data)
    {
        return;
    }

    // think about a shorting of the call list below
    __catch_node(*data, info.ip, host);
    __catch_node(*data, info.ip_type, host);
    __catch_node(*data, info.continent, host);
    __catch_node(*data, info.continent_code, host);
    __catch_node(*data, info.country, host);
    __catch_node(*data, info.country_code, host);
    __catch_node(*data, info.country_capital, host);
    __catch_node(*data, info.country_ph_code, host);
    __catch_node(*data, info.country_neighbors, host);
    __catch_node(*data, info.region, host);
    __catch_node(*data, info.region_code, host);
    __catch_node(*data, info.city, host);
    __catch_node(*data, info.city_district, host);
    __catch_node(*data, info.zip_code, host);
    __catch_node(*data, info.latitude, host);
    __catch_node(*data, info.longitude, host);
    __catch_node(*data, info.city_timezone, host);
    __catch_node(*data, info.timezone, host);
    __catch_node(*data, info.gmt_offset, host);
    __catch_node(*data, info.dst_offset, host);
    __catch_node(*data, info.timezone_gmt, host);
    __catch_node(*data, info.isp, host);
    __catch_node(*data, info.as, host);
    __catch_node(*data, info.org, host);
    __catch_node(*data, info.reverse_dns, host);
    __catch_node(*data, info.is_hosting, host);
    __catch_node(*data, info.is_proxy, host);
    __catch_node(*data, info.is_mobile, host);
    __catch_node(*data, info.currency, host);
    __catch_node(*data, info.currency_code, host);
    __catch_node(*data, info.currency_symbol, host);
    __catch_node(*data, info.currency_rates, host);
    __catch_node(*data, info.currency_plural, host);

    ::cJSON_Delete(data);
}

ipinfo::usr::types::error
ipinfo::srv::parser::get_last_error() const
{
    return {}; // !!!
}
