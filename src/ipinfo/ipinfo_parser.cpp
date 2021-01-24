#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <string>
#include <cstdint>
#include <cjson/cJSON.h>

::cJSON*
ipinfo::service::parser::__prepare(const std::string &json)
{
    ::cJSON * const data{::cJSON_Parse(json.c_str())};

    if (nullptr == data)
    {
        std::string error_location{"unknown"};
        const auto * const json_error{::cJSON_GetErrorPtr()};

        if (nullptr != json_error &&
            !(std::string{json_error}.empty()))
        {
            error_location = json_error;
        }
    }

    return data;
}

template<template<typename ...> class T> void
ipinfo::service::parser::__fill_node(
        T<std::string> &node,
        const ::cJSON &item,
        const std::string &host)
{
    if (::cJSON_IsString(&item))
    {
        auto &content{node.cont.at(host)};
        const char * const val{item.valuestring};

        if ((nullptr == val) || (std::string{val}.empty()))
        {
            content.is_parsed = false;
            return;
        }

        content.val = val;
        content.is_parsed = true;
    }

    return;
}

template<template<typename ...> class T> void
ipinfo::service::parser::__fill_node(
        T<std::int32_t> &node,
        const ::cJSON &item,
        const std::string &host)
{
    auto &content{node.cont.at(host)};

    if (::cJSON_IsString(&item))
    {
        const auto *val{item.valuestring};

        if ((nullptr == val) || (std::string{val}.empty()))
        {
            content.is_parsed = false;
            return;
        }

        content.val = std::stoi(val);
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&item))
    {
        const auto &val{item.valueint};

        content.val = val;
        content.is_parsed = true;
    }

    return;
}

template<template<typename ...> class T> void
ipinfo::service::parser::__fill_node(
        T<double> &node,
        const ::cJSON &item,
        const std::string &host)
{
    auto &content{node.cont.at(host)};

    if (::cJSON_IsString(&item))
    {
        const auto *val{item.valuestring};

        if ((nullptr == val) || (std::string{val}.empty()))
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

    return;
}

template<template<typename ...> class T> void
ipinfo::service::parser::__fill_node(
        T<bool> &node,
        const ::cJSON &item,
        const std::string &host)
{
    auto &content{node.cont.at(host)};

    if (::cJSON_IsString(&item))
    {
        const auto *val{item.valuestring};

        if ((nullptr == val) || (std::string{val}.empty()))
        {
            content.is_parsed = false;
            return;
        }

        content.val = ("true" == std::string{val});
        content.is_parsed = true;
    }

    if (::cJSON_IsBool(&item))
    {
        content.val = item.valueint;
        content.is_parsed = true;
    }

    return;
}

template<template<typename ...> class T, typename sub_T> void
ipinfo::service::parser::__catch_node(
        const ::cJSON &data,
        T<sub_T> &node,
        const std::string &host)
{
    const auto &node_name{node.cont.at(host).json_name.c_str()};
    const auto * const item{::cJSON_GetObjectItemCaseSensitive(&data, node_name)};

    this->__fill_node(node, *item, host);
    return;
}

void
ipinfo::service::parser::parse(
        const std::string &json,
        ipinfo::service::types::info &info,
        const std::string &host)
{
    ::cJSON * const data{this->__prepare(json)};

    if (nullptr == data)
    {
        return;
    }

    // think about a shorting of the call list below
    this->__catch_node(*data, info.ip, host);
    this->__catch_node(*data, info.ip_type, host);
    this->__catch_node(*data, info.continent, host);
    this->__catch_node(*data, info.continent_code, host);
    this->__catch_node(*data, info.country, host);
    this->__catch_node(*data, info.country_code, host);
    this->__catch_node(*data, info.country_capital, host);
    this->__catch_node(*data, info.country_ph_code, host);
    this->__catch_node(*data, info.country_neighbors, host);
    this->__catch_node(*data, info.region, host);
    this->__catch_node(*data, info.region_code, host);
    this->__catch_node(*data, info.city, host);
    this->__catch_node(*data, info.city_district, host);
    this->__catch_node(*data, info.zip_code, host);
    this->__catch_node(*data, info.latitude, host);
    this->__catch_node(*data, info.longitude, host);
    this->__catch_node(*data, info.city_timezone, host);
    this->__catch_node(*data, info.timezone, host);
    this->__catch_node(*data, info.gmt_offset, host);
    this->__catch_node(*data, info.dst_offset, host);
    this->__catch_node(*data, info.timezone_gmt, host);
    this->__catch_node(*data, info.isp, host);
    this->__catch_node(*data, info.as, host);
    this->__catch_node(*data, info.org, host);
    this->__catch_node(*data, info.reverse_dns, host);
    this->__catch_node(*data, info.is_hosting, host);
    this->__catch_node(*data, info.is_proxy, host);
    this->__catch_node(*data, info.is_mobile, host);
    this->__catch_node(*data, info.currency, host);
    this->__catch_node(*data, info.currency_code, host);
    this->__catch_node(*data, info.currency_symbol, host);
    this->__catch_node(*data, info.currency_rates, host);
    this->__catch_node(*data, info.currency_plural, host);

    ::cJSON_Delete(data);
    return;
}

ipinfo::user::types::error
ipinfo::service::parser::get_last_error() const
{
    return {}; // !!!
}
