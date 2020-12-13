#include <string>
#include <cstdint>
#include <iostream>

#include "../../include/cJSON/cJSON.h"

#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

namespace ipinfo
{
    static void
    fill_node(const ::cJSON &data_item,
              const std::string &host,
              ipinfo::__data_node<std::string> &info_node);

    static void
    fill_node(const ::cJSON &data_item,
              const std::string &host,
              ipinfo::__data_node<std::int32_t> &info_node);

    static void
    fill_node(const ::cJSON &data_item,
              const std::string &host,
              ipinfo::__data_node<std::uint32_t> &info_node);

    static void
    fill_node(const ::cJSON &data_item,
              const std::string &host,
              ipinfo::__data_node<double> &info_node);

    static void
    fill_node(const ::cJSON &data_item,
              const std::string &host,
              ipinfo::__data_node<bool> &info_node);

    static void
    fill_node(const ::cJSON &data_item,
              const std::string &host,
              ipinfo::__data_node<std::string> &info_node);

    template<typename T> static void
    parse_json_node(const ::cJSON &data_item,
                    const std::string &host,
                    ipinfo::__data_node<T> &info_node);
}


void
ipinfo::fill_node(const ::cJSON &data_item,
                  const std::string &host,
                  ipinfo::__data_node<std::uint32_t> &info_node)
{
    auto &content{info_node.content.at(host)};

    if (::cJSON_IsString(&data_item))
    {
        const std::string item_val{data_item.valuestring};

        content.str_val = item_val;
        content.val = static_cast<std::uint32_t>(std::stoi(content.str_val));
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&data_item))
    {
        const auto &item_val{data_item.valueint};

        content.val = static_cast<std::uint32_t>(item_val);
        content.str_val = std::to_string(content.val);
        content.is_parsed = true;
    }

    // log, unacceptable data type
    return;
}


void
ipinfo::fill_node(const ::cJSON &data_item,
                  const std::string &host,
                  ipinfo::__data_node<std::int32_t> &info_node)
{
    auto &content{info_node.content.at(host)};

    if (::cJSON_IsString(&data_item))
    {
        const std::string item_val{data_item.valuestring};

        content.str_val = item_val;
        content.val = static_cast<std::int32_t>(std::stoi(content.str_val));
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&data_item))
    {
        const auto &item_val{data_item.valueint};

        content.val = static_cast<int32_t>(item_val);
        content.str_val = std::to_string(content.val);
        content.is_parsed = true;
    }

    // log, unacceptable data type
    return;
}


void
ipinfo::fill_node(const ::cJSON &data_item,
                  const std::string &host,
                  ipinfo::__data_node<double> &info_node)
{;
    auto &content{info_node.content.at(host)};

    if (::cJSON_IsString(&data_item))
    {
        const std::string item_val{data_item.valuestring};
        const double rounded_val{ipinfo::__utiler::round_double(std::stod(item_val), 2u)};

        content.val = rounded_val;
        content.str_val = std::to_string(content.val);
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&data_item))
    {
        const auto &item_value{data_item.valuedouble};
        const double rounded_value{ipinfo::__utiler::round_double(item_value, 2u)};

        content.val = rounded_value;
        content.str_val = std::to_string(content.val);
        content.is_parsed = true;
    }

    return;
}


void
ipinfo::fill_node(const ::cJSON &item,
                  const std::string &host,
                  ipinfo::__data_node<std::string> &node)
{
    auto &current_node{node.content.at(host)};

    if (::cJSON_IsString(&item))
    {
        const std::string item_value{item.valuestring};

        if (item_value.empty())
        {
            current_node.is_parsed = false;
            return;
        }

        current_node.str_val = item_value;
        current_node.val = current_node.str_val;
        current_node.is_parsed = true;
    }

    return;
}


void
ipinfo::fill_node(const ::cJSON &data_item,
                  const std::string &host,
                  ipinfo::__data_node<bool> &info_node)
{
    auto &content{info_node.content.at(host)};

    if (::cJSON_IsString(&data_item))
    {
        const std::string item_val{data_item.valuestring};

        content.val = ("true" == item_val);
        content.str_val = std::to_string(content.val);
        content.is_parsed = true;
    }

    if (::cJSON_IsBool(&data_item))
    {
        const auto &item_value{data_item.valueint};

        content.val = item_value;
        content.str_val = (content.val ? "true" : "false");
        content.is_parsed = true;
    }

    return;
}


template<typename T> void
ipinfo::parse_json_node(const ::cJSON &data,
                        const std::string &host,
                        ipinfo::__data_node<T> &info_node)
{
    const auto node_name{info_node.content.at(host).json_name.c_str()};
    const auto data_item{::cJSON_GetObjectItemCaseSensitive(&data, node_name)};

    if (!data_item)
    {
        // log!
        return;
    }

    ipinfo::fill_node(*data_item, host, info_node);
    return;
}


void
ipinfo::__parser::parse_data(const std::string &host,
                             const std::string &json,
                             ipinfo::__info_t &info)
{
    const auto data{::cJSON_Parse(json.c_str())};

    if (!data)
    {
        // log!
        return;
    }

    ipinfo::parse_json_node(*data, host, info.ip);
    ipinfo::parse_json_node(*data, host, info.ip_type);
    ipinfo::parse_json_node(*data, host, info.reverse_dns);

    ipinfo::parse_json_node(*data, host, info.continent);
    ipinfo::parse_json_node(*data, host, info.continent_code);

    ipinfo::parse_json_node(*data, host, info.country);
    ipinfo::parse_json_node(*data, host, info.country_code);
    ipinfo::parse_json_node(*data, host, info.country_capital);
    ipinfo::parse_json_node(*data, host, info.country_ph_code);
    ipinfo::parse_json_node(*data, host, info.country_neighbors);

    ipinfo::parse_json_node(*data, host, info.region);
    ipinfo::parse_json_node(*data, host, info.region_code);

    ipinfo::parse_json_node(*data, host, info.city);
    ipinfo::parse_json_node(*data, host, info.city_district);
    ipinfo::parse_json_node(*data, host, info.zip_code);

    ipinfo::parse_json_node(*data, host, info.latitude);
    ipinfo::parse_json_node(*data, host, info.longitude);

    ipinfo::parse_json_node(*data, host, info.city_timezone);
    ipinfo::parse_json_node(*data, host, info.timezone);

    ipinfo::parse_json_node(*data, host, info.gmt_offset);
    ipinfo::parse_json_node(*data, host, info.dst_offset);
    ipinfo::parse_json_node(*data, host, info.timezone_gmt);

    ipinfo::parse_json_node(*data, host, info.isp);
    ipinfo::parse_json_node(*data, host, info.as);
    ipinfo::parse_json_node(*data, host, info.org);

    ipinfo::parse_json_node(*data, host, info.is_hosting);
    ipinfo::parse_json_node(*data, host, info.is_proxy);
    ipinfo::parse_json_node(*data, host, info.is_mobile);

    ipinfo::parse_json_node(*data, host, info.currency);
    ipinfo::parse_json_node(*data, host, info.currency_code);
    ipinfo::parse_json_node(*data, host, info.currency_symbol);
    ipinfo::parse_json_node(*data, host, info.currency_rates);
    ipinfo::parse_json_node(*data, host, info.currency_plural);

    return;
}
