#include "../../include/ipinfo/ipinfo_informer.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cstdint>
#include <string>
#include <utility>

ipinfo::interface::informer::informer(
        const std::string &ip,
        const std::string &lang,
        const std::uint8_t conn_num) :

    __ip{ip},
    __lang{lang},
    __conn_num{conn_num} {}

ipinfo::interface::informer::informer(
        const std::string &ip,
        const std::uint8_t &lang_id,
        const std::uint8_t conn_num) :

    __ip{ip},
    __lang{},
    __conn_num{conn_num}
{
    const auto &avl_langs{ipinfo::constants::AVAILABLE_LANGS};

    if (lang_id < avl_langs.size())
    {
        __lang = avl_langs.at(lang_id);
    }
}

void
ipinfo::interface::informer::set_conn_num(const std::uint8_t n)
{
    __conn_num = n;
    return;
}

void
ipinfo::interface::informer::set_ip(const std::string &ip)
{
    __ip = ip;
    return;
}

void
ipinfo::interface::informer::set_lang(const std::string &lang)
{
    __lang = __utiler->to_lower_case(lang);
    return;
}

void /// !!!
ipinfo::interface::informer::set_lang(const std::uint8_t lang_id)
{
    const auto &avl_langs{ipinfo::constants::AVAILABLE_LANGS};

    if (lang_id < avl_langs.size())
    {
        this->set_lang(avl_langs.at(lang_id));
    }

    return;
}

void /// !!!
ipinfo::interface::informer::set_api_key(
        const std::string &host,
        const std::string &key)
{
    if (__utiler->is_host_supported(host))
    {
        __api_keys.insert(std::make_pair(host, key));
    }

    return;
}

void
ipinfo::interface::informer::set_api_key(
        const std::uint8_t host_id,
        const std::string &key)
{
    if (__utiler->is_host_supported(host_id))
    {
        const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};
        this->set_api_key(avl_hosts.at(host_id), key);
    }

    return;
}

void
ipinfo::interface::informer::set_api_keys(
        const std::map<std::string, std::string> &host_key_mp)
{
    for (auto &&[host, api_key] : host_key_mp)
    {
        this->set_api_key(host, api_key);
    }

    return;
}

void
ipinfo::interface::informer::set_api_keys(
        const std::map<std::uint8_t, std::string> &host_id_key_mp)
{
    for (auto &&[host_id, api_key] : host_id_key_mp)
    {
        this->set_api_key(host_id, api_key);
    }

    return;
}

void
ipinfo::interface::informer::exclude_host(const std::string &host)
{
    if (__utiler->is_host_supported(host))
    {
        __excluded_hosts.push_back(host);
    }

    return;
}

void
ipinfo::interface::informer::exclude_host(const std::uint8_t host_id)
{
    if (__utiler->is_host_supported(host_id))
    {
        const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};
        __excluded_hosts.push_back(avl_hosts.at(host_id));
    }

    return;
}

void
ipinfo::interface::informer::exclude_hosts(
        const std::vector<std::string> &hosts)
{
    for (const auto &host : hosts)
    {
        this->exclude_host(host);
    }

    return;
}

void
ipinfo::interface::informer::exclude_hosts(
        const std::vector<std::uint8_t> &hosts_ids)
{
    for (const auto &id : hosts_ids)
    {
        this->exclude_host(id);
    }

    return;
}

void
ipinfo::interface::informer::run()
{
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};
    __utiler->clear_info(__info);

    if ((0u == __conn_num) || (avl_hosts.size() < __conn_num))
    {
        __conn_num = avl_hosts.size();
    }

    for (std::size_t i{0u}; (i < avl_hosts.size()) && (i < __conn_num); i++)
    {
        std::string answ{};
        const auto  &host{avl_hosts.at(i)};

        if (__utiler->is_host_excluded(host, __excluded_hosts))
        {
            continue;
        }

        answ = __requester->request(host, __ip, __lang, __api_keys[host]);
        __parser->parse(answ, __info, host);
    }

    return;
}

