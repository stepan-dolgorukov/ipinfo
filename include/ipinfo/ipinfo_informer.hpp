#ifndef __IPINFO__INFORMER__HPP__
    #define __IPINFO__INFORMER__HPP__

    #include <cstdint>

    #include "ipinfo_parser.hpp"
    #include "ipinfo_requester.hpp"
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

                bool                get_status(void);
                std::string         get_error_msg(void);
                std::string         get_ip(void);
                std::string         get_ip_type(void);
                std::string         get_continent(void);
                std::string         get_continent_code(void);
                std::string         get_country(void);
                std::string         get_country_code(void);
                std::string         get_country_capital(void);
                std::string         get_country_phone_code(void);
                std::string         get_country_neighbors(void);
                std::string         get_region(void);
                std::string         get_region_code(void);
                std::string         get_city(void);
                std::string         get_city_district(void);
                std::string         get_zip_code(void);
                double              get_latitude(void);
                double              get_longitude(void);
                std::string         get_timezone(void);
                std::string         get_city_timezone(void);
                std::string         get_timezone_gmt(void);
                std::int32_t        get_gmt_offset(void);
                std::int32_t        get_dst_offset(void);
                std::string         get_isp(void);
                std::string         get_as(void);
                std::string         get_org(void);
                std::string         get_reverse_dns(void);
                bool                get_hosting_status(void);
                bool                get_proxy_status(void);
                bool                get_mobile_status(void);
                std::string         get_currency(void);
                std::string         get_currency_code(void);
                std::string         get_currency_symbol(void);
                double              get_currency_rates(void);
                std::string         get_currency_plural(void);
        };
    }
#endif
