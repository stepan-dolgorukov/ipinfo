#ifndef IPINFO_INFORMER_HPP
    #define IPINFO_INFORMER_HPP

#include "ipinfo_constants.hpp"
#include "ipinfo_types.hpp"
#include "ipinfo_aliases.hpp"

#include <cstdint> // std::uint8_t
#include <cstddef> // std::size_t

#include <string> // std::string
#include <vector> // std::vector
#include <map>    // std::map

namespace ipinfo::srv
{
    class requester;
    class parser;
    class utiler;
}

namespace ipinfo::usr { class informer; }
class ipinfo::usr::informer
{
    private:
        std::string  __ip{};
        std::string  __lang{};
        std::uint8_t __conn_num{ 0u };

        std::map<std::string, als::err>    __errors{};
        std::map<std::string, std::string> __api_keys{};
        std::vector<std::string>           __excluded_hosts{};

        als::info        __info{};
        srv::requester * __requester{};
        srv::parser    * __parser{};
        srv::utiler    * __utiler{};

        bool           __is_api_key_setted_up(const als::str &host) const;
        bool           __is_host_excluded(const als::str &host)     const;
        als::req_attrs __get_req_attrs(const als::str &host)        const;

    public:
        informer() = default;

        informer(const std::string &ip,
                 const std::string &lang,
                 const std::uint8_t conn_num);

        informer(const std::string &ip,
                 const std::uint8_t lang_id,
                 const std::uint8_t conn_num);

        void set_ip(const std::string &ip);

        void set_lang(const std::string &lang);
        void set_lang(const std::uint8_t lang_id);

        void set_conn_num(const std::uint8_t n);

        void set_api_key(const std::string &host, const std::string &key);
        void set_api_key(const std::uint8_t host_id, const std::string &key);

        void set_api_keys(const std::map<als::str, als::str> &host_key_mp);
        void set_api_keys(const std::map<als::u8, als::str> &host_id_key_mp);

        void exclude_host(const std::string &host);
        void exclude_host(const std::uint8_t host_id);

        void exclude_hosts(const std::vector<std::string> &hosts);
        void exclude_hosts(const std::vector<std::uint8_t> &hosts_ids);

        void run(void); // let's ROLL!

        usr::types::error get_last_error(const std::string &host)    const;
        usr::types::error get_last_error(const std::uint8_t host_id) const;
        std::size_t       get_errors_num(void)                       const;

        // ordinary getters
        std::string  get_ip(void)                const;
        std::string  get_ip_type(void)           const;
        std::string  get_continent(void)         const;
        std::string  get_continent_code(void)    const;
        std::string  get_country(void)           const;
        std::string  get_country_code(void)      const;
        std::string  get_country_capital(void)   const;
        std::string  get_country_ph_code(void)   const;
        std::string  get_country_neighbors(void) const;
        std::string  get_region(void)            const;
        std::string  get_region_code(void)       const;
        std::string  get_city(void)              const;
        std::string  get_city_district(void)     const;
        std::string  get_zip_code(void)          const;
        double       get_latitude(void)          const;
        double       get_longitude(void)         const;
        std::string  get_timezone(void)          const;
        std::string  get_city_timezone(void)     const;
        std::string  get_timezone_gmt(void)      const;
        std::int32_t get_gmt_offset(void)        const;
        std::int32_t get_dst_offset(void)        const;
        std::string  get_isp(void)               const;
        std::string  get_as(void)                const;
        std::string  get_org(void)               const;
        std::string  get_reverse_dns(void)       const;
        bool         get_hosting_status(void)    const;
        bool         get_proxy_status(void)      const;
        bool         get_mobile_status(void)     const;
        std::string  get_currency(void)          const;
        std::string  get_currency_code(void)     const;
        std::string  get_currency_symbol(void)   const;
        double       get_currency_rates(void)    const;
        std::string  get_currency_plural(void)   const;

        // extra information getters
        als::u_node<std::string>  get_ip_ex(void)                const;
        als::u_node<std::string>  get_ip_type_ex(void)           const;
        als::u_node<std::string>  get_continent_ex(void)         const;
        als::u_node<std::string>  get_continent_code_ex(void)    const;
        als::u_node<std::string>  get_country_ex(void)           const;
        als::u_node<std::string>  get_country_code_ex(void)      const;
        als::u_node<std::string>  get_country_capital_ex(void)   const;
        als::u_node<std::string>  get_country_ph_code_ex(void)   const;
        als::u_node<std::string>  get_country_neighbors_ex(void) const;
        als::u_node<std::string>  get_region_ex(void)            const;
        als::u_node<std::string>  get_region_code_ex(void)       const;
        als::u_node<std::string>  get_city_ex(void)              const;
        als::u_node<std::string>  get_city_district_ex(void)     const;
        als::u_node<std::string>  get_zip_code_ex(void)          const;
        als::u_node<double>       get_latitude_ex(void)          const;
        als::u_node<double>       get_longitude_ex(void)         const;
        als::u_node<std::string>  get_timezone_ex(void)          const;
        als::u_node<std::string>  get_city_timezone_ex(void)     const;
        als::u_node<std::string>  get_timezone_gmt_ex(void)      const;
        als::u_node<std::int32_t> get_gmt_offset_ex(void)        const;
        als::u_node<std::int32_t> get_dst_offset_ex(void)        const;
        als::u_node<std::string>  get_isp_ex(void)               const;
        als::u_node<std::string>  get_as_ex(void)                const;
        als::u_node<std::string>  get_org_ex(void)               const;
        als::u_node<std::string>  get_reverse_dns_ex(void)       const;
        als::u_node<bool>         get_hosting_status_ex(void)    const;
        als::u_node<bool>         get_proxy_status_ex(void)      const;
        als::u_node<bool>         get_mobile_status_ex(void)     const;
        als::u_node<std::string>  get_currency_ex(void)          const;
        als::u_node<std::string>  get_currency_code_ex(void)     const;
        als::u_node<std::string>  get_currency_symbol_ex(void)   const;
        als::u_node<double>       get_currency_rates_ex(void)    const;
        als::u_node<std::string>  get_currency_plural_ex(void)   const;
};

#endif // IPINFO_INFORMER_HPP
