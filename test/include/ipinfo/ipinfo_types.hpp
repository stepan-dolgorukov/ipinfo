#ifndef __IPINFO__TYPES__HPP__
    #define __IPINFO__TYPES__HPP__

    #include <cstddef>
    #include <cstdint>
    #include <map>
    #include <string>

    #include "ipinfo_values.hpp"

    namespace ipinfo
    {
        typedef struct error
        {
            std::uint8_t    code{0u};
            std::string     desc{"No error"};

            std::string     part{};
            std::string     func{};
        } error_t;

        template<typename T> struct __data_node
        {
            struct data_content
            {
                bool                is_parsed : 1 {false};
                T                   val{};
                std::string         str_val{};
                const std::string   json_name{};
            };

            const std::string                           desc{};
            std::map<const std::string, data_content>   content{};
        };

        template<typename T> struct user_node
        {
            bool            is_parsed : 1 {false};
            T               val{};
            std::string     host{};
            std::string     desc{};
        };

        typedef struct __info
        {
            __data_node<std::string> ip
            {
                .desc{"IP address"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                           .json_name{"query"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"ip"}
                        }
                    }
                }
            };

            __data_node<std::string> ip_type
            {
                .desc{"IP address type"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"type"}
                        }
                    }
                }
            };

            __data_node<std::string> continent
            {
                .desc{"Continent name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"continent"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"continent"}
                        }
                    }
                }
            };

            __data_node<std::string> continent_code
            {
                .desc{"Continent code"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"continentCode"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"continent_code"}
                        }
                    }
                }
            };

            __data_node<std::string> country
            {
                .desc{"Country name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"country"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country"}
                        }
                    }
                }
            };

            __data_node<std::string> country_code
            {
                .desc{"Country code"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"countryCode"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_code"}
                        }
                    }
                }
            };

            __data_node<std::string> country_capital
            {
                .desc{"The capital of country"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_capital"}
                        }
                    }
                }
            };

            __data_node<std::string> country_ph_code
            {
                .desc{"Country phone code"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_phone"}
                        }
                    }
                }
            };

            __data_node<std::string> country_neighbors
            {
                .desc{"Neighboring countries"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"country_neighbours"}
                        }
                    }
                }
            };

            __data_node<std::string> region
            {
                .desc{"Region name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"regionName"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"region"}
                        }
                    }
                }
            };

            __data_node<std::string> region_code
            {
                .desc{"Region code"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"region"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    }
                }
            };

           __data_node<std::string> city
            {
                .desc{"City name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"city"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"city"}
                        }
                    }
                }
            };

            __data_node<std::string> city_district
            {
                .desc{"City district"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"district"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    }
                }
            };

            __data_node<std::string> zip_code
            {
                .desc{"ZIP code"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"zip"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    },
                }
            };

            __data_node<double> latitude
            {
                .desc{"Latitude"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"lat"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"latitude"}
                        }
                    }
                }
            };

            __data_node<double> longitude
            {
                .desc{"Longitude"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"lon"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"longitude"}
                        }
                    }
                }
            };

            __data_node<std::string> city_timezone
            {
                .desc{"City timezone"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"timezone"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone"}
                        }
                    }
                }
            };

            __data_node<std::string> timezone
            {
                .desc{"Full timezone name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_name"}
                        }
                    }

                }
            };

            __data_node<std::int32_t> gmt_offset
            {
                .desc{"UTC offset"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"offset"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_gmtOffset"}
                        }
                    }
                }
            };

            __data_node<std::int32_t> dst_offset
            {
                .desc{"DST offset"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_dstOffset"}
                        }
                    }
                }
            };

            __data_node<std::string> timezone_gmt
            {
                .desc{"Timezone GMT"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"timezone_gmt"}
                        }
                    }
                }
            };

            __data_node<std::string> isp
            {
                .desc{"Internet Service Provider"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"isp"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"isp"}
                        }
                    }
                }
            };

            __data_node<std::string> as
            {
                .desc{"Autonomous system"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"as"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"as"}
                        }
                    }
                }
            };

            __data_node<std::string> org
            {
                .desc{"Organization name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"org"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"org"}
                        }
                    }
                }
            };

            __data_node<std::string> reverse_dns
            {
                .desc{"Reverse DNS of the IP"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"reverse"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    }

                }
            };

            __data_node<bool> is_hosting
            {
                .desc{"Hosting, colocated or data center"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"hosting"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    }

                }
            };

            __data_node<bool> is_proxy
            {
                .desc{"Proxy, VPN or Tor usage"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"proxy"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    }
                }
            };

            __data_node<bool> is_mobile
            {
                .desc{"Mobile connection usage"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"mobile"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{}
                        }
                    }

                }
            };

            __data_node<std::string> currency
            {
                .desc{"Currency name"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency"}
                        }
                    }
                }
            };

            __data_node<std::string> currency_code
            {
                .desc{"Currency code"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"currency"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_code"}
                        }
                    }
                }
            };

            __data_node<std::string> currency_symbol
            {
                .desc{"Currency symbol"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_symbol"}
                        }
                    }
                }
            };

            __data_node<double> currency_rates
            {
                .desc{"Currency exchange rate to USD"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_rates"}
                        }
                    }
                }
            };

            __data_node<std::string> currency_plural
            {
                .desc{"Currency plural"},
                .content
                {
                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                        {
                            .json_name{"currency_plural"}
                        }
                    },

                    {
                        avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                        {
                            .json_name{"currency_plural"}
                        }
                    }
                }
            };

        } __info_t;
    }
#endif
