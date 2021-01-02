#include <cstdint>
#include <string>
#include <utility>

#include "../../include/ipinfo/ipinfo_informer.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

ipinfo::informer::informer(
        const std::string &ip,
        const std::string &lang,
        const std::uint8_t conn_num) : __ip(ip),
                                       __lang(lang),
                                       __conn_num(conn_num) {}
ipinfo::informer::informer(
        const std::string &ip,
        const std::uint8_t &lang_id,
        const std::uint8_t conn_num) : __ip(ip),
                                       __lang(),
                                       __conn_num(conn_num)
{
    if (lang_id < avail_langs.size())
    {
        __lang = avail_langs.at(lang_id);
    }
}

ipinfo::informer::informer() : __ip(),
                               __lang(),
                               __conn_num(0u) {}

void
ipinfo::informer::set_conn_num(const std::uint8_t n)
{
    __conn_num = n;
    return;
}

void
ipinfo::informer::set_ip(const std::string &ip)
{
    __ip = ip;
    return;
}

void
ipinfo::informer::set_lang(const std::string &lang)
{
    __lang = str_to_lower_case(lang);
    return;
}

void
ipinfo::informer::set_lang(const std::uint8_t lang_id)
{
    if (lang_id < avail_langs.size())
    {
        for (const auto &lang : avail_langs)
        {
            if (avail_langs.at(lang_id) == lang)
            {
                __lang = lang;
                break;
            }
        }
    }

    return;
}

void
ipinfo::informer::set_api_key(const std::string &host,
                              const std::string &key)
{
    if (__utiler::is_host_correct(host))
    {
        __api_keys[host] = key;
    }

    return;
}

void
ipinfo::informer::set_api_key(const std::uint8_t host_id,
                              const std::string &key)
{
    if (__utiler::is_host_correct(host_id))
    {
        set_api_key(avail_hosts.at(host_id), key);
    }

    return;
}

void
ipinfo::informer::set_api_keys(const std::map<std::string,
                                              std::string> &host_key_mp)
{
    for (const auto &[host, api_key] : host_key_mp)
    {
        set_api_key(host, api_key);
    }

    return;
}

void
ipinfo::informer::set_api_keys(const std::map<std::uint8_t,
                                              std::string> &host_id_key_mp)
{
    for (const auto &[host_id, api_key] : host_id_key_mp)
    {
        set_api_key(host_id, api_key);
    }

    return;
}

void
ipinfo::informer::exclude_host(const std::string &host)
{
    if (__utiler::is_host_correct(host))
    {
        __excluded_hosts.push_back(host);
    }

    return;
}

void
ipinfo::informer::exclude_host(const std::uint8_t host_id)
{
    if (__utiler::is_host_correct(host_id))
    {
        __excluded_hosts.push_back(avail_hosts.at(host_id));
    }

    return;
}

void
ipinfo::informer::exclude_hosts(const std::vector<std::string> &hosts)
{
    for (const auto &host : hosts)
    {
        exclude_host(host);
    }

    return;
}

void
ipinfo::informer::exclude_hosts(const std::vector<std::uint8_t> &hosts_ids)
{
    for (const auto &id : hosts_ids)
    {
        exclude_host(id);
    }

    return;
}

void
ipinfo::informer::run()
{
    ipinfo::__utiler::clear_info(__info);

    if (0u == __conn_num ||
        __conn_num > avail_hosts.size())
    {
        __conn_num = avail_hosts.size();
    }

    for (auto i{0u};
            i < avail_hosts.size() &&
            i < __conn_num; i++)
    {
        const auto &host{avail_hosts.at(i)};

        __errors.insert(std::make_pair(host, error{}));
        auto &curr_err{__errors.at(host)};

        if (__utiler::is_host_excluded(host, __excluded_hosts))
        {
            continue;
        }

        __requester::create_request_url(host,
                                        __ip,
                                        __lang,
                                        __api_keys[host]);
        __requester::send_request();

        curr_err = __requester::get_last_error();

        if (curr_err.code != ERRORS_IDS::NO_ERRORS)
        {
            return;
        }

        __parser::put_json(__requester::get_request_answer());
        __parser::deserialize_json(__info, host);

        curr_err = __parser::get_last_error();
    }

    return;
}

