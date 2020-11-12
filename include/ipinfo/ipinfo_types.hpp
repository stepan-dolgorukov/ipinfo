#ifndef __IPINFO__TYPES__HPP__
    #define __IPINFO__TYPES__HPP__


    #include <map>
    #include <string>
    #include <cstddef>
    #include <cstdint>


    #include "ipinfo_values.hpp"


    namespace ipinfo
    {
        typedef struct error
        {
            std::uint8_t    code;
            std::string     description;
            std::string     function_name;

        } error_t;


        template<typename T>
        struct node
        {
            struct data
            {
                bool                is_parsed;
                T                   value;
                std::string         str_value;
                const std::string   json_name;
            };

            const std::string                   description;
            std::map<const std::string, data>   content;
        };


        typedef struct info
        {
            // 1. request status
            ipinfo::node <bool> status
            {
                .description{"Request status"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{"status"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{"success"}
                        }
                    }
                }
            };

            // 2. request error message
            // it'll be filled if status
            // of the request wasn't success
            ipinfo::node <std::string> error_msg
            {
                .description{"Request error message"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"message"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"message"}
                        }
                    }
                }
            };

            // 3. IP address
            ipinfo::node <std::string> ip
            {
                .description{"IP address"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"query"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"ip"}
                        }
                    }
                }
            };

            // 4. type of IP address
            // IPv4, IPv6
            ipinfo::node <std::string> ip_type
            {
                .description{"Type of IP address"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"type"}
                        }
                    }
                }
            };

            // 5. continent name
            ipinfo::node <std::string> continent
            {
                .description{"Continent name"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"continent"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0u}, \
                            .json_name{"continent"}
                        }
                    }
                }
            };

            // 6. continent code
            ipinfo::node <std::string> continent_code
            {
                .description{"Continent code"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"continentCode"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"continent_code"}
                        }
                    }
                }
            };

            // 7. country name
            ipinfo::node <std::string> country
            {
                .description{"Country name"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"country"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"country"}
                        }
                    }
                }
            };

            // 8. country code
            ipinfo::node <std::string> country_code
            {
                .description{"Country code"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"countryCode"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"country_code"}
                        }
                    }
                }
            };

            // 9. country capital
            ipinfo::node <std::string> country_capital
            {
                .description{"The capital of country"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"country_capital"}
                        }
                    }
                }
            };

            // 10. country phone code
            ipinfo::node <std::string> country_phone
            {
                .description{"Country phone code"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u),
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"country_phone"}
                        }
                    }
                }
            };

            // 11. country neighbors
            ipinfo::node <std::string> country_neighbors
            {
                .description{"Neighboring countries"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"country_neighbours"}
                        }
                    }
                }
            };

            // 12. region name
            ipinfo::node <std::string> region
            {
                .description{"Region name"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"regionName"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"region"}
                        }
                    }
                }
            };

            // 13. region code
            ipinfo::node <std::string> region_code
            {
                .description{"Region code"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"region"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }
                }
            };

            // 14. city name
            ipinfo::node <std::string> city
            {
                .description{"City name"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"city"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"city"}
                        }
                    }
                }
            };

            // 15. city district, subdivision
            ipinfo::node <std::string> city_district
            {
                .description{"City district"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"district"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }
                }
            };

            // 16. zip code
            ipinfo::node <std::string> zip_code
            {
                .description{"ZIP code"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"zip"}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }
                }
            };

            // 17. latitude
            ipinfo::node <double> latitude
            {
                .description{"Latitude"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = 0.0, \
                            .str_value{0}, \
                            .json_name{"lat"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = 0.0, \
                            .str_value{0}, \
                            .json_name{"latitude"}
                        }
                    }
                }
            };

            // 18. longitude
            ipinfo::node <double> longitude
            {
                .description{"Longitude"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = 0.0, \
                            .str_value{0}, \
                            .json_name{"lon"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = 0.0, \
                            .str_value{0}, \
                            .json_name{"longitude"}
                        }
                    }
                }
            };

            // 19. city timezone
            ipinfo::node <std::string> city_timezone
            {
                .description{"City timezone"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"timezone"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"timezone"}
                        }
                    }
                }
            };

            // 20. full timezone name
            ipinfo::node <std::string> timezone
            {
                .description{"Full timezone name"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"timezone_name"}
                        }
                    }
                }
            };

            // 21. UTC offset (in seconds)
            ipinfo::node <std::int32_t> gmt_offset
            {
                .description{"UTC offset (in seconds)"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = 0, \
                            .str_value{0}, \
                            .json_name{"offset"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = 0, \
                            .str_value{0}, \
                            .json_name{"timezone_gmtOffset"}
                        }
                    }
                }
            };

            // 22. DST (daylight savings time) offset (in seconds)
            ipinfo::node <std::int32_t> dst_offset
            {
                .description{"DST offset (in seconds)"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = 0, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = 0, \
                            .str_value{0}, \
                            .json_name{"timezone_dstOffset"}
                        }
                    }
                }
            };

            // 23. timezone GMT
            ipinfo::node <std::string> timezone_gmt
            {
                .description{"Timezone GMT"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"timezone_gmt"}
                        }
                    }
                }
            };

            // 24. ISP (internet service provider)
            ipinfo::node <std::string> isp
            {
                .description{"Internet Service Provider"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"isp"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"isp"}
                        }
                    }
                }
            };

            // 25. AS (autonomous system)
            ipinfo::node <std::string> as
            {
                .description{"Autonomous system"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"as"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), 
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"as"}
                        }
                    }
                }
            };

            // 26. organization name
            ipinfo::node <std::string> organization
            {
                .description{"Organization name"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"org"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"org"}
                        }
                    }
                }
            };

            // 27. reverse DNS IP lookup
            ipinfo::node <std::string> reverse_dns
            {
                .description{"Reverse DNS of the IP"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"reverse"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0},\
                            .json_name{0}
                        }
                    }
                }
            };

            // 28. hosting, colocated or data center
            ipinfo::node <bool> is_hosting
            {
                .description{"Hosting, colocated or data center"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{"hosting"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }
                }
            };

            // 29. proxy, VPN, Tor usage
            ipinfo::node <bool> is_proxy
            {
                .description{"Proxy, VPN or Tor usage"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = false,\
                            .str_value{0}, \
                            .json_name{"proxy"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }
                }
            };

            // 30. mobile connection usage
            ipinfo::node <bool> is_mobile
            {
                .description{"Mobile connection usage"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{"mobile"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = false, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }
                }
            };

            // 31. nation currency code
            ipinfo::node <std::string> currency_code
            {
                .description{"Currency code"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"currency"}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"currency_code"}
                        }
                    }
                }
            };

            // 32. national currency name
            ipinfo::node <std::string> currency
            {
                .description{"currency name"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"currency"}
                        }
                    }
                }
            };

            // 33. national currency symbol
            ipinfo::node <std::string> currency_symbol
            {
                .description{"Currency symbol"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    },

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"currency_symbol"}
                        }
                    }
                }
            };

            // 34. the current exchange rate against the US dollar
            ipinfo::node <double> currency_rates
            {
                .description{"Currency exchange rate to USD"},

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value = 0.0, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    }, \

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value = 0.0, \
                            .str_value{0}, \
                            .json_name{"currency_rates"}
                        }
                    }
                }
            };

            // 35. currency plural
            ipinfo::node <std::string> currency_plural
            {
                .description{"National currency plural"}, \

                .content
                {
                    {
                        ipinfo::avail_hosts.at(0u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{0}
                        }
                    },\

                    {
                        ipinfo::avail_hosts.at(1u), \
                        {
                            .is_parsed = false, \
                            .value{0}, \
                            .str_value{0}, \
                            .json_name{"currency_plural"}
                        }
                    }
                }
            };

        } info_t;

    }
#endif
