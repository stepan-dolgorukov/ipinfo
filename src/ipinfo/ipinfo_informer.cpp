#include <cstdint>
#include <string>
#include <iostream>

#include "../../include/ipinfo/ipinfo_informer.hpp"


ipinfo::informer::informer(const std::string &ip,
                           const std::string &lang,
                           const std::uint8_t connection_nums)
{
    this->__ip = ip;
    this->__lang = lang;
    this->__connection_nums = connection_nums;
}


void
ipinfo::informer::set_connection_nums(const std::uint8_t n)
{
    this->__connection_nums = n;
}


void
ipinfo::informer::set_connection_nums(const std::uint8_t &&n)
{
    this->__connection_nums = n;
}


void
ipinfo::informer::set_ip(const std::string &ip)
{
    this->__ip= ip;
}


void
ipinfo::informer::set_ip(const std::string &&ip)
{
    this->__ip = ip;
}


void
ipinfo::informer::set_lang(const std::string &lang)
{
    this->__lang = lang;
}


void
ipinfo::informer::set_lang(const std::string &&lang)
{
    this->__lang = lang;
}


void
ipinfo::informer::run()
{
    ipinfo::__utiler::clear_info(this->__info);

    std::map<const std::string, std::string> urls{};
    std::map<const std::string, std::string> answers{};
    std::size_t counter{0u};

    for (const auto &host : ipinfo::avail_hosts)
    {
        if (this->__connection_nums != 0u)
        {
            if (this->__connection_nums < ++counter)
            {
                break;
            }
        }

        urls[host] = this->__requester.get_full_url(host,
                                                    this->__ip,
                                                    this->__lang);
        if (urls.at(host).empty())
        {
            // log!
            continue;
        }

        answers[host] = this->__requester.make_request(urls.at(host));

        if (answers.at(host).empty())
        {
            // log!
            continue;
        }

        this->__parser.parse_data(host, answers.at(host), this->__info);
    }

    return;
}


std::string
ipinfo::informer::get_ip() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.ip.content.at(host)};

        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_ip_type() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.ip_type.content.at(host)};

        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_continent() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.continent.content.at(host)};

        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_continent_code() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.continent_code.content.at(host)};

        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_country() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.country.content.at(host)};

        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_country_code() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.country_code.content.at(host)};

        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_country_capital() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.country_capital.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {"N/A"};
}


std::string
ipinfo::informer::get_country_phone_code() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.country_phone.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_country_neighbors() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.country_neighbors.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_region() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.region.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_region_code() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.region_code.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_city() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.city.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_city_district() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.city_district.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_zip_code() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.zip_code.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


double
ipinfo::informer::get_latitude() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.latitude.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


double
ipinfo::informer::get_longitude() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.longitude.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_city_timezone() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.city_timezone.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_timezone() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.timezone.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::int32_t
ipinfo::informer::get_gmt_offset() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.gmt_offset.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::int32_t
ipinfo::informer::get_dst_offset() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.dst_offset.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_timezone_gmt() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.timezone_gmt.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_isp() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.isp.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_as() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.as.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_org() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.org.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_reverse_dns() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.reverse_dns.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


bool
ipinfo::informer::get_hosting_status() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.is_hosting.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


bool
ipinfo::informer::get_proxy_status() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.is_proxy.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


bool
ipinfo::informer::get_mobile_status() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.is_mobile.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_currency() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.currency.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_currency_code() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.currency_code.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_currency_symbol() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.currency_symbol.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


double
ipinfo::informer::get_currency_rates() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.currency_rates.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


std::string
ipinfo::informer::get_currency_plural() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.currency_plural.content.at(host)};
        if (content.is_parsed)
        {
            return content.val;
        }
    }

    return {};
}


ipinfo::user_node<std::string>
ipinfo::informer::get_ip_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.ip.content.at(host)};
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
        const auto &content{this->__info.ip_type.content.at(host)};
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
        const auto &content{this->__info.continent.content.at(host)};
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
        const auto &content{this->__info.continent_code.content.at(host)};
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
        const auto &content{this->__info.country.content.at(host)};
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
        const auto &content{this->__info.country_code.content.at(host)};
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
        const auto &content{this->__info.country_capital.content.at(host)};
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
ipinfo::informer::get_country_phone_code_ex() const
{
    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{this->__info.country_phone.content.at(host)};
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
        const auto &content{this->__info.country_neighbors.content.at(host)};
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
        const auto &content{this->__info.region.content.at(host)};
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
        const auto &content{this->__info.region_code.content.at(host)};
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
        const auto &content{this->__info.city.content.at(host)};
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
        const auto &content{this->__info.city_district.content.at(host)};
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
        const auto &content{this->__info.zip_code.content.at(host)};
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
        const auto &content{this->__info.latitude.content.at(host)};
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
        const auto &content{this->__info.longitude.content.at(host)};
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
        const auto &content{this->__info.timezone.content.at(host)};
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
        const auto &content{this->__info.city_timezone.content.at(host)};
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
        const auto &content{this->__info.timezone_gmt.content.at(host)};
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
        const auto &content{this->__info.gmt_offset.content.at(host)};
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
        const auto &content{this->__info.dst_offset.content.at(host)};
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
        const auto &content{this->__info.isp.content.at(host)};
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
        const auto &content{this->__info.as.content.at(host)};
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
        const auto &content{this->__info.org.content.at(host)};
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
        const auto &content{this->__info.reverse_dns.content.at(host)};
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
        const auto &content{this->__info.is_hosting.content.at(host)};
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
        const auto &content{this->__info.is_proxy.content.at(host)};
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
        const auto &content{this->__info.is_mobile.content.at(host)};
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
        const auto &content{this->__info.currency.content.at(host)};
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
        const auto &content{this->__info.currency_code.content.at(host)};
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
        const auto &content{this->__info.currency_symbol.content.at(host)};
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
        const auto &content{this->__info.currency_rates.content.at(host)};
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
        const auto &content{this->__info.currency_plural.content.at(host)};
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
