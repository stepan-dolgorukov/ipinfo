#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_aliases.hpp"
#include "../../include/ipinfo/ipinfo_constants.hpp"

#include "../../include/ipinfo/ipinfo_informer.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_parser.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cstdint>
#include <string>
#include <utility>
#include <algorithm>

ipi::usr::informer::informer(
        const std::string &ip,
        const std::string &lang,
        const std::uint8_t conn_num) :

    __ip{ ip },
    __lang{ lang },
    __conn_num{ conn_num } {}

ipi::usr::informer::informer(
        const std::string &ip,
        const std::uint8_t lang_id,
        const std::uint8_t conn_num) :

    __ip{ ip },
    __conn_num{ conn_num }
{
    if (__utiler->is_lang_supported(lang_id))
    {
        __lang = constants::AVAILABLE_LANGS.at(lang_id);
    }
}

bool
ipi::usr::informer::__is_api_key_setted_up(const std::string &host) const
{
    return (0u != __api_keys.count(host));
}

bool
ipi::usr::informer::__is_host_excluded(const std::string &host) const
{
    const auto &excl_hsts{ __excluded_hosts };
    const auto res{ std::find(excl_hsts.begin(), excl_hsts.end(), host) };

    return (excl_hsts.end() != res);
}

ipinfo::als::req_attrs
ipi::usr::informer::__get_req_attrs(const std::string &host) const
{
    const std::string api_key {
        (__is_api_key_setted_up(host)) ? __api_keys.at(host) : ""
    };

    return {
        .host{ host },
        .ip{ __ip },
        .lang{ __lang },
        .api_key{ api_key }
    };
}

void
ipi::usr::informer::set_conn_num(const std::uint8_t n)
{
    __conn_num = n;
    return;
}

void
ipi::usr::informer::set_ip(const std::string &ip)
{
    __ip = ip;
    return;
}

void
ipi::usr::informer::set_lang(const std::string &lang)
{
    __lang = __utiler->to_lower_case(lang);
    return;
}

void
ipi::usr::informer::set_lang(const std::uint8_t lang_id)
{
    if (__utiler->is_lang_supported(lang_id))
    {
        __lang = ipinfo::constants::AVAILABLE_LANGS.at(lang_id);
    }

    return;
}

void
ipi::usr::informer::set_api_key(
        const std::string &host,
        const std::string &key)
{
    if (__utiler->is_host_supported(host) && !(key.empty()))
    {
        __api_keys.insert(std::make_pair(host, key));
    }

    return;
}

void
ipi::usr::informer::informer::set_api_key(
        const std::uint8_t host_id,
        const std::string &key)
{
    if (__utiler->is_host_supported(host_id))
    {
        this->set_api_key(constants::AVAILABLE_HOSTS.at(host_id), key);
    }

    return;
}

void
ipi::usr::informer::set_api_keys(
        const std::map<std::string,
                       std::string> &host_key_mp)
{
    for (const auto &[host, api_key] : host_key_mp)
    {
        this->set_api_key(host, api_key);
    }

    return;
}

void
ipi::usr::informer::set_api_keys(const std::map<als::u8, als::str> &host_id_key_mp)
{
    for (const auto &[host_id, api_key] : host_id_key_mp)
    {
        this->set_api_key(host_id, api_key);
    }

    return;
}

void
ipi::usr::informer::exclude_host(const std::string &host)
{
    if (__utiler->is_host_supported(host))
    {
        __excluded_hosts.push_back(host);
    }

    return;
}

void
ipi::usr::informer::exclude_host(const std::uint8_t host_id)
{
    if (__utiler->is_host_supported(host_id))
    {
        __excluded_hosts.push_back(constants::AVAILABLE_HOSTS.at(host_id)
        );
    }

    return;
}

void
ipi::usr::informer::exclude_hosts(
        const std::vector<std::string> &hosts)
{
    for (const auto &host : hosts)
    {
        this->exclude_host(host);
    }

    return;
}