ipinfo::error_t
ipinfo::informer::get_last_error(const std::string &host) const
{
    for (auto &&[__host, __error] : __errors)
    {
        if (__host == host)
        {
            return __errors.at(host);
        }
    }

    // !!!
    return {};
}

ipinfo::error_t
ipinfo::informer::get_last_error(const std::uint8_t host_id) const
{
    if (host_id < avail_hosts.size())
    {
        const auto &curr_host{avail_hosts.at(host_id)};
        return __errors.at(curr_host);
    }

    // !!!
    return {};
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
    const auto &curr{__info.ip};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_ip_type_ex() const
{
    const auto &curr{__info.ip_type};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_continent_ex() const
{
    const auto &curr{__info.continent};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_continent_code_ex() const
{
    const auto &curr{__info.continent_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_country_ex() const
{
    const auto &curr{__info.country_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_country_code_ex() const
{
    const auto &curr{__info.country_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host = host,
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_country_capital_ex() const
{
    const auto &curr{__info.country_capital};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_country_ph_code_ex() const
{
    const auto &curr{__info.country_ph_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_country_neighbors_ex() const
{
    const auto& curr{__info.country_neighbors};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_region_ex() const
{
    const auto& curr{__info.region};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_region_code_ex() const
{
    const auto& curr{__info.region_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_city_ex() const
{
    const auto &curr{__info.city};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}


ipinfo::user_node<std::string>
ipinfo::informer::get_city_district_ex() const
{
    const auto &curr{__info.city_district};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_zip_code_ex() const
{
    const auto &curr{__info.zip_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<double>
ipinfo::informer::get_latitude_ex() const
{
    const auto &curr{__info.latitude};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = round_double(content.val, 2u),
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<double>
ipinfo::informer::get_longitude_ex() const
{
    const auto &curr{__info.longitude};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = round_double(content.val, 2u),
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_timezone_ex() const
{
    const auto &curr{__info.timezone};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_city_timezone_ex() const
{
    const auto& curr{__info.city_timezone};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_timezone_gmt_ex() const
{
    const auto &curr{__info.timezone_gmt};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::int32_t>
ipinfo::informer::get_gmt_offset_ex() const
{
    const auto &curr{__info.gmt_offset};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::int32_t>
ipinfo::informer::get_dst_offset_ex() const
{
    const auto &curr{__info.dst_offset};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_isp_ex() const
{
    const auto &curr{__info.isp};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_as_ex() const
{
    const auto &curr{__info.as};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_org_ex() const
{
    const auto &curr{__info.org};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_reverse_dns_ex() const
{
    const auto &curr{__info.reverse_dns};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<bool>
ipinfo::informer::get_hosting_status_ex() const
{
    const auto &curr{__info.is_hosting};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<bool>
ipinfo::informer::get_proxy_status_ex() const
{
    const auto &curr{__info.is_proxy};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<bool>
ipinfo::informer::get_mobile_status_ex() const
{
    const auto &curr{__info.is_mobile};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_currency_ex() const
{
    const auto &curr{__info.currency};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_currency_code_ex() const
{
    const auto &curr{__info.currency_code};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_currency_symbol_ex() const
{
    const auto &curr{__info.currency_symbol};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<double>
ipinfo::informer::get_currency_rates_ex() const
{
    const auto& curr{__info.currency_rates};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val = content.val,
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}

ipinfo::user_node<std::string>
ipinfo::informer::get_currency_plural_ex() const
{
    const auto &curr{__info.currency_plural};

    for (const auto &host : ipinfo::avail_hosts)
    {
        const auto &content{curr.content.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed = true,
                .val{content.val},
                .host{host},
                .desc{curr.desc}
            };
        }
    }

    return {
        .desc{curr.desc}
    };
}
