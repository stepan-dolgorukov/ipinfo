#ifndef __IPINFO__TYPES__HPP__
    #define __IPINFO__TYPES__HPP__

    #include <cstddef>
    #include <cstdint>
    #include <map>
    #include <string>

    #include "ipinfo_values.hpp"

    namespace ipinfo
    {
        typedef struct __error
        {
            std::uint8_t    code{};
            std::string     desc{};
            std::string     func{};
        } __error_t;

        template<typename T> struct __data_node
        {
            struct data_content
            {
                bool                is_parsed{false};
                T                   val{};
                std::string         str_val{};
                const std::string   json_name{};
            };

            const std::string                           desc{};
            std::map<const std::string, data_content>   content{};
        };

        typedef struct __info
        {
            // 1. request status
            // can be only true or false
            ipinfo::__data_node<bool> request_status
            {
                .desc{"Request status"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"status"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"success"}
                        }
                    }
                }
            };

            // 2. request error message
            // it'll be filled if the request status isn't success
            ipinfo::__data_node<std::string> error_message
            {
                .desc{"Request error message"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"message"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"message"}
                        }
                    }
                }
            };

            // 3. IP address
            ipinfo::__data_node<std::string> ip
            {
                .desc{"IP address"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                           .json_name{"query"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"ip"}
                        }
                    }
                }
            };

            // 4. type of IP address
            // IPv4, IPv6
            ipinfo::__data_node<std::string> ip_type
            {
                .desc{"Type of IP address"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"type"}
                        }
                    }
                }
            };

            // 5. continent name
            ipinfo::__data_node<std::string> continent
            {
                .desc{"Continent name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"continent"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"continent"}
                        }
                    }
                }
            };

            // 6. continent code
            ipinfo::__data_node<std::string> continent_code
            {
                .desc{"Continent code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"continentCode"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"continent_code"}
                        }
                    }
                }
            };

            // 7. country name
            ipinfo::__data_node<std::string> country
            {
                .desc{"Country name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"country"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country"}
                        }
                    }
                }
            };

            // 8. country code
            ipinfo::__data_node<std::string> country_code
            {
                .desc{"Country code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"countryCode"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_code"}
                        }
                    }
                }
            };

            // 9. country capital
            ipinfo::__data_node<std::string> country_capital
            {
                .desc{"The capital of country"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_capital"}
                        }
                    }
                }
            };

            // 10. country phone code
            ipinfo::__data_node<std::string> country_phone
            {
                .desc{"Country phone code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_phone"}
                        }
                    }
                }
            };

            // 11. country neighbors
            ipinfo::__data_node<std::string> country_neighbors
            {
                .desc{"Neighboring countries"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_neighbours"}
                        }
                    }
                }
            };

            // 12. region name
            ipinfo::__data_node<std::string> region
            {
                .desc{"Region name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"regionName"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"region"}
                        }
                    }
                }
            };

            // 13. region code
            ipinfo::__data_node<std::string> region_code
            {
                .desc{"Region code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"region"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    }
                }
            };

            // 14. city name
            ipinfo::__data_node<std::string> city
            {
                .desc{"City name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"city"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"city"}
                        }
                    }
                }
            };

            // 15. city district (subdivision)
            ipinfo::__data_node<std::string> city_district
            {
                .desc{"City district"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"district"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    }
                }
            };

            // 16. zip code
            ipinfo::__data_node<std::string> zip_code
            {
                .desc{"ZIP code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"zip"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    },
                }
            };

            // 17. latitude
            ipinfo::__data_node<double> latitude
            {
                .desc{"Latitude"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"lat"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"latitude"}
                        }
                    }
                }
            };

            // 18. longitude
            ipinfo::__data_node<double> longitude
            {
                .desc{"Longitude"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"lon"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"longitude"}
                        }
                    }
                }
            };

            // 19. city timezone
            ipinfo::__data_node<std::string> city_timezone
            {
                .desc{"City timezone"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"timezone"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone"}
                        }
                    }
                }
            };

            // 20. full timezone name
            ipinfo::__data_node<std::string> timezone
            {
                .desc{"Full timezone name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_name"}
                        }
                    }

                }
            };

            // 21. UTC offset (in seconds)
            ipinfo::__data_node<std::int32_t> gmt_offset
            {
                .desc{"UTC offset"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"offset"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_gmtOffset"}
                        }
                    }
                }
            };

            // 22. DST (daylight savings time) offset (in seconds)
            ipinfo::__data_node<std::int32_t> dst_offset
            {
                .desc{"DST offset"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_dstOffset"}
                        }
                    }
                }
            };

            // 23. timezone GMT
            ipinfo::__data_node<std::string> timezone_gmt
            {
                .desc{"Timezone GMT"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_gmt"}
                        }
                    }
                }
            };

            // 24. ISP (internet service provider)
            ipinfo::__data_node<std::string> isp
            {
                .desc{"Internet Service Provider"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"isp"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"isp"}
                        }
                    }
                }
            };

            // 25. AS (autonomous system)
            ipinfo::__data_node<std::string> as
            {
                .desc{"Autonomous system"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"as"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"as"}
                        }
                    }
                }
            };

            // 26. organization name
            ipinfo::__data_node<std::string> organization
            {
                .desc{"Organization name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"org"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"org"}
                        }
                    }
                }
            };

            // 27. reverse DNS IP lookup
            ipinfo::__data_node<std::string> reverse_dns
            {
                .desc{"Reverse DNS of the IP"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"reverse"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    }

                }
            };

            // 28. hosting, colocated or data center
            ipinfo::__data_node<bool> is_hosting
            {
                .desc{"Hosting, colocated or data center"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"hosting"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    }

                }
            };

            // 29. proxy, VPN, Tor usage
            ipinfo::__data_node<bool> is_proxy
            {
                .desc{"Proxy, VPN or Tor usage"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"proxy"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    }
                }
            };

            // 30. mobile connection usage
            ipinfo::__data_node<bool> is_mobile
            {
                .desc{"Mobile connection usage"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"mobile"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {

                        }
                    }

                }
            };

            // 31. national currency code
            ipinfo::__data_node<std::string> currency_code
            {
                .desc{"Currency code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"currency"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_code"}
                        }
                    }
                }
            };

            // 32. national currency name
            ipinfo::__data_node<std::string> currency
            {
                .desc{"currency name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency"}
                        }
                    }
                }
            };

            // 33. national currency symbol
            ipinfo::__data_node<std::string> currency_symbol
            {
                .desc{"Currency symbol"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_symbol"}
                        }
                    }
                }
            };

            // 34. current exchange rate against the US dollar
            ipinfo::__data_node<double> currency_rates
            {
                .desc{"Currency exchange rate to USD"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {

                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_rates"}
                        }
                    }
                }
            };

            // 35. currency plural
            ipinfo::__data_node<std::string> currency_plural
            {
                .desc{"National currency plural"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"currency_plural"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_plural"}
                        }
                    }
                }
            };

        } __info_t;

    }
#endif