void
ipi::usr::informer::exclude_hosts(const std::vector<als::u8> &hosts_ids)
{
    for (const auto &id : hosts_ids)
    {
        this->exclude_host(id);
    }

    return;
}

void
ipi::usr::informer::run()
{
    __utiler->clear_info(__info);
    const auto &avl_hosts{ constants::AVAILABLE_HOSTS };

    if ((0u == __conn_num) || (__conn_num > avl_hosts.size()))
    {
        __conn_num = avl_hosts.size();
    }

    for (std::uint8_t i{0u}; i < __conn_num; i++)
    {
        std::string          answ{};
        const std::string    &host{ avl_hosts.at(i) };
        const als::req_attrs req_attrs { this->__get_req_attrs(host) };

        if (this->__is_host_excluded(host)) { continue; }

        answ = __requester->request(req_attrs);
        __parser->parse(answ, __info, host);
    }

    return;
}

ipi::als::err
ipi::usr::informer::get_last_error(const std::string &host) const
{
    if (host.empty())
    {
        return {
            .code{ constants::ERRORS_IDS::EMPTY_HOST },
            .desc{ "Empty host string" }
        };
    }

    if (!(__utiler->is_host_supported(host)))
    {
        return {
            .code{ constants::ERRORS_IDS::UNSUPPORTED_HOST },
            .desc{ "This host in unsuppoted by ipinfo" }
        };
    }

    if (this->__is_host_excluded(host))
    {
        return {
            .code{ constants::ERRORS_IDS::EXCLUDED_HOST },
            .desc{ "This host is excluded" }
        };
    }

    // !!!
    for (const auto &[__host, _] : __errors)
    {
        if (__host == host)
        {
            return __errors.at(host);
        }
    }

    // !!!
    return {};
}

ipi::als::err
ipi::usr::informer::get_last_error(const std::uint8_t host_id) const
{
    if (!(__utiler->is_host_supported(host_id)))
    {
        return {
            .code{ constants::ERRORS_IDS::UNSUPPORTED_HOST },
            .desc{ "This host in unsuppoted by ipinfo" }
        };
    }

    return this->get_last_error(constants::AVAILABLE_HOSTS.at(host_id));
}


std::size_t // !!!
ipi::usr::informer::get_errors_num() const
{
    std::size_t i{0u};

    for (const auto &[_, __error] : __errors)
    {
        if (ipinfo::constants::ERRORS_IDS::NO_ERRORS != __error.code)
        {
            i += 1;
        }
    }

    return i;
}

std::string
ipi::usr::informer::get_ip() const
{
    return this->get_ip_ex().val;
}

std::string
ipi::usr::informer::get_ip_type() const
{
    return this->get_ip_type_ex().val;
}

std::string
ipi::usr::informer::get_continent() const
{
    return this->get_continent_ex().val;
}

std::string
ipi::usr::informer::get_continent_code() const
{
    return this->get_continent_code_ex().val;
}

std::string
ipi::usr::informer::get_country() const
{
    return this->get_country_ex().val;
}

std::string
ipi::usr::informer::get_country_code() const
{
    return this->get_country_code_ex().val;
}

std::string
ipi::usr::informer::get_country_capital() const
{
    return this->get_country_capital_ex().val;
}

std::string
ipi::usr::informer::get_country_ph_code() const
{
    return this->get_country_ph_code_ex().val;
}

std::string
ipi::usr::informer::get_country_neighbors() const
{
    return this->get_country_neighbors_ex().val;
}

std::string
ipi::usr::informer::get_region() const
{
    return this->get_region_ex().val;
}

std::string
ipi::usr::informer::get_region_code() const
{
    return this->get_region_code_ex().val;
}

std::string
ipi::usr::informer::get_city() const
{
    return this->get_city_ex().val;
}

std::string
ipi::usr::informer::get_city_district() const
{
    return this->get_city_district_ex().val;
}

std::string
ipi::usr::informer::get_zip_code() const
{
    return this->get_zip_code_ex().val;
}

