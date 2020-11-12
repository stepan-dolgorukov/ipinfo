#include <cmath>
#include <cstdint>
#include <iostream>


#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_util.hpp"


namespace ipinfo
{
    void \
        set_error(ipinfo::error_t &error, \
                  const std::uint8_t code, \
                  const std::string &description, \
                  const std::string &function_name)
    {
        error.code = code;
        error.description = description;
        error.function_name = function_name;

        return;
    }


    template<typename T> static void \
        clear_node(node<T> &node)
    {
        for (const auto &host : ipinfo::avail_hosts)
        {
            if ((typeid(std::uint32_t).hash_code()) == (typeid(T).hash_code()))
            {
                node.content.at(host).value = 0u;
            }

            else
            {
                if (typeid(bool).hash_code() == typeid(T).hash_code())
                {
                    node.content.at(host).value = false;
                }

                else
                {
                    node.content.at(host).value = 0;
                }
            }

            node.content.at(host).str_value.clear();
            node.content.at(host).is_parsed = false;
        }

        return;
    }


    template<> void \
        clear_node(node<std::string> &node)
    {
        for (const auto &host : ipinfo::avail_hosts)
        {
            node.content.at(host).value.clear();
            node.content.at(host).str_value.clear();
            node.content.at(host).is_parsed = false;
        }

        return;
    }


    void \
        clear_info(ipinfo::info_t &info)
    {
        ipinfo::clear_node(info.status);
        ipinfo::clear_node(info.error_msg);

        ipinfo::clear_node(info.ip);
        ipinfo::clear_node(info.ip_type);
        ipinfo::clear_node(info.reverse_dns);

        ipinfo::clear_node(info.continent);
        ipinfo::clear_node(info.continent_code);

        ipinfo::clear_node(info.country);
        ipinfo::clear_node(info.continent_code);
        ipinfo::clear_node(info.country_capital);
        ipinfo::clear_node(info.country_phone);
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
        ipinfo::clear_node(info.organization);

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


    double \
        round_double(const double value, \
                     const std::uint8_t places)
    {
        const auto div \
        {
            std::pow(10u, places)
        };

        const auto rounded_val \
        {
            (std::round(value * div)) / (div)
        };

        return rounded_val;
    }


    bool \
        is_host_correct(const std::string &host,
                        ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Empty host string"}, \
                              {__func__});
            return false;
        }

        if (!(host.empty()))
        {
            for (const auto &avail_host : ipinfo::avail_hosts)
            {
                if (avail_host == host)
                {
                    return true;
                }
            }
        }

        ipinfo::set_error(error, \
                          1u, \
                          {"Unsupported host"}, \
                          {__func__});

        return false;
    }


    bool \
        is_lang_correct(const std::string &host, \
                        const std::string &lang,
                        ipinfo::error_t &error)
    {
        if (lang.empty())
        {
            ipinfo::set_error(error, \
                              1u, \
                              {"Empty language string"}, \
                              {__func__});
            return false;
        }

        if (ipinfo::is_host_correct(host, error))
        {
            for (const auto &pair : ipinfo::avail_langs.at(host))
            {
                if (pair.first == lang)
                {
                    return true;
                }
            }
        }

        ipinfo::set_error(error, \
                          1u, \
                          {"Unsupported language"}, \
                          {__func__});
        return false;
    }


    bool \
        is_status_success(const ipinfo::info_t &info)
    {
        for (const auto &host : ipinfo::avail_hosts)
        {
            if (info.status.content.at(host).is_parsed &&
                info.status.content.at(host).value)
            {
                return true ;
            }
        }

        return false;
    }
}
