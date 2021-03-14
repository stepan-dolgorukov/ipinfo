#include <ipinfo/ipinfo.hpp>
#include <fmt/core.h>
#include <string>
#include <cstdint>

namespace app
{
    void show_ip_info(
        const std::string &ip,
        const std::string &lang);

    void show_ip_info_ex(
        const std::string &ip,
        const std::string &lang);
}

int
main(void)
{
    // app::show_ip_info("8.8.8.8", "english");
    app::show_ip_info_ex("2001:4860:4860::888", "russian");

    return 0;
}

void
app::show_ip_info(
    const std::string &ip,
    const std::string &lang)
{
    ipinfo::usr::informer infr{};
    ipinfo::usr::types::error err{};

    infr.set_ip(ip);
    infr.set_lang(lang);

    // You can set your API keys below.
    // In example they're initialized as empty strings.
    // But this initialization isn't compulsory.

    infr.set_api_keys({
        { ipi::als::C::AVAILABLE_HOSTS_IDS::IP_API_COM, {} },
        { ipi::als::C::AVAILABLE_HOSTS_IDS::IPWHOIS_APP, {} }
    });

    infr.run();

    fmt::print("IP: {:s}\n", infr.get_ip());
    fmt::print("IP type: {:s}\n", infr.get_ip_type());
    fmt::print("Continent: {:s}\n", infr.get_continent());
    fmt::print("Continent code: {}\n", infr.get_continent_code());
    fmt::print("County: {:s}\n", infr.get_country());
    fmt::print("Country code: {:s}\n", infr.get_country_code());
    fmt::print("Country capital: {:s}\n", infr.get_country_capital());
    fmt::print("Country phone code: {:s}\n", infr.get_country_ph_code());
    fmt::print("Country neighbors: {:s}\n", infr.get_country_neighbors());
    fmt::print("Region: {:s}\n", infr.get_region());
    fmt::print("Region code: {:s}\n", infr.get_region_code());
    fmt::print("City: {:s}\n", infr.get_city());
    fmt::print("City district: {:s}\n", infr.get_city_district());
    fmt::print("ZIP code: {:s}\n", infr.get_zip_code());
    fmt::print("Latitude: {:.2f}\n", infr.get_latitude());
    fmt::print("Longitude: {:.2f}\n", infr.get_longitude());
    fmt::print("Timezone: {:s}\n", infr.get_timezone());
    fmt::print("City timezone: {:s}\n", infr.get_city_timezone());
    fmt::print("Timezone GMT: {:s}\n", infr.get_timezone_gmt());
    fmt::print("GMT offset: {:d}\n", infr.get_gmt_offset());
    fmt::print("DST offset: {:d}\n", infr.get_dst_offset());
    fmt::print("ISP: {:s}\n", infr.get_isp());
    fmt::print("AS: {:s}\n", infr.get_as());
    fmt::print("Organization: {:s}\n", infr.get_org());
    fmt::print("Reverse DNS lookup: {:s}\n", infr.get_reverse_dns());
    fmt::print("Hosting, data center: {:d}\n", infr.get_hosting_status());
    fmt::print("Proxy, VPN, Tor usage: {:d}\n", infr.get_proxy_status());
    fmt::print("Mobile connection usage: {:d}\n", infr.get_mobile_status());
    fmt::print("Currency: {:s}\n", infr.get_currency());
    fmt::print("Currency code: {:s}\n",  infr.get_currency_code());
    fmt::print("Currency symbol: {:s}\n", infr.get_currency_symbol());
    fmt::print("Currency exc. rate to USD: {:.2f}\n", infr.get_currency_rates());
    fmt::print("Currency plural: {:s}\n", infr.get_currency_plural());

    return;
}

void
app::show_ip_info_ex(
    const std::string &ip,
    const std::string &lang)
{
    ipinfo::usr::informer informer{ ip, lang };
    ipinfo::usr::types::error error{};

    // You can use the ipinfo aliases.
    // They make your code rly shorter.

    ipi::als::u_node<std::string> str_cont{};
    ipi::als::u_node<std::int32_t> i32_cont{};
    ipi::als::u_node<double> dbl_cont{};
    ipi::als::u_node<bool> bool_cont{};

    const std::string
        str_fmt{ "{:s}: {:s}; parsed: {:d}; host: {:s}\n" },
        i32_fmt{ "{:s}: {:d}; parsed: {:d}; host: {:s}\n" },
        dbl_fmt{ "{:s}: {:.2f}; parsed: {:d}; host: {:s}\n" },
        bool_fmt{ "{:s}: {:d}; parsed: {:d}; host: {:s}\n" };

    // Another way of API keys setting.

    informer.set_api_key(ipi::als::C::AVAILABLE_HOSTS_IDS::IP_API_COM, {});
    informer.set_api_key(ipi::als::C::AVAILABLE_HOSTS_IDS::IPWHOIS_APP, {});

    informer.run();

    // Printing below isn't such of good,
    // we need to find a compact solution.

    str_cont = informer.get_ip_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_ip_type_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_continent_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont= informer.get_continent_code_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_country_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_country_code_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_country_capital_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_country_ph_code_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_country_neighbors_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_region_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_region_code_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_city_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_city_district_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_zip_code_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    dbl_cont = informer.get_latitude_ex();
    fmt::print(dbl_fmt, dbl_cont.desc, dbl_cont.val,
            bool{ dbl_cont.is_parsed }, dbl_cont.host);

    dbl_cont = informer.get_longitude_ex();
    fmt::print(dbl_fmt, dbl_cont.desc, dbl_cont.val,
               bool{ dbl_cont.is_parsed }, dbl_cont.host);

    str_cont = informer.get_timezone_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_city_timezone_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_timezone_gmt_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    i32_cont = informer.get_gmt_offset_ex();
    fmt::print(i32_fmt, i32_cont.desc, i32_cont.val,
               bool{ i32_cont.is_parsed }, i32_cont.host);

    i32_cont = informer.get_dst_offset_ex();
    fmt::print(i32_fmt, i32_cont.desc, i32_cont.val,
               bool{ i32_cont.is_parsed }, i32_cont.host);

    str_cont = informer.get_isp_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_as_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_org_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_reverse_dns_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    bool_cont = informer.get_hosting_status_ex();
    fmt::print(bool_fmt, bool_cont.desc, bool_cont.val,
               bool{ bool_cont.is_parsed }, bool_cont.host);

    bool_cont = informer.get_proxy_status_ex();
    fmt::print(bool_fmt, bool_cont.desc, bool_cont.val,
               bool{ bool_cont.is_parsed }, bool_cont.host);

    bool_cont = informer.get_mobile_status_ex();
    fmt::print(bool_fmt, bool_cont.desc, bool_cont.val,
               bool{ bool_cont.is_parsed }, bool_cont.host);

    str_cont = informer.get_currency_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_currency_code_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    str_cont = informer.get_currency_symbol_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    dbl_cont = informer.get_currency_rates_ex();
    fmt::print(dbl_fmt, dbl_cont.desc, dbl_cont.val,
               bool{ dbl_cont.is_parsed }, dbl_cont.host);

    str_cont = informer.get_currency_plural_ex();
    fmt::print(str_fmt, str_cont.desc, str_cont.val,
               bool{ str_cont.is_parsed }, str_cont.host);

    return;
}
