#include <string>
#include <cstddef>

#include "../../include/cJSON/cJSON.h"

#include "../../include/ipinfo/ipinfo.hpp"
#include "../../include/ipinfo/ipinfo_util.hpp"
#include "../../include/ipinfo/ipinfo_parse.hpp"


namespace ipinfo
{
    void \
        fill_ui32_node(const cJSON &item,
                       const std::string &host,
                       void * const node,
                       ipinfo::error_t &error)
    {
        if (std::nullptr_t{nullptr} == node)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Invalid node pointer"}, \
                              std::string{__func__});
            return;
        }

        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<ui32> *>(node)
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

            current_node.str_value = (item_value);
            current_node.value = (static_cast<ipinfo::ui32>(std::stoi(current_node.str_value)));
            current_node.is_parsed = bool{true};
        }

        if (cJSON_IsNumber(&item))
        {
            const auto &item_value
            {
                item.valueint
            };

            current_node.value = (static_cast<ipinfo::ui32>(item_value));
            current_node.str_value = (std::to_string(current_node.value));
            current_node.is_parsed = bool{true};
        }

        return;
    }


    void \
        fill_i32_node(const cJSON &item, \
                      const std::string &host, \
                      void * const node, \
                      ipinfo::error_t &error)
    {
        if (std::nullptr_t{nullptr} == node)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Invalid node pointer"}, \
                              std::string{__func__});
            return;
        }

        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<i32> *>(node)
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

            current_node.str_value = (item_value);
            current_node.value = (static_cast<ipinfo::i32>(std::stoi(current_node.str_value)));
            current_node.is_parsed = bool{true};
        }

        if (cJSON_IsNumber(&item))
        {
            const auto &item_value
            {
                item.valueint
            };

            current_node.value = (static_cast<ipinfo::i32>(item_value));
            current_node.str_value = (std::to_string(current_node.value));
            current_node.is_parsed = bool{true};
        }

        return;
    }


    void \
        fill_dbl_node(const cJSON &item, \
                      const std::string &host, \
                      void * const node, \
                      ipinfo::error_t &error)
    {
        if (std::nullptr_t{nullptr} == node)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Invalid node pointer"}, \
                              std::string{__func__});
            return;
        }

        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<dbl> *>(node)
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

            const ipinfo::dbl rounded_value \
            {
                round_dbl(std::stod(item_value), \
                          ipinfo::ui8{2u})
            };

            current_node.value = (rounded_value);
            current_node.str_value = (std::to_string(current_node.value));
            current_node.is_parsed = bool{true};
        }

        if (cJSON_IsNumber(&item))
        {
            const auto &item_value \
            {
                item.valuedouble
            };

            const ipinfo::dbl rounded_value \
            {
                round_dbl(item_value, \
                          ipinfo::ui8{2u})
            };

            current_node.value = (rounded_value);
            current_node.str_value = (std::to_string(current_node.value));
            current_node.is_parsed = bool{true};
        }

        return;
    }


    void \
        fill_bl_node(const cJSON &item, \
                     const std::string &host, \
                     void * const node, \
                     ipinfo::error_t &error)
    {
        if (std::nullptr_t{nullptr} == node)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Invalid node pointer"}, \
                              std::string{__func__});
            return;
        }

        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
            return;
        }

        auto * const node_redirect \
        {
            reinterpret_cast<ipinfo::node<bl> *>(node)
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
                current_node.is_parsed = bool{false};
                return;
            }

            if ((int{0} == host.compare(ipinfo::avail_hosts.at(0u))) && \
                (int{0} == std::string{"status"}.compare(current_node.json_name)))
            {

                if (int{0} == std::string{"success"}.compare(item_value))
                {
                    current_node.value = bool{true};
                    current_node.str_value = (item_value);
                    current_node.is_parsed = bool{true};
                }

                else
                {
                    current_node.value = bool{true};
                    current_node.str_value = (item_value);
                    current_node.is_parsed = bool{true};
                }

                return;
            }

            if (int{0} == std::string{"true"}.compare(item_value))
            {
                current_node.value = bool{true};
            }

            else
            {
                current_node.value = bool{false};
            }

            current_node.str_value = (std::to_string(current_node.value));
            current_node.is_parsed = bool{true};
        }

        if (cJSON_IsBool(&item))
        {
            const auto &item_value \
            {
                item.valueint
            };

            current_node.value = (item_value);
            current_node.str_value = ((current_node.value) ? std::string{"true"} :
                                                             std::string{"false"});
            current_node.is_parsed = bool{true};
        }

        return;
    }


    template<typename T> void \
        parse_json_node(const cJSON &data, \
                        const std::string &host, \
                        ipinfo::node<T> &node, \
                        ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
            return;
        }

        const cJSON * item{std::nullptr_t{nullptr}};
        const char * node_name{std::nullptr_t{nullptr}};

        auto &item_node \
        {
            node.content.at(host)
        };

        if (item_node.json_name.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty JSON node name"}, \
                              std::string{__func__});
            return;
        }

        node_name = (item_node.json_name.c_str());
        item = (cJSON_GetObjectItemCaseSensitive((&data), node_name));

        if (std::nullptr_t{nullptr} == item)
        {
            return;
        }

        const auto &type_hash \
        {
            typeid(item_node.value).hash_code()
        };

        if (typeid(ipinfo::bl).hash_code() == type_hash)
        {
            ipinfo::fill_bl_node((*item), host, (&node), error);
        }

        if (typeid(ipinfo::ui32).hash_code() == type_hash)
        {
            ipinfo::fill_ui32_node((*item), host, (&node), error);
        }

        if (typeid(ipinfo::i32).hash_code() == type_hash)
        {
            ipinfo::fill_i32_node((*item), host, (&node), error);
        }

        if (typeid(ipinfo::dbl).hash_code() == type_hash)
        {
            ipinfo::fill_dbl_node((*item), host, (&node), error);
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
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
            return;
        }

        const cJSON * item{std::nullptr_t{nullptr}};
        const char * node_name{std::nullptr_t{nullptr}};

        auto &current_node \
        {
            node.content.at(host)
        };

        if (current_node.json_name.empty())
        {
            return;
        }

        node_name = (current_node.json_name.c_str());
        item = (cJSON_GetObjectItemCaseSensitive(&data, node_name));

        if (std::nullptr_t{nullptr} == item)
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
                current_node.is_parsed = bool{false};
                return;
            }
 
            current_node.str_value = (item_value);
            current_node.value = (current_node.str_value);
            current_node.is_parsed = bool{true};
        }

        return;
    }


    void \
        parse_data(const std::string &host, \
                   const std::string &json, \
                   ipinfo::info_t &info, \
                   ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (json.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty JSON data string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
             ipinfo::set_error(error, \
                               ipinfo::ui8{1u}, \
                               std::string{"Unavailable host"}, \
                               std::string{__func__});
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

        if (std::nullptr_t{nullptr} == data)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Parsing an received " \
                                          "JSON object failed"}, \
                              std::string{__func__});
            return;
        }

        ipinfo::parse_json_node<bool>(*data, host, info.status, error);

        if (!(status.is_parsed))
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Couldn't parse a " \
                                          "request status"},
                              std::string{__func__});
            return;
        }

        else
        {
            if (!(status.value))
            {
                ipinfo::set_error(error, \
                                  ipinfo::ui8{1u}, \
                                  std::string{"A request status " \
                                              "isn't success"},
                                  std::string{__func__});

                ipinfo::parse_json_node<std::string>(*data, host, info.error_msg, error);
                return;
            }

            else
            {
                ipinfo::parse_json_node<std::string>(*data, host, info.ip, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.ip_type, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.reverse_dns, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.continent, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.continent_code, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.country, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.country_code, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.country_capital, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.country_phone, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.country_neighbors, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.region, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.region_code, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.city, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.city_district, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.zip_code, error);

                ipinfo::parse_json_node<ipinfo::dbl>(*data, host, info.latitude, error);
                ipinfo::parse_json_node<ipinfo::dbl>(*data, host, info.longitude, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.city_timezone, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.timezone, error);

                ipinfo::parse_json_node<ipinfo::i32>(*data, host, info.gmt_offset, error);
                ipinfo::parse_json_node<ipinfo::i32>(*data, host, info.dst_offset, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.timezone_gmt, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.isp, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.as, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.organization, error);

                ipinfo::parse_json_node<ipinfo::bl>(*data, host, info.is_hosting, error);
                ipinfo::parse_json_node<ipinfo::bl>(*data, host, info.is_proxy, error);
                ipinfo::parse_json_node<ipinfo::bl>(*data, host, info.is_mobile, error);

                ipinfo::parse_json_node<std::string>(*data, host, info.currency, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.currency_code, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.currency_symbol, error);
                ipinfo::parse_json_node<ipinfo::dbl>(*data, host, info.currency_rates, error);
                ipinfo::parse_json_node<std::string>(*data, host, info.currency_plural, error);
            }
        }

        cJSON_Delete(const_cast<cJSON*>(data));
        return;
    }
}
