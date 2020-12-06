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
            // Request status
            // Can be only true or false
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

            // Request error message
            // It'll be filled if the request status isn't success
            ipinfo::__data_node<std::string> err_msg
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

            // IP address
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

            // Type of the IP address
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

            // Continent name
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

            // Continent code
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

            // Country name
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

            // Country code
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

            // Country capital
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

            // Country phone code
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

            // Country neighbors
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

            // Region name
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

            // Region code
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

            // City name
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

            // City district (subdivision)
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

            // ZIP code
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

            // Latitude
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

            // Longitude
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

            // City timezone
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

            // Full timezone name
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

            // UTC offset in seconds
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

            // DST (daylight savings time) offset in seconds
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

            // Timezone GMT
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

            // ISP (Internet Service Provider)
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

            // AS (Autonomous System)
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

            // Organization name
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

            // Reverse DNS IP lookup
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

            // Hosting, colocated or data center
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

            // Proxy, VPN, Tor usage
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

            // Mobile connection usage
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

            // National currency name
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

            // Currency code
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

            // Currency symbol
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

            // Current exchange rate against the US dollar
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

            // Currency plural
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
