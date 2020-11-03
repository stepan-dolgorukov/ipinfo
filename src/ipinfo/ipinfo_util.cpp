#include <math.h>


#include "../../include/ipinfo/ipinfo.hpp"
#include "../../include/ipinfo/ipinfo_util.hpp"


namespace ipinfo
{
    void \
        set_error(ipinfo::error_t &error, \
                    const ipinfo::ui8 code, \
                    const std::string &description, \
                    const std::string &function_name)
    {
        error.code = (code);
        error.description = (description);
        error.function_name = (function_name);

        return;
    }


    template<typename T> static void \
        clear_node(node<T> &node)
    {
        for (const auto &host : ipinfo::avail_hosts)
        {
            if ((typeid(ipinfo::ui32).hash_code()) == (typeid(T).hash_code()))
            {
                node.content.at(host).value = (0u);
            }

            else
            {
                node.content.at(host).value = (0);
            }

            node.content.at(host).str_value = ("");
            node.content.at(host).is_parsed = (false);
        }

        return;
    }


    template<> void \
        clear_node(node<std::string> &node)
    {
        for (const auto &host : ipinfo::avail_hosts)
        {
            node.content.at(host).value = ("");
            node.content.at(host).str_value = ("");
            node.content.at(host).is_parsed = (false);
        }

        return;
    }


    void \
        clear_info(ipinfo::info_t &info)
    {
        ipinfo::clear_node<ipinfo::bl>(info.status);
        ipinfo::clear_node<std::string>(info.error_msg);

        ipinfo::clear_node<std::string>(info.ip);
        ipinfo::clear_node<std::string>(info.ip_type);
        ipinfo::clear_node<std::string>(info.reverse_dns);

        ipinfo::clear_node<std::string>(info.continent);
        ipinfo::clear_node<std::string>(info.continent_code);

        ipinfo::clear_node<std::string>(info.country);
        ipinfo::clear_node<std::string>(info.continent_code);
        ipinfo::clear_node<std::string>(info.country_capital);
        ipinfo::clear_node<std::string>(info.country_phone);
        ipinfo::clear_node<std::string>(info.country_neighbors);


        ipinfo::clear_node<std::string>(info.region);
        ipinfo::clear_node<std::string>(info.region_code);

        ipinfo::clear_node<std::string>(info.city);
        ipinfo::clear_node<std::string>(info.city_district);
        ipinfo::clear_node<std::string>(info.city_timezone);

        ipinfo::clear_node<std::string>(info.zip_code);

        ipinfo::clear_node<ipinfo::dbl>(info.latitude);
        ipinfo::clear_node<ipinfo::dbl>(info.longitude);

        ipinfo::clear_node<ipinfo::i32>(info.gmt_offset);
        ipinfo::clear_node<ipinfo::i32>(info.dst_offset);
        ipinfo::clear_node<std::string>(info.timezone_gmt);

        ipinfo::clear_node<std::string>(info.isp);
        ipinfo::clear_node<std::string>(info.as);
        ipinfo::clear_node<std::string>(info.organization);

        ipinfo::clear_node<ipinfo::bl>(info.is_hosting);
        ipinfo::clear_node<ipinfo::bl>(info.is_proxy);
        ipinfo::clear_node<ipinfo::bl>(info.is_mobile);

        ipinfo::clear_node<std::string>(info.currency);
        ipinfo::clear_node<std::string>(info.currency_code);
        ipinfo::clear_node<std::string>(info.currency_symbol);
        ipinfo::clear_node<ipinfo::dbl>(info.currency_rates);
        ipinfo::clear_node<std::string>(info.currency_plural);

        return;
    }


    ipinfo::dbl \
        round_dbl(const ipinfo::dbl value, \
                  const ipinfo::ui8 places)
    {
        const auto div \
        {
            std::pow(ipinfo::ui32{10u}, places)
        };

        const auto rounded_val \
        {
            (std::floor(value * div)) / (div)
        };

        return (ipinfo::dbl{rounded_val});
    }


    bool \
        is_host_avail(const std::string &host)
    {
        if (host.empty())
        {
            return bool{false};
        }

        for (const auto &v : ipinfo::avail_hosts)
        {
            if (int{0} == (v.compare(host)))
            {
                return (bool{true});
            }
        }

        return (bool{false});
    }


    bool \
        is_lang_avail(const std::string &host, \
                      const std::string &lang)
    {
        if (lang.empty())
        {
            return bool{false};
        }

        if (ipinfo::is_host_avail(host))
        {
            for (const auto &pair : ipinfo::avail_langs.at(host))
            {
                if (int{0} == pair.first.compare(lang))
                {
                    return bool{true};
                }
            }
        }

        return (bool{false});
    }
}