ipinfo::types::error
ipinfo::interface::informer::get_last_error(const std::string &host) const
{
    if (host.empty())
    {
        return {
            .code = ipinfo::constants::ERRORS_IDS::EMPTY_HOST,
            .desc{"Empty host string"}
        };
    }

    if (!(__utiler->is_host_supported(host)))
    {
        return {
            .code = ipinfo::constants::ERRORS_IDS::UNSUPPORTED_HOST,
            .desc{"This host in unsuppoted by ipinfo"}
        };
    }

    if (__utiler->is_host_excluded(host, __excluded_hosts))
    {
        return {
            .code = ipinfo::constants::ERRORS_IDS::EXCLUDED_HOST,
            .desc{"This host is excluded"}
        };
    }

    for (auto &&[__host, _] : __errors)
    {
        if (__host == host)
        {
            return __errors.at(host);
        }
    }

    // !!!
    return {};
}

ipinfo::types::error
ipinfo::interface::informer::get_last_error(const std::uint8_t host_id) const
{
    if (!(__utiler->is_host_supported(host_id)))
    {
        return {
            .code = constants::ERRORS_IDS::UNSUPPORTED_HOST,
            .desc{"This host in unsuppoted by ipinfo"}
        };
    }

    return (this->get_last_error(
                ipinfo::constants::AVAILABLE_HOSTS.at(host_id)));
}

std::size_t
ipinfo::interface::informer::get_errors_num() const
{
    auto i{0u};

    for (auto &&[_, __error] : __errors)
    {
        if (ipinfo::constants::ERRORS_IDS::NO_ERRORS != __error.code)
        {
            i += 1;
        }
    }

    return i;
}

std::string
ipinfo::interface::informer::get_ip() const
{
    return get_ip_ex().val;
}

std::string
ipinfo::interface::informer::get_ip_type() const
{
    return get_ip_type_ex().val;
}

std::string
ipinfo::interface::informer::get_continent() const
{
    return get_continent_ex().val;
}

std::string
ipinfo::interface::informer::get_continent_code() const
{
    return get_continent_code_ex().val;
}

std::string
ipinfo::interface::informer::get_country() const
{
    return get_country_ex().val;
}

std::string
ipinfo::interface::informer::get_country_code() const
{
    return get_country_code_ex().val;
}

std::string
ipinfo::interface::informer::get_country_capital() const
{
    return get_country_capital_ex().val;
}

std::string
ipinfo::interface::informer::get_country_ph_code() const
{
    return get_country_ph_code_ex().val;
}

std::string
ipinfo::interface::informer::get_country_neighbors() const
{
    return get_country_neighbors_ex().val;
}

std::string
ipinfo::interface::informer::get_region() const
{

    return get_region_ex().val;
}

std::string
ipinfo::interface::informer::get_region_code() const
{
    return get_region_code_ex().val;
}

std::string
ipinfo::interface::informer::get_city() const
{
    return get_city_ex().val;
}

std::string
ipinfo::interface::informer::get_city_district() const
{
    return get_city_district_ex().val;
}

std::string
ipinfo::interface::informer::get_zip_code() const
{
    return get_zip_code_ex().val;
}

double
ipinfo::interface::informer::get_latitude() const
{
    return get_latitude_ex().val;
}

double
ipinfo::interface::informer::get_longitude() const
{
    return get_longitude_ex().val;
}

std::string
ipinfo::interface::informer::get_city_timezone() const
{
    return get_city_timezone_ex().val;
}

std::string
ipinfo::interface::informer::get_timezone() const
{
    return get_timezone_ex().val;
}

std::int32_t
ipinfo::interface::informer::get_gmt_offset() const
{
    return get_gmt_offset_ex().val;
}

std::int32_t
ipinfo::interface::informer::get_dst_offset() const
{
    return get_dst_offset_ex().val;
}

std::string
ipinfo::interface::informer::get_timezone_gmt() const
{
    return get_timezone_gmt_ex().val;
}

std::string
ipinfo::interface::informer::get_isp() const
{
    return get_isp_ex().val;
}

std::string
ipinfo::interface::informer::get_as() const
{
    return get_as_ex().val;
}

std::string
ipinfo::interface::informer::get_org() const
{
    return get_org_ex().val;
}

std::string
ipinfo::interface::informer::get_reverse_dns() const
{
    return get_reverse_dns_ex().val;
}

