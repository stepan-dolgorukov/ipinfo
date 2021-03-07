#ifndef IPINFO_INFORMER_HPP
    #define IPINFO_INFORMER_HPP

#include "ipinfo_constants.hpp"
#include "ipinfo_types.hpp"
#include "ipinfo_aliases.hpp"

#include <cstdint>
#include <cstddef>

#include <string>
#include <vector>
#include <map>

namespace ipinfo::srv
{
    class requester;
    class parser;
    class utiler;
}

namespace ipinfo::usr
{
    class informer;
}

class ipinfo::usr::informer
{
  private:
    std::string __ip{};
    std::string __lang{};
    std::uint8_t __conn_num{ 0u };

    std::map<std::string, usr::types::error> __errors{};
    std::map<std::string, std::string> __api_keys{};
    std::vector<std::string> __excluded_hosts{};
    srv::types::info __info{};

    srv::requester * const __requester{};
    srv::parser * const __parser{};
    srv::utiler * const __utiler{};

    bool __is_api_key_setted_up(const std::string &host) const;
    bool __is_host_excluded(const std::string &host) const;
    als::req_attrs __get_request_attributes(const std::string &host) const;

  public:
    informer() = default;

    informer(
        const std::string &ip,
        const std::string &lang);

    informer(
        const std::string &ip,
        const std::uint8_t lang_id);

    void set_ip(const std::string &ip);
    void set_connections_num(const std::uint8_t n);

    void set_lang(const std::string &lang);
    void set_lang(const std::uint8_t lang_id);

    void set_api_key(
        const std::string &host,
        const std::string &key);

    void set_api_key(
        const std::uint8_t host_id,
        const std::string &key);

    void set_api_keys(const std::map<als::str, als::str> &host_key_mp);
    void set_api_keys(const std::map<als::u8, als::str> &host_id_key_mp);

    void exclude_host(const std::string &host);
    void exclude_host(const std::uint8_t host_id);

    void exclude_hosts(const std::vector<std::string> &hosts);
    void exclude_hosts(const std::vector<std::uint8_t> &hosts_ids);

    void run(); // let's ROLL!

    usr::types::error get_last_error(const std::string &host) const;
    usr::types::error get_last_error(const std::uint8_t host_id) const;
    std::uint8_t get_errors_num() const;

    // ordinary getters
    std::string get_ip() const;
    std::string get_ip_type() const;
    std::string get_continent() const;
    std::string get_continent_code() const;
    std::string get_country() const;
    std::string get_country_code() const;
    std::string get_country_capital() const;
    std::string get_country_ph_code() const;
    std::string get_country_neighbors() const;
    std::string get_region() const;
    std::string get_region_code() const;
    std::string get_city() const;
    std::string get_city_district() const;
    std::string get_zip_code() const;
    double get_latitude() const;
    double get_longitude() const;
    std::string get_timezone() const;
    std::string get_city_timezone() const;
    std::string get_timezone_gmt() const;
    std::int32_t get_gmt_offset() const;
    std::int32_t get_dst_offset() const;
    std::string get_isp() const;
    std::string get_as() const;
    std::string get_org() const;
    std::string get_reverse_dns() const;
    bool get_hosting_status() const;
    bool get_proxy_status() const;
    bool get_mobile_status() const;
    std::string get_currency() const;
    std::string get_currency_code() const;
    std::string get_currency_symbol() const;
    double get_currency_rates() const;
    std::string get_currency_plural() const;

    // extra information getters
    als::u_node<std::string> get_ip_ex() const;
    als::u_node<std::string> get_ip_type_ex() const;
    als::u_node<std::string> get_continent_ex() const;
    als::u_node<std::string> get_continent_code_ex() const;
    als::u_node<std::string> get_country_ex() const;
    als::u_node<std::string> get_country_code_ex() const;
    als::u_node<std::string> get_country_capital_ex() const;
    als::u_node<std::string> get_country_ph_code_ex() const;
    als::u_node<std::string> get_country_neighbors_ex() const;
    als::u_node<std::string> get_region_ex() const;
    als::u_node<std::string> get_region_code_ex() const;
    als::u_node<std::string> get_city_ex() const;
    als::u_node<std::string> get_city_district_ex() const;
    als::u_node<std::string> get_zip_code_ex() const;
    als::u_node<double> get_latitude_ex() const;
    als::u_node<double> get_longitude_ex() const;
    als::u_node<std::string> get_timezone_ex() const;
    als::u_node<std::string> get_city_timezone_ex() const;
    als::u_node<std::string> get_timezone_gmt_ex() const;
    als::u_node<std::int32_t> get_gmt_offset_ex() const;
    als::u_node<std::int32_t> get_dst_offset_ex() const;
    als::u_node<std::string> get_isp_ex() const;
    als::u_node<std::string> get_as_ex() const;
    als::u_node<std::string> get_org_ex() const;
    als::u_node<std::string> get_reverse_dns_ex() const;
    als::u_node<bool> get_hosting_status_ex() const;
    als::u_node<bool> get_proxy_status_ex() const;
    als::u_node<bool> get_mobile_status_ex() const;
    als::u_node<std::string> get_currency_ex() const;
    als::u_node<std::string> get_currency_code_ex() const;
    als::u_node<std::string> get_currency_symbol_ex() const;
    als::u_node<double>      get_currency_rates_ex() const;
    als::u_node<std::string> get_currency_plural_ex() const;
};

#endif // IPINFO_INFORMER_HPP
