#include <string>
#include <cstdint>

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
    process_node(const ::cJSON &data_item,
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

        content.str_val = item_val;
        content.val = std::stod(content.str_val);
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&data_item))
    {
        const auto &item_val{data_item.valuedouble};

        content.val = item_val;
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
    if (::cJSON_IsString(&item))
    {
        auto &current_node{node.content.at(host)};
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
ipinfo::process_node(const ::cJSON &data,
                     const std::string &host,
                     ipinfo::__data_node<T> &info_node)
{
    const auto node_name{info_node.content.at(host).json_name.c_str()};
    const auto *data_item{::cJSON_GetObjectItemCaseSensitive(&data, node_name)};

    if (nullptr == data_item)
    {
        // log!
        return;
    }

    ipinfo::fill_node(*data_item, host, info_node);
    return;
}

void
ipinfo::__parser::put_json(const std::string &s)
{
    if (s.empty())
    {
        __utiler::set_error(__error,
                            EMPTY_JSON_STRING,
                            "Empty JSON string",
                            __func__);
        return;
    }

    __data = ::cJSON_Parse(s.c_str());

    if (nullptr == __data)
    {
        std::string error_location{"unknown"};
        const auto * const json_error{::cJSON_GetErrorPtr()};

        if (nullptr != json_error)
        {
            error_location = json_error;
        }

        __utiler::set_error(__error,
                            FAILED_JSON_PARSING,
                            "JSON parsing error. " \
                            "Error before: " + error_location,
                            __func__);
    }

    return;
}

void
ipinfo::__parser::deserialize_json(ipinfo::__info_t &i,
                                   const std::string &host) const
{
    if (nullptr == __data)
    {
        return;
    }

    ipinfo::process_node(*__data, host, i.ip);
    ipinfo::process_node(*__data, host, i.ip_type);

    ipinfo::process_node(*__data, host, i.continent);
    ipinfo::process_node(*__data, host, i.continent_code);

    ipinfo::process_node(*__data, host, i.country);
    ipinfo::process_node(*__data, host, i.country_code);
    ipinfo::process_node(*__data, host, i.country_capital);
    ipinfo::process_node(*__data, host, i.country_ph_code);
    ipinfo::process_node(*__data, host, i.country_neighbors);

    ipinfo::process_node(*__data, host, i.region);
    ipinfo::process_node(*__data, host, i.region_code);

    ipinfo::process_node(*__data, host, i.city);
    ipinfo::process_node(*__data, host, i.city_district);
    ipinfo::process_node(*__data, host, i.zip_code);

    ipinfo::process_node(*__data, host, i.latitude);
    ipinfo::process_node(*__data, host, i.longitude);

    ipinfo::process_node(*__data, host, i.city_timezone);
    ipinfo::process_node(*__data, host, i.timezone);

    ipinfo::process_node(*__data, host, i.gmt_offset);
    ipinfo::process_node(*__data, host, i.dst_offset);
    ipinfo::process_node(*__data, host, i.timezone_gmt);

    ipinfo::process_node(*__data, host, i.isp);
    ipinfo::process_node(*__data, host, i.as);
    ipinfo::process_node(*__data, host, i.org);
    ipinfo::process_node(*__data, host, i.reverse_dns);

    ipinfo::process_node(*__data, host, i.is_hosting);
    ipinfo::process_node(*__data, host, i.is_proxy);
    ipinfo::process_node(*__data, host, i.is_mobile);

    ipinfo::process_node(*__data, host, i.currency);
    ipinfo::process_node(*__data, host, i.currency_code);
    ipinfo::process_node(*__data, host, i.currency_symbol);
    ipinfo::process_node(*__data, host, i.currency_rates);
    ipinfo::process_node(*__data, host, i.currency_plural);

    return;
}

ipinfo::error_t
ipinfo::__parser::get_last_error() const
{
    return __error;
}
