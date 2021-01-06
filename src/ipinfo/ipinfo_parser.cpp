#include <string>
#include <cstdint>
#include <cjson/cJSON.h>

#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

namespace ipinfo
{
    static void
    fill_node(const ::cJSON &item,
              const std::string &host,
              __data_node<std::int32_t> &node);

    static void
    fill_node(const ::cJSON &item,
              const std::string &host,
              __data_node<double> &node);

    static void
    fill_node(const ::cJSON &item,
              const std::string &host,
              __data_node<std::string> &node);

    static void
    fill_node(const ::cJSON &item,
              const std::string &host,
              ipinfo::__data_node<bool> &node);

    template<typename T> static void
    process_node(const ::cJSON &item,
                 const std::string &host,
                 ipinfo::__data_node<T> &node);
}

void
ipinfo::fill_node(const ::cJSON &item,
                  const std::string &host,
                  ipinfo::__data_node<std::int32_t> &node)
{
    auto &content{node.content.at(host)};

    if (::cJSON_IsString(&item))
    {
        const auto *val{item.valuestring};

        if (nullptr == val ||
            std::string(val).empty())
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

void
ipinfo::fill_node(const ::cJSON &item,
                  const std::string &host,
                  ipinfo::__data_node<double> &node)
{;
    auto &content{node.content.at(host)};

    if (::cJSON_IsString(&item))
    {
        const auto *val{item.valuestring};

        if (nullptr == val ||
            std::string(val).empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = std::stod(std::string(val));
        content.is_parsed = true;
    }

    if (::cJSON_IsNumber(&item))
    {
        content.val = item.valuedouble;
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
        auto &content{node.content.at(host)};
        const auto *val{item.valuestring};

        if (nullptr == val ||
            std::string(val).empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = val;
        content.is_parsed = true;
    }

    return;
}

void
ipinfo::fill_node(const ::cJSON &item,
                  const std::string &host,
                  ipinfo::__data_node<bool> &node)
{
    auto &content{node.content.at(host)};

    if (::cJSON_IsString(&item))
    {
        auto &content{node.content.at(host)};
        const auto *val{item.valuestring};

        if (nullptr == val ||
            std::string(val).empty())
        {
            content.is_parsed = false;
            return;
        }

        content.val = ("true" == std::string(val));
        content.is_parsed = true;
    }

    if (::cJSON_IsBool(&item))
    {
        content.val = item.valueint;
        content.is_parsed = true;
    }

    return;
}

template<typename T> void
ipinfo::process_node(const ::cJSON &data,
                     const std::string &host,
                     ipinfo::__data_node<T> &node)
{
    const auto node_name{
        node.content.at(host).json_name.c_str()};

    const auto *item{
        ::cJSON_GetObjectItemCaseSensitive(&data, node_name)};

    if (nullptr == item)
    {
        // log!
        return;
    }

    ipinfo::fill_node(*item, host, node);
    return;
}

void
ipinfo::__parser::put_json(const std::string &json)
{
    if (json.empty())
    {
        __utiler::set_error(
                __error,
                EMPTY_JSON_STRING,
                "Empty JSON string",
                __func__);
        return;
    }

    __data = ::cJSON_Parse(json.c_str());

    if (nullptr == __data)
    {
        std::string error_location{"unknown"};
        const auto * const json_error{::cJSON_GetErrorPtr()};

        if (nullptr != json_error)
        {
            error_location = json_error;
        }

        __utiler::set_error(
                __error,
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
