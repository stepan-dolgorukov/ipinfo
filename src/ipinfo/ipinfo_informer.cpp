#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_constants.hpp"
#include "../../include/ipinfo/ipinfo_aliases.hpp"

#include "../../include/ipinfo/ipinfo_informer.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cstdint>
#include <string>
#include <utility>
#include <algorithm>

ipinfo::usr::informer::informer(
    const std::string &ip,
    const std::string &lang) :

    __ip{ ip },
    __lang{ lang } {}

ipinfo::usr::informer::informer(
    const std::string &ip,
    const std::uint8_t lang_id) :

    __ip { ip }
{
    if (__utiler->is_lang_supported(lang_id))
    {
        __lang = constants::AVAILABLE_LANGS.at(lang_id);
    }
}

bool
ipinfo::usr::informer::__is_api_key_setted_up(const std::string &host) const
{
    return (0u != __api_keys.count(host));
}

bool
ipinfo::usr::informer::__is_host_excluded(const std::string &host) const
{
    const auto &excl_hsts{ __excluded_hosts };
    const auto res{ std::find(excl_hsts.begin(), excl_hsts.end(), host) };

    return (excl_hsts.end() != res);
}

ipinfo::srv::types::request_attributes
ipinfo::usr::informer::__get_request_attributes(const std::string &host) const
{
    std::string api_key{};

    if (__is_api_key_setted_up(host))
    {
        api_key = __api_keys.at(host);
    }

    return {
        .host{ host },
        .ip{ __ip },
        .lang{ __lang },
        .api_key{ api_key }
    };
}

void
ipinfo::usr::informer::set_connections_num(const std::uint8_t n)
{
    __conn_num = n;
}

void
ipinfo::usr::informer::set_ip(const std::string &ip)
{
    __ip = ip;
}

void
ipinfo::usr::informer::set_lang(const std::string &lang)
{
    __lang = __utiler->to_lower_case(lang);
}

void
ipinfo::usr::informer::set_lang(const std::uint8_t lang_id)
{
    if (__utiler->is_lang_supported(lang_id))
    {
        __lang = constants::AVAILABLE_LANGS.at(lang_id);
    }
}

void
ipinfo::usr::informer::set_api_key(
        const std::string &host,
        const std::string &key)
{
    if (__utiler->is_host_supported(host) and not key.empty())
    {
        __api_keys.insert(std::make_pair(host, key));
    }
}

void
ipinfo::usr::informer::informer::set_api_key(
    const std::uint8_t host_id,
    const std::string &key)
{
    if (__utiler->is_host_supported(host_id))
    {
        set_api_key(constants::AVAILABLE_HOSTS.at(host_id), key);
    }
}

void
ipi::usr::informer::set_api_keys(const std::map<als::str, als::str> &host_key)
{
    for (const auto &[host, api_key] : host_key)
    {
        set_api_key(host, api_key);
    }
}

void
ipi::usr::informer::set_api_keys(const std::map<als::u8, als::str> &host_id_key)
{
    for (const auto &[host_id, api_key] : host_id_key)
    {
        this->set_api_key(host_id, api_key);
    }
}

void
ipinfo::usr::informer::exclude_host(const std::string &host)
{
    if (__utiler->is_host_supported(host) and not __is_host_excluded(host))
    {
        __excluded_hosts.push_back(host);
    }
}

void
ipinfo::usr::informer::exclude_host(const std::uint8_t host_id)
{
    if (__utiler->is_host_supported(host_id))
    {
        __excluded_hosts.push_back(constants::AVAILABLE_HOSTS.at(host_id));
    }
}

void
ipinfo::usr::informer::exclude_hosts(const std::vector<std::string> &hosts)
{
    for (const std::string &host : hosts)
    {
        exclude_host(host);
    }
}

void
ipinfo::usr::informer::exclude_hosts(const std::vector<std::uint8_t> &hosts_ids)
{
    for (const std::uint8_t &id : hosts_ids)
    {
        exclude_host(id);
    }
}

void
ipinfo::usr::informer::run()
{
    __utiler->clear_info(__info);
    const auto &avl_hosts{ constants::AVAILABLE_HOSTS };

    if (0u == __conn_num or __conn_num > avl_hosts.size())
    {
        __conn_num = avl_hosts.size();
    }

    for (std::uint8_t i{ 0u }; i < __conn_num; i++)
    {
        const std::string &host{ avl_hosts.at(i) };

        if (__is_host_excluded(host))
        {
            continue;
        }

        std::string answ{};
        const als::req_attrs ra{ __get_request_attributes(host) };

        answ = __requester->request(ra);
        __parser->parse(answ, __info, host);
    }

    return;
}

