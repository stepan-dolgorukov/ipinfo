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
            std::uint8_t    code{0u};
            std::string     desc{"No error"};

            std::string     part{};
            std::string     func{};
        } __error_t;

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

            ipinfo::__data_node<std::string> ip_type
            {
                .desc{"IP address type"},

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

            ipinfo::__data_node<std::string> country_ph_code
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

            ipinfo::__data_node<std::string> org
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

            ipinfo::__data_node<std::string> currency
            {
                .desc{"Currency name"},

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

            ipinfo::__data_node<std::string> currency_plural
            {
                .desc{"Currency plural"},
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
