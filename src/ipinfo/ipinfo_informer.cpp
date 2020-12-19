#include <cstdint>
#include <string>

#include "../../include/ipinfo/ipinfo_informer.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

ipinfo::informer::informer(const std::string &ip,
                           const std::string &lang,
                           const std::uint8_t connection_nums)
{
    __ip = ip;
    __lang = lang;
    __connection_nums = connection_nums;
}


void
ipinfo::informer::set_connection_nums(const std::uint8_t n)
{
    __connection_nums = n;
    return;
}


void
ipinfo::informer::set_connection_nums(const std::uint8_t &&n)
{
    __connection_nums = n;
    return;
}


void
ipinfo::informer::set_ip(const std::string &ip)
{
    __ip= ip;
    return;
}


void
ipinfo::informer::set_ip(const std::string &&ip)
{
    __ip = ip;
    return;
}


void
ipinfo::informer::set_lang(const std::string &lang)
{
    __lang = ipinfo::__utiler::str_to_lower_case(lang);
    return;
}


void
ipinfo::informer::set_lang(const std::string &&lang)
{
    __lang = ipinfo::__utiler::str_to_lower_case(lang);
    return;
}


void
ipinfo::informer::run()
{
    ipinfo::__utiler::clear_info(__info);

    std::map<const std::string, std::string> urls{};
    std::map<const std::string, std::string> answers{};
    auto counter{0u};

    for (const auto &host : ipinfo::avail_hosts)
    {
        if (__connection_nums != 0u)
        {
            if (__connection_nums < ++counter)
            {
                break;
            }
        }

        urls[host] = get_full_url(host, __ip, __lang);
        if (urls.at(host).empty())
        {
            // log!
            continue;
        }

        answers[host] = make_request(urls.at(host));

        if (answers.at(host).empty())
        {
            // log!
            continue;
        }

        parse_data(host, answers.at(host), __info);
    }

    return;
}


std::string
ipinfo::informer::get_ip() const
{
    return get_ip_ex().val;
}


std::string
ipinfo::informer::get_ip_type() const
{
    return get_ip_type_ex().val;
}


std::string
ipinfo::informer::get_continent() const
{
    return get_continent_ex().val;
}


std::string
ipinfo::informer::get_continent_code() const
{
    return get_continent_code_ex().val;
}


std::string
ipinfo::informer::get_country() const
{
    return get_country_ex().val;
}


std::string
ipinfo::informer::get_country_code() const
{
    return get_country_code_ex().val;
}


std::string
ipinfo::informer::get_country_capital() const
{
    return get_country_capital_ex().val;
}


std::string
ipinfo::informer::get_country_ph_code() const
{
    return get_country_ph_code_ex().val;
}


std::string
ipinfo::informer::get_country_neighbors() const
{
    return get_country_neighbors_ex().val;
}


std::string
ipinfo::informer::get_region() const
{

    return get_region_ex().val;
}


std::string
ipinfo::informer::get_region_code() const
{
    return get_region_code_ex().val;
}


std::string
ipinfo::informer::get_city() const
{
    return get_city_ex().val;
}


std::string
ipinfo::informer::get_city_district() const
{
    return get_city_district_ex().val;
}


std::string
ipinfo::informer::get_zip_code() const
{
    return get_zip_code_ex().val;
}


double
ipinfo::informer::get_latitude() const
{
    return get_latitude_ex().val;
}


double
ipinfo::informer::get_longitude() const
{
    return get_longitude_ex().val;
}


std::string
ipinfo::informer::get_city_timezone() const
{
    return get_city_timezone_ex().val;
}


std::string
ipinfo::informer::get_timezone() const
{
    return get_timezone_ex().val;
}


std::int32_t
ipinfo::informer::get_gmt_offset() const
{
    return get_gmt_offset_ex().val;
}


std::int32_t
ipinfo::informer::get_dst_offset() const
{
    return get_dst_offset_ex().val;
}


std::string
ipinfo::informer::get_timezone_gmt() const
{
    return get_timezone_gmt_ex().val;
}


std::string
ipinfo::informer::get_isp() const
{
    return get_isp_ex().val;
}


std::string
ipinfo::informer::get_as() const
{
    return get_as_ex().val;
}


std::string
ipinfo::informer::get_org() const
{
    return get_org_ex().val;
}


std::string
ipinfo::informer::get_reverse_dns() const
{
    return get_reverse_dns_ex().val;
}


bool
ipinfo::informer::get_hosting_status() const
{
    return get_hosting_status_ex().val;
}


bool
ipinfo::informer::get_proxy_status() const
{
    return get_proxy_status_ex().val;
}


bool
ipinfo::informer::get_mobile_status() const
{
    return get_mobile_status_ex().val;
}


std::string
ipinfo::informer::get_currency() const
{
    return get_currency_ex().val;
}


std::string
ipinfo::informer::get_currency_code() const
{
    return get_currency_code_ex().val;
}


std::string
ipinfo::informer::get_currency_symbol() const
{
    return get_currency_symbol_ex().val;
}


double
ipinfo::informer::get_currency_rates() const
{
    return get_currency_rates_ex().val;
}


std::string
ipinfo::informer::get_currency_plural() const
{
    return get_currency_plural_ex().val;
}


ipinfo::user_node<std::string>
ipinfo::informer::get_ip_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.ip.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_ip_type_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.ip_type.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_continent_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.continent.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_continent_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.continent_code.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_country_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.country.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_country_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.country_code.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_country_capital_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.country_capital.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_country_ph_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.country_ph_code.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_country_neighbors_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.country_neighbors.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_region_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.region.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}



ipinfo::user_node<std::string>
ipinfo::informer::get_region_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.region_code.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_city_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.city.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_city_district_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.city_district.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_zip_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.zip_code.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<double>
ipinfo::informer::get_latitude_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.latitude.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<double>
ipinfo::informer::get_longitude_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.longitude.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_timezone_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.timezone.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_city_timezone_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.city_timezone.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}



ipinfo::user_node<std::string>
ipinfo::informer::get_timezone_gmt_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.timezone_gmt.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::int32_t>
ipinfo::informer::get_gmt_offset_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.gmt_offset.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}



ipinfo::user_node<std::int32_t>
ipinfo::informer::get_dst_offset_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.dst_offset.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}



ipinfo::user_node<std::string>
ipinfo::informer::get_isp_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.isp.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_as_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.as.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_org_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.org.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_reverse_dns_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.reverse_dns.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<bool>
ipinfo::informer::get_hosting_status_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.is_hosting.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}



ipinfo::user_node<bool>
ipinfo::informer::get_proxy_status_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.is_proxy.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}

ipinfo::user_node<bool>
ipinfo::informer::get_mobile_status_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.is_mobile.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_currency_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.currency.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}



ipinfo::user_node<std::string>
ipinfo::informer::get_currency_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.currency_code.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_currency_symbol_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.currency_symbol.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<double>
ipinfo::informer::get_currency_rates_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.currency_rates.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_currency_plural_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{__info.currency_plural.content.at(host)};
        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host = host
            };
        }
    }

    return {};
}
