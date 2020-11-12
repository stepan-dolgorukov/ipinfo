#include <string>
#include <cstdint>


#include "../../include/cJSON/cJSON.h"

#include "../../include/ipinfo/ipinfo_util.hpp"
#include "../../include/ipinfo/ipinfo_parse.hpp"
#include "../../include/ipinfo//ipinfo_types.hpp"


namespace ipinfo
{
    void \
        fill_uint32_node(const cJSON &item,
                         const std::string &host,
                         void * const node,
                         ipinfo::error_t &error)
    {
        if (nullptr == node)
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Invalid node pointer"}, \
                              {__func__});
            return;
        }

        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<uint32_t> *>(node)
        };

        auto &current_node \
        {
            node_redirect->content.at(host)
        };

        if (cJSON_IsString(&item))
        {
            const std::string item_value
            {
                item.valuestring
            };

            current_node.str_value = item_value;
            current_node.value = static_cast<std::uint32_t>(std::stoi(current_node.str_value));
            current_node.is_parsed = true;
        }

        if (cJSON_IsNumber(&item))
        {
            const auto &item_value
            {
                item.valueint
            };

            current_node.value = static_cast<std::uint32_t>(item_value);
            current_node.str_value = std::to_string(current_node.value);
            current_node.is_parsed = true;
        }

        return;
    }


    void \
        fill_int32_node(const cJSON &item, \
                        const std::string &host, \
                        void * const node, \
                        ipinfo::error_t &error)
    {
        if (nullptr == node)
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Invalid node pointer"}, \
                              {__func__});
            return;
        }

        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<std::int32_t> *>(node)
        };

        auto &current_node \
        {
            node_redirect->content.at(host)
        };

        if (cJSON_IsString(&item))
        {
            const std::string item_value
            {
                item.valuestring
            };

            current_node.str_value = item_value;
            current_node.value = static_cast<std::uint32_t>(std::stoi(current_node.str_value));
            current_node.is_parsed = true;
        }

        if (cJSON_IsNumber(&item))
        {
            const auto &item_value
            {
                item.valueint
            };

            current_node.value = static_cast<int32_t>(item_value);
            current_node.str_value = std::to_string(current_node.value);
            current_node.is_parsed = true;
        }

        return;
    }


    void \
        fill_double_node(const cJSON &item, \
                         const std::string &host, \
                         void * const node, \
                         ipinfo::error_t &error)
    {
        if (nullptr == node)
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Invalid node pointer"}, \
                              {__func__});
            return;
        }

        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<double> *>(node)
        };

        auto &current_node \
        {
            node_redirect->content.at(host)
        };

        if (cJSON_IsString(&item))
        {
            const std::string item_value \
            {
                item.valuestring
            };

            const double rounded_value \
            {
                ipinfo::round_double(std::stod(item_value), 2u)
            };

            current_node.value = rounded_value;
            current_node.str_value = std::to_string(current_node.value);
            current_node.is_parsed = true;
        }

        if (cJSON_IsNumber(&item))
        {
            const auto &item_value \
            {
                item.valuedouble
            };

            const double rounded_value \
            {
                ipinfo::round_double(item_value, 2u)
            };

            current_node.value = rounded_value;
            current_node.str_value = std::to_string(current_node.value);
            current_node.is_parsed = true;
        }

        return;
    }


    void \
        fill_bool_node(const cJSON &item, \
                       const std::string &host, \
                       void * const node, \
                       ipinfo::error_t &error)
    {
        if (nullptr == node)
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Invalid node pointer"}, \
                              {__func__});
            return;
        }

        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<bool> *>(node)
        };

        auto &current_node \
        {
            node_redirect->content.at(host)
        };

        if (cJSON_IsString(&item))
        {
            const std::string item_value \
            {
                item.valuestring
            };

            if (item_value.empty())
            {
                current_node.is_parsed = false;
                return;
            }

            if (host == ipinfo::avail_hosts.at(0) && \
                "status" == current_node.json_name)
            {
                current_node.value = ("success" == item_value);
                current_node.str_value = item_value;
                current_node.is_parsed = true;
                return;
            }

            current_node.value = ("true" == item_value);
            current_node.str_value = std::to_string(current_node.value);
            current_node.is_parsed = true;
        }

        if (cJSON_IsBool(&item))
        {
            const auto &item_value \
            {
                item.valueint
            };

            current_node.value = (item_value);
            current_node.str_value = (current_node.value ? "true": "false");
            current_node.is_parsed = true;
        }

        return;
    }



    template<typename T> void \
        parse_json_node(const cJSON &data, \
                        const std::string &host, \
                        ipinfo::node<T> &node, \
                        ipinfo::error_t &error)
    {
        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        const cJSON * item{};
        const char * node_name{};

        auto &item_node \
        {
            node.content.at(host)
        };

        if (item_node.json_name.empty())
        {
            ipinfo::set_error(error, \
                              1u, \
                              "Empty JSON node name", \
                              {__func__});
            return;
        }

        node_name = item_node.json_name.c_str();
        item = cJSON_GetObjectItemCaseSensitive((&data), node_name);

        if (nullptr == item)
        {
            return;
        }

        const auto &type_hash \
        {
            typeid(item_node.value).hash_code()
        };

        if (typeid(bool).hash_code() == type_hash)
        {
            ipinfo::fill_bool_node((*item), host, (&node), error);
        }

        if (typeid(std::uint32_t).hash_code() == type_hash)
        {
            ipinfo::fill_uint32_node((*item), host, (&node), error);
        }

        if (typeid(std::int32_t).hash_code() == type_hash)
        {
            ipinfo::fill_int32_node((*item), host, (&node), error);
        }

        if (typeid(double).hash_code() == type_hash)
        {
            ipinfo::fill_double_node((*item), host, (&node), error);
        }

        return;
    }


    template<> void \
        parse_json_node(const cJSON &data, \
                        const std::string &host, \
                        ipinfo::node<std::string> &node, \
                        ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              1u, \
                              "Empty host string", \
                              {__func__});
            return;
        }

        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        const cJSON * item{};
        const char * node_name{};

        auto &current_node \
        {
            node.content.at(host)
        };

        if (current_node.json_name.empty())
        {
            return;
        }

        node_name = current_node.json_name.c_str();
        item = cJSON_GetObjectItemCaseSensitive(&data, node_name);

        if (nullptr == item)
        {
            return;
        }

        if (cJSON_IsString(item))
        {
            const std::string item_value \
            {
                item->valuestring
            };

            if (item_value.empty())
            {
                current_node.is_parsed = false;
                return;
            }
 
            current_node.str_value = item_value;
            current_node.value = current_node.str_value;
            current_node.is_parsed = true;
        }

        return;
    }


    void \
        parse_data(const std::string &host, \
                   const std::string &json, \
                   ipinfo::info_t &info, \
                   ipinfo::error_t &error)
    {
        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        if (json.empty())
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Empty JSON data string"}, \
                              {__func__});
            return;
        }

        const auto &status \
        {
            info.status.content.at(host)
        };

        const cJSON * const data \
        {
            cJSON_Parse(json.c_str())
        };

        if (nullptr == data)
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Parsing the received " \
                               "JSON object failed"}, \
                              {__func__});
            return;
        }

        ipinfo::parse_json_node<bool>(*data, host, info.status, error);

        if (!(status.is_parsed))
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Couldn't parse the " \
                                          "request status"},
                              {__func__});
            return;
        }

        else
        {
            if (!(status.value))
            {
                ipinfo::set_error(error, \
                                  1u, \
                                  {"A request status " \
                                              "isn't success"},
                                  {__func__});

                ipinfo::parse_json_node<std::string>(*data, host, info.error_msg, error);
                return;
            }

            else
            {
                ipinfo::parse_json_node(*data, host, info.ip, error);
                ipinfo::parse_json_node(*data, host, info.ip_type, error);
                ipinfo::parse_json_node(*data, host, info.reverse_dns, error);

                ipinfo::parse_json_node(*data, host, info.continent, error);
                ipinfo::parse_json_node(*data, host, info.continent_code, error);

                ipinfo::parse_json_node(*data, host, info.country, error);
                ipinfo::parse_json_node(*data, host, info.country_code, error);
                ipinfo::parse_json_node(*data, host, info.country_capital, error);
                ipinfo::parse_json_node(*data, host, info.country_phone, error);
                ipinfo::parse_json_node(*data, host, info.country_neighbors, error);

                ipinfo::parse_json_node(*data, host, info.region, error);
                ipinfo::parse_json_node(*data, host, info.region_code, error);

                ipinfo::parse_json_node(*data, host, info.city, error);
                ipinfo::parse_json_node(*data, host, info.city_district, error);
                ipinfo::parse_json_node(*data, host, info.zip_code, error);

                ipinfo::parse_json_node(*data, host, info.latitude, error);
                ipinfo::parse_json_node(*data, host, info.longitude, error);

                ipinfo::parse_json_node(*data, host, info.city_timezone, error);
                ipinfo::parse_json_node(*data, host, info.timezone, error);

                ipinfo::parse_json_node(*data, host, info.gmt_offset, error);
                ipinfo::parse_json_node(*data, host, info.dst_offset, error);
                ipinfo::parse_json_node(*data, host, info.timezone_gmt, error);

                ipinfo::parse_json_node(*data, host, info.isp, error);
                ipinfo::parse_json_node(*data, host, info.as, error);
                ipinfo::parse_json_node(*data, host, info.organization, error);

                ipinfo::parse_json_node(*data, host, info.is_hosting, error);
                ipinfo::parse_json_node(*data, host, info.is_proxy, error);
                ipinfo::parse_json_node(*data, host, info.is_mobile, error);

                ipinfo::parse_json_node(*data, host, info.currency, error);
                ipinfo::parse_json_node(*data, host, info.currency_code, error);
                ipinfo::parse_json_node(*data, host, info.currency_symbol, error);
                ipinfo::parse_json_node(*data, host, info.currency_rates, error);
                ipinfo::parse_json_node(*data, host, info.currency_plural, error);
            }
        }

        cJSON_Delete(const_cast<cJSON*>(data));
        return;
    }
}
