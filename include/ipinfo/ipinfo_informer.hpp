#ifndef __IPINFO__INFORMER__HPP__
    #define __IPINFO__INFORMER__HPP__

    #include <cstdint>

    #include "ipinfo_parser.hpp"
    #include "ipinfo_requester.hpp"
    #include "ipinfo_types.hpp"
    #include "ipinfo_utiler.hpp"

    namespace ipinfo
    {
        class informer
        {
            private:
                ipinfo::__requester   __requester{};
                ipinfo::__parser      __parser{};

                ipinfo::__info_t      __info{};

                std::uint8_t          __connection_nums{0u};
                std::string           __ip{0};
                std::string           __lang{"English"};

            public:
                // todo: create several class constructors
                informer(const std::string &ip,
                         const std::string &lang,
                         const std::uint8_t connection_nums);

                informer(void){};

                void                set_connection_nums(const std::uint8_t n);
                void                set_connection_nums(const std::uint8_t &&n);

                void                set_ip(const std::string &ip);
                void                set_ip(const std::string &&ip);

                void                set_lang(const std::string &lang);
                void                set_lang(const std::string &&lang);

                void                run(void);

                bool                get_status(void) const;
                std::string         get_error_msg(void) const;
                std::string         get_ip(void) const;
                std::string         get_ip_type(void) const;
                std::string         get_continent(void) const;
                std::string         get_continent_code(void) const;
                std::string         get_country(void) const;
                std::string         get_country_code(void) const;
                std::string         get_country_capital(void) const;
                std::string         get_country_phone_code(void) const;
                std::string         get_country_neighbors(void) const;
                std::string         get_region(void) const;
                std::string         get_region_code(void) const;
                std::string         get_city(void) const;
                std::string         get_city_district(void) const;
                std::string         get_zip_code(void) const;
                double              get_latitude(void) const;
                double              get_longitude(void) const;
                std::string         get_timezone(void) const;
                std::string         get_city_timezone(void) const;
                std::string         get_timezone_gmt(void) const;
                std::int32_t        get_gmt_offset(void) const;
                std::int32_t        get_dst_offset(void) const;
                std::string         get_isp(void) const;
                std::string         get_as(void) const;
                std::string         get_org(void) const;
                std::string         get_reverse_dns(void) const;
                bool                get_hosting_status(void) const;
                bool                get_proxy_status(void) const;
                bool                get_mobile_status(void) const;
                std::string         get_currency(void) const;
                std::string         get_currency_code(void) const;
                std::string         get_currency_symbol(void) const;
                double              get_currency_rates(void) const;
                std::string         get_currency_plural(void) const;
        };
    }
#endif
