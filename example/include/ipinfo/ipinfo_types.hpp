#ifndef __IPINFO__TYPES__HPP__
    #define __IPINFO__TYPES__HPP__

    #include <map>
    #include <string>

    #include "ipinfo_values.hpp"


    namespace ipinfo
    {
        // I like short type names
        typedef std::uint8_t     ui8;
        typedef std::uint32_t    ui32;
        typedef std::int32_t     i32;
        typedef std::size_t      sz;
        typedef double           dbl;
        typedef bool             bl;


        typedef struct error
        {
            ipinfo::ui8         code;
            std::string         description;
            std::string         function_name;

        } error_t;


        template<typename T>
        struct node
        {
            struct data
            {
                ipinfo::bl          is_parsed;
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
            ipinfo::node <ipinfo::bl> status
            {
                .description{"Request status"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"status"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"success"}
                        }
                    }
                }
            };

            // 2. request error message (if status isn't success)
            ipinfo::node <std::string> error_msg
            {
                .description{"Request error message"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"message"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"message"}
                        }
                    }
                }
            };

            // 3. IP address
            ipinfo::node <std::string> ip
            {
                .description{"IP address"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"query"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"ip"}
                        }
                    }
                }
            };

            // 4. type of IP address (IPv4, IPv6)
            ipinfo::node <std::string> ip_type
            {
                .description{"Type of IP address"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"type"}
                        }
                    }
                }
            };

            // 5. continent name
            ipinfo::node <std::string> continent
            {
                .description{"Continent name"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"continent"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"continent"}
                        }
                    }
                }
            };

            // 6. continent code
            ipinfo::node <std::string> continent_code
            {
                .description{"Continent code"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"continentCode"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"continent_code"}
                        }
                    }
                }
            };

            // 7. country name
            ipinfo::node <std::string> country
            {
                .description{"Country name"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"country"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"country"}
                        }
                    }
                }
            };

            // 8. country code
            ipinfo::node <std::string> country_code
            {
                .description{"Country code"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"countryCode"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"country_phone"}
                        }
                    }
                }
            };

            // 11. country neighbors
            ipinfo::node <std::string> country_neighbors
            {
                .description{"Neighboring countries"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"country_neighbours"}
                        }
                    }
                }
            };

            // 12. region name
            ipinfo::node <std::string> region
            {
                .description{"Region name"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"regionName"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"region"}
                        }
                    }
                }
            };

            // 13. region code
            ipinfo::node <std::string> region_code
            {
                .description{"Region code"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"region"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 14. city name
            ipinfo::node <std::string> city
            {
                .description{"City name"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"city"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"city"}
                        }
                    }
                }
            };

            // 15. city district, subdivision
            ipinfo::node <std::string> city_district
            {
                .description{"City district"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"district"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 16. zip code
            ipinfo::node <std::string> zip_code
            {
                .description{"ZIP code"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"zip"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 17. latitude
            ipinfo::node <ipinfo::dbl> latitude
            {
                .description{"Latitude"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0.0},
                            .str_value{0},
                            .json_name{"lat"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0.0},
                            .str_value{0},
                            .json_name{"latitude"}
                        }
                    }
                }
            };

            // 18. longitude
            ipinfo::node <ipinfo::dbl> longitude
            {
                .description{"Longitude"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0.0},
                            .str_value{0},
                            .json_name{"lon"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0.0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"timezone"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"timezone"}
                        }
                    }
                }
            };

            // 20. full timezone name
            ipinfo::node <std::string> timezone
            {
                .description{"Full timezone name"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"timezone_name"}
                        }
                    }
                }
            };

            // 21. UTC offset (in seconds)
            ipinfo::node <ipinfo::i32> gmt_offset
            {
                .description{"UTC offset (in seconds)"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"offset"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"timezone_gmtOffset"}
                        }
                    }
                }
            };

            // 22. DST (daylight savings time) offset (in seconds)
            ipinfo::node <ipinfo::i32> dst_offset
            {
                .description{"DST offset (in seconds)"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"isp"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"as"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"org"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
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
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"reverse"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 28. hosting, colocated or data center
            ipinfo::node <ipinfo::bl> is_hosting
            {
                .description{"Hosting, colocated or data center"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"hosting"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 29. proxy, VPN, Tor usage
            ipinfo::node <ipinfo::bl> is_proxy
            {
                .description{"Proxy, VPN, Tor usage"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"proxy"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 30. mobile connection usage
            ipinfo::node <ipinfo::bl> is_mobile
            {
                .description{"Mobile connection usage"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"mobile"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    }
                }
            };

            // 31. nation currency code
            ipinfo::node <std::string> currency_code
            {
                .description{"National currency code"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"currency"}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"currency_code"}
                        }
                    }
                }
            };

            // 32. national currency name
            ipinfo::node <std::string> currency
            {
                .description{"National currency name"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"currency"}
                        }
                    }
                }
            };

            // 33. national currency symbol
            ipinfo::node <std::string> currency_symbol
            {
                .description{"National currency symbol"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"currency_symbol"}
                        }
                    }
                }
            };

            // 34. the current exchange rate against the US dollar
            ipinfo::node <ipinfo::dbl> currency_rates
            {
                .description{"National currency exchange rate to USD"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"currency_rates"}
                        }
                    }
                }
            };

            // 35. currency plural
            ipinfo::node <std::string> currency_plural
            {
                .description{"National currency plural"},
                
                .content
                {
                    {
                        avail_hosts.at(0u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{0}
                        }
                    },

                    {
                        avail_hosts.at(1u),
                        {
                            .is_parsed{false},
                            .value{0},
                            .str_value{0},
                            .json_name{"currency_plural"}
                        }
                    }
                }
            };

        } info_t;
    }

#endif