ipinfo::usr::types::error
ipinfo::usr::informer::get_last_error(const std::string &host) const
{
    if (host.empty())
    {
        return {
            .code{ constants::ERRORS_IDS::EMPTY_HOST },
            .desc{ "Empty host string" }
        };
    }

    if (not __utiler->is_host_supported(host))
    {
        return {
            .code{ constants::ERRORS_IDS::UNSUPPORTED_HOST },
            .desc{ "This host in unsuppoted by ipinfo" }
        };
    }

    if (__is_host_excluded(host))
    {
        return {
            .code{ constants::ERRORS_IDS::EXCLUDED_HOST },
            .desc{ "This host is excluded" }
        };
    }

    return (__errors.find(host) != __errors.end()) ?
        __errors.at(host) : als::err{};
}

ipinfo::usr::types::error
ipinfo::usr::informer::get_last_error(const std::uint8_t host_id) const
{
    if (not __utiler->is_host_supported(host_id))
    {
        return {
            .code{ constants::ERRORS_IDS::UNSUPPORTED_HOST },
            .desc{ "This host is unsuppoted by ipinfo" }
        };
    }

    return get_last_error(constants::AVAILABLE_HOSTS.at(host_id));
}


std::uint8_t
ipinfo::usr::informer::get_errors_num() const
{
    std::uint8_t i{ 0u };

    for (const auto &[_, __error] : __errors)
    {
        if (constants::ERRORS_IDS::NO_ERRORS != __error.code)
        {
            i += 1;
        }
    }

    return i;
}

std::string
ipinfo::usr::informer::get_ip() const
{
    return get_ip_ex().val;
}

std::string
ipinfo::usr::informer::get_ip_type() const
{
    return get_ip_type_ex().val;
}

std::string
ipinfo::usr::informer::get_continent() const
{
    return get_continent_ex().val;
}

std::string
ipinfo::usr::informer::get_continent_code() const
{
    return get_continent_code_ex().val;
}

std::string
ipinfo::usr::informer::get_country() const
{
    return get_country_ex().val;
}

std::string
ipinfo::usr::informer::get_country_code() const
{
    return get_country_code_ex().val;
}

std::string
ipinfo::usr::informer::get_country_capital() const
{
    return get_country_capital_ex().val;
}

std::string
ipinfo::usr::informer::get_country_ph_code() const
{
    return get_country_ph_code_ex().val;
}

std::string
ipinfo::usr::informer::get_country_neighbors() const
{
    return get_country_neighbors_ex().val;
}

std::string
ipinfo::usr::informer::get_region() const
{
    return get_region_ex().val;
}

std::string
ipinfo::usr::informer::get_region_code() const
{
    return get_region_code_ex().val;
}

std::string
ipinfo::usr::informer::get_city() const
{
    return get_city_ex().val;
}

std::string
ipinfo::usr::informer::get_city_district() const
{
    return get_city_district_ex().val;
}

std::string
ipinfo::usr::informer::get_zip_code() const
{
    return get_zip_code_ex().val;
}

double
ipinfo::usr::informer::get_latitude() const
{
    return get_latitude_ex().val;
}

double
ipinfo::usr::informer::get_longitude() const
{
    return get_longitude_ex().val;
}

std::string
ipinfo::usr::informer::get_city_timezone() const
{
    return get_city_timezone_ex().val;
}

std::string
ipinfo::usr::informer::get_timezone() const
{
    return get_timezone_ex().val;
}

std::int32_t
ipinfo::usr::informer::get_gmt_offset() const
{
    return get_gmt_offset_ex().val;
}

std::int32_t
ipinfo::usr::informer::get_dst_offset() const
{
    return get_dst_offset_ex().val;
}

std::string
ipinfo::usr::informer::get_timezone_gmt() const
{
    return get_timezone_gmt_ex().val;
}

std::string
ipinfo::usr::informer::get_isp() const
{
    return get_isp_ex().val;
}

std::string
ipinfo::usr::informer::get_as() const
{
    return get_as_ex().val;
}

std::string
ipinfo::usr::informer::get_org() const
{
    return get_org_ex().val;
}

std::string
ipinfo::usr::informer::get_reverse_dns() const
{
    return get_reverse_dns_ex().val;
}

bool
ipinfo::usr::informer::get_hosting_status() const
{
    return get_hosting_status_ex().val;
}