bool
ipinfo::interface::informer::get_hosting_status() const
{
    return get_hosting_status_ex().val;
}

bool
ipinfo::interface::informer::get_proxy_status() const
{
    return get_proxy_status_ex().val;
}

bool
ipinfo::interface::informer::get_mobile_status() const
{
    return get_mobile_status_ex().val;
}

std::string
ipinfo::interface::informer::get_currency() const
{
    return get_currency_ex().val;
}

std::string
ipinfo::interface::informer::get_currency_code() const
{
    return get_currency_code_ex().val;
}

std::string
ipinfo::interface::informer::get_currency_symbol() const
{
    return get_currency_symbol_ex().val;
}

double
ipinfo::interface::informer::get_currency_rates() const
{
    return get_currency_rates_ex().val;
}

std::string
ipinfo::interface::informer::get_currency_plural() const
{
    return get_currency_plural_ex().val;
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_ip_ex() const
{
    const auto &node{__info.ip};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_ip_type_ex() const
{
    const auto &node{__info.ip_type};
    const auto &avail_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avail_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_continent_ex() const
{
    const auto &node{__info.continent};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content = node.cont.at(host);

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_continent_code_ex() const
{
    const auto &node{ __info.continent_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_country_ex() const
{
    const auto &node{__info.country_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_country_code_ex() const
{
    const auto &node{__info.country_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host = host,
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_country_capital_ex() const
{
    const auto &node{__info.country_capital};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_country_ph_code_ex() const
{
    const auto &node{__info.country_ph_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_country_neighbors_ex() const
{
    const auto &node{__info.country_neighbors};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_region_ex() const
{
    const auto &node{__info.region};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_region_code_ex() const
{
    const auto &node{__info.region_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_city_ex() const
{
    const auto &node{__info.city};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}


ipinfo::types::node<std::string>
ipinfo::interface::informer::get_city_district_ex() const
{
    const auto &node{__info.city_district};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_zip_code_ex() const
{
    const auto &node{__info.zip_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<double>
ipinfo::interface::informer::get_latitude_ex() const
{
    const auto &node{__info.latitude};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{__utiler->round_val(content.val, 2u)},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<double>
ipinfo::interface::informer::get_longitude_ex() const
{
    const auto &node{__info.longitude};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{__utiler->round_val(content.val, 2u)},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_timezone_ex() const
{
    const auto &node{__info.timezone};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_city_timezone_ex() const
{
    const auto &node{__info.city_timezone};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_timezone_gmt_ex() const
{
    const auto &node{__info.timezone_gmt};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::int32_t>
ipinfo::interface::informer::get_gmt_offset_ex() const
{
    const auto &node{__info.gmt_offset};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val = content.val,
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::int32_t>
ipinfo::interface::informer::get_dst_offset_ex() const
{
    const auto &node{__info.dst_offset};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val = content.val,
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_isp_ex() const
{
    const auto &node{__info.isp};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_as_ex() const
{
    const auto &node{__info.as};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_org_ex() const
{
    const auto &node{__info.org};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_reverse_dns_ex() const
{
    const auto &node{__info.reverse_dns};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<bool>
ipinfo::interface::informer::get_hosting_status_ex() const
{
    const auto &node{__info.is_hosting};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val = content.val,
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<bool>
ipinfo::interface::informer::get_proxy_status_ex() const
{
    const auto &node{__info.is_proxy};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val = content.val,
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<bool>
ipinfo::interface::informer::get_mobile_status_ex() const
{
    const auto &node{__info.is_mobile};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val = content.val,
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_currency_ex() const
{
    const auto &node{__info.currency};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_currency_code_ex() const
{
    const auto &node{__info.currency_code};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_currency_symbol_ex() const
{
    const auto &node{__info.currency_symbol};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<double>
ipinfo::interface::informer::get_currency_rates_ex() const
{
    const auto &node{ __info.currency_rates};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val = content.val,
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}

ipinfo::types::node<std::string>
ipinfo::interface::informer::get_currency_plural_ex() const
{
    const auto &node{__info.currency_plural};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{true},
                .val{content.val},
                .host{host},
                .desc{node.desc}
            };
        }
    }

    return {
        .desc{node.desc}
    };
}