double
ipi::usr::informer::get_latitude() const
{
    return this->get_latitude_ex().val;
}

double
ipi::usr::informer::get_longitude() const
{
    return this->get_longitude_ex().val;
}

std::string
ipi::usr::informer::get_city_timezone() const
{
    return this->get_city_timezone_ex().val;
}

std::string
ipi::usr::informer::get_timezone() const
{
    return this->get_timezone_ex().val;
}

std::int32_t
ipi::usr::informer::get_gmt_offset() const
{
    return this->get_gmt_offset_ex().val;
}

std::int32_t
ipi::usr::informer::get_dst_offset() const
{
    return this->get_dst_offset_ex().val;
}

std::string
ipi::usr::informer::get_timezone_gmt() const
{
    return this->get_timezone_gmt_ex().val;
}

std::string
ipi::usr::informer::get_isp() const
{
    return this->get_isp_ex().val;
}

std::string
ipi::usr::informer::get_as() const
{
    return this->get_as_ex().val;
}

std::string
ipi::usr::informer::get_org() const
{
    return this->get_org_ex().val;
}

std::string
ipi::usr::informer::get_reverse_dns() const
{
    return this->get_reverse_dns_ex().val;
}

bool
ipi::usr::informer::get_hosting_status() const
{
    return this->get_hosting_status_ex().val;
}

bool
ipi::usr::informer::get_proxy_status() const
{
    return this->get_proxy_status_ex().val;
}

bool
ipi::usr::informer::get_mobile_status() const
{
    return this->get_mobile_status_ex().val;
}

std::string
ipi::usr::informer::get_currency() const
{
    return this->get_currency_ex().val;
}

std::string
ipi::usr::informer::get_currency_code() const
{
    return this->get_currency_code_ex().val;
}

std::string
ipi::usr::informer::get_currency_symbol() const
{
    return this->get_currency_symbol_ex().val;
}

double
ipi::usr::informer::get_currency_rates() const
{
    return this->get_currency_rates_ex().val;
}

std::string
ipi::usr::informer::get_currency_plural() const
{
    return this->get_currency_plural_ex().val;
}

ipi::als::u_node<std::string>
ipi::usr::informer::get_ip_ex() const
{
    const auto &node{ __info.ip };
    const auto &avl_hosts{ constants::AVAILABLE_HOSTS };

    for (const auto &host : avl_hosts)
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_ip_type_ex() const
{
    const auto &node{ __info.ip_type };
    const auto &avail_hosts{ constants::AVAILABLE_HOSTS };

    for (const auto &host : avail_hosts)
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
        .desc{node.desc}
    };
}

ipi::als::u_node<std::string>
ipi::usr::informer::get_continent_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_continent_code_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_country_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_country_code_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_country_capital_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_country_ph_code_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_country_neighbors_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_region_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_region_code_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_city_ex() const
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


ipi::als::u_node<std::string>
ipi::usr::informer::get_city_district_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_zip_code_ex() const
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

ipi::als::u_node<double>
ipi::usr::informer::get_latitude_ex() const
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

ipi::als::u_node<double>
ipi::usr::informer::get_longitude_ex() const
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

ipi::als::u_node<std::string>
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

ipi::als::u_node<std::string>
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

ipi::als::u_node<std::string>
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

ipi::als::u_node<std::int32_t>
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

ipi::als::u_node<std::int32_t>
ipi::usr::informer::get_dst_offset_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_isp_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_as_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_org_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_reverse_dns_ex() const
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

ipi::als::u_node<bool>
ipi::usr::informer::get_hosting_status_ex() const
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

ipi::als::u_node<bool>
ipi::usr::informer::get_proxy_status_ex() const
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

ipi::als::u_node<bool>
ipi::usr::informer::get_mobile_status_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_currency_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_currency_code_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_currency_symbol_ex() const
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

ipi::als::u_node<double>
ipi::usr::informer::get_currency_rates_ex() const
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

ipi::als::u_node<std::string>
ipi::usr::informer::get_currency_plural_ex() const
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