bool
ipinfo::usr::informer::get_proxy_status() const
{
    return get_proxy_status_ex().val;
}

bool
ipinfo::usr::informer::get_mobile_status() const
{
    return get_mobile_status_ex().val;
}

std::string
ipinfo::usr::informer::get_currency() const
{
    return get_currency_ex().val;
}

std::string
ipinfo::usr::informer::get_currency_code() const
{
    return get_currency_code_ex().val;
}

std::string
ipinfo::usr::informer::get_currency_symbol() const
{
    return get_currency_symbol_ex().val;
}

double
ipinfo::usr::informer::get_currency_rates() const
{
    return get_currency_rates_ex().val;
}

std::string
ipinfo::usr::informer::get_currency_plural() const
{
    return get_currency_plural_ex().val;
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_ip_ex() const
{
    const auto &node{ __info.ip };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_ip_type_ex() const
{
    const auto &node{ __info.ip_type };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_continent_ex() const
{
    const auto &node{__info.continent};

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_continent_code_ex() const
{
    const auto &node{ __info.continent_code };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_country_ex() const
{
    const auto &node{ __info.country_code };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_country_code_ex() const
{
    const auto &node{ __info.country_code };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_country_capital_ex() const
{
    const auto &node{ __info.country_capital };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_country_ph_code_ex() const
{
    const auto &node{ __info.country_ph_code };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_country_neighbors_ex() const
{
    const auto &node{ __info.country_neighbors };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_region_ex() const
{
    const auto &node{ __info.region };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_region_code_ex() const
{
    const auto &node{ __info.region_code };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_city_ex() const
{
    const auto &node{ __info.city };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}


ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_city_district_ex() const
{
    const auto &node{ __info.city_district };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_zip_code_ex() const
{
    const auto &node{ __info.zip_code };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<double>
ipinfo::usr::informer::get_latitude_ex() const
{
    const auto &node{ __info.latitude };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ __utiler->round_val(content.val, 2u) },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<double>
ipinfo::usr::informer::get_longitude_ex() const
{
    const auto &node{ __info.longitude };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ __utiler->round_val(content.val, 2u) },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipi::usr::informer::get_timezone_ex() const
{
    const auto &node{__info.timezone};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipi::usr::informer::get_city_timezone_ex() const
{
    const auto &node{__info.city_timezone};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipi::usr::informer::get_timezone_gmt_ex() const
{
    const auto &node{__info.timezone_gmt};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::int32_t>
ipi::usr::informer::get_gmt_offset_ex() const
{
    const auto &node{__info.gmt_offset};
    const auto &avl_hosts{ipinfo::constants::AVAILABLE_HOSTS};

    for (const auto &host : avl_hosts)
    {
        const auto &content{node.cont.at(host)};

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val = content.val,
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::int32_t>
ipinfo::usr::informer::get_dst_offset_ex() const
{
    const auto &node{ __info.dst_offset };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_isp_ex() const
{
    const auto &node{ __info.isp };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_as_ex() const
{
    const auto &node{ __info.as };

    for (const auto &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_org_ex() const
{
    const auto &node{ __info.org };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_reverse_dns_ex() const
{
    const auto &node{__info.reverse_dns};

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<bool>
ipinfo::usr::informer::get_hosting_status_ex() const
{
    const auto &node{ __info.is_hosting };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<bool>
ipinfo::usr::informer::get_proxy_status_ex() const
{
    const auto &node{ __info.is_proxy };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<bool>
ipinfo::usr::informer::get_mobile_status_ex() const
{
    const auto &node{ __info.is_mobile };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_currency_ex() const
{
    const auto &node{ __info.currency };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_currency_code_ex() const
{
    const auto &node{ __info.currency_code };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_currency_symbol_ex() const
{
    const auto &node{ __info.currency_symbol };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<double>
ipinfo::usr::informer::get_currency_rates_ex() const
{
    const auto &node{ __info.currency_rates };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}

ipinfo::usr::types::node<std::string>
ipinfo::usr::informer::get_currency_plural_ex() const
{
    const auto &node{ __info.currency_plural };

    for (const std::string &host : constants::AVAILABLE_HOSTS)
    {
        const auto &content{ node.cont.at(host) };

        if (content.is_parsed)
        {
            return {
                .is_parsed{ true },
                .val{ content.val },
                .host{ host },
                .desc{ node.desc }
            };
        }
    }

    return {
        .desc{ node.desc }
    };
}
