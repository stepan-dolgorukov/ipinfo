#ifndef IPINFO_TYPES_HPP
    #define IPINFO_TYPES_HPP

#include "ipinfo_constants.hpp"

#include <map>     // std::map
#include <string>  // std::string
#include <cstdint> // std::uint8_t, std::int32_t

namespace ipinfo::usr::types
{
    struct error;
    template <typename T> struct node;
}

namespace ipinfo::srv::types
{
    struct req_attrs;
    struct info;
}

struct ipinfo::usr::types::error
{
    std::uint8_t code{};
    std::string  desc{};
};

// node structure for user
template<typename T> struct ipinfo::usr::types::node
{
    bool        is_parsed : 1 {false};
    T           val{};
    std::string host{};
    std::string desc{};
};


// add this structure usage to the code
struct ipinfo::srv::types::req_attrs
{
    const std::string host{};
    const std::string ip{};
    const std::string lang{};
    const std::string api_key{};
};

struct ipinfo::srv::types::info
{
    private:
        template<typename T> struct node
        {
            struct data
            {
                bool              is_parsed : 1 {false};
                T                 val{};
                const std::string json_name{};
            };

            const std::string                 desc{};
            std::map<const std::string, data> cont{};

        };

    public:
        node<std::string> ip
        {
            .desc{"IP address"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM), 
                    {
                        .json_name{"query"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"ip"}
                    }
                }
            }
        };

        node<std::string> ip_type
        {
            .desc{"IP address type"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"type"}
                    }
                }
            }
        };

        node<std::string> continent
        {
            .desc{"Continent name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"continent"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"continent"}
                    }
                }
            }
        };

        node<std::string> continent_code
        {
            .desc{"Continent code"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"continentCode"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"continent_code"}
                    }
                }
            }
        };

        node<std::string> country
        {
            .desc{"Country name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"country"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"country"}
                    }
                }
            }
        };

        node<std::string> country_code
        {
            .desc{"Country code"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"countryCode"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"country_code"}
                    }
                }
            }
        };

        node<std::string> country_capital
        {
            .desc{"The capital of country"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"country_capital"}
                    }
                }
            }
        };

        node<std::string> country_ph_code
        {
            .desc{"Country phone code"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"country_phone"}
                    }
                }
            }
        };

        node<std::string> country_neighbors
        {
            .desc{"Neighboring countries"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"country_neighbours"}
                    }
                }
            }
        };

        node<std::string> region
        {
            .desc{"Region name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"regionName"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"region"}
                    }
                }
            }
        };

        node<std::string> region_code
        {
            .desc{"Region code"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"region"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }
            }
        };

       node<std::string> city
        {
            .desc{"City name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"city"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"city"}
                    }
                }
            }
        };

        node<std::string> city_district
        {
            .desc{"City district"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"district"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }
            }
        };

        node<std::string> zip_code
        {
            .desc{"ZIP code"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"zip"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                },
            }
        };

        node<double> latitude
        {
            .desc{"Latitude"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"lat"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"latitude"}
                    }
                }
            }
        };

        node<double> longitude
        {
            .desc{"Longitude"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"lon"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"longitude"}
                    }
                }
            }
        };

        node<std::string> city_timezone
        {
            .desc{"City timezone"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"timezone"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"timezone"}
                    }
                }
            }
        };

        node<std::string> timezone
        {
            .desc{"Full timezone name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"timezone_name"}
                    }
                }

            }
        };

        node<std::int32_t> gmt_offset
        {
            .desc{"UTC offset"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"offset"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"timezone_gmtOffset"}
                    }
                }
            }
        };

        node<std::int32_t> dst_offset
        {
            .desc{"DST offset"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"timezone_dstOffset"}
                    }
                }
            }
        };

        node<std::string> timezone_gmt
        {
            .desc{"Timezone GMT"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"timezone_gmt"}
                    }
                }
            }
        };

        node<std::string> isp
        {
            .desc{"Internet Service Provider"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"isp"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"isp"}
                    }
                }
            }
        };

        node<std::string> as
        {
            .desc{"Autonomous system"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"as"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"as"}
                    }
                }
            }
        };

        node<std::string> org
        {
            .desc{"Organization name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"org"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"org"}
                    }
                }
            }
        };

        node<std::string> reverse_dns
        {
            .desc{"Reverse DNS of the IP"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"reverse"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }

            }
        };

        node<bool> is_hosting
        {
            .desc{"Hosting, colocated or data center"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"hosting"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }

            }
        };

        node<bool> is_proxy
        {
            .desc{"Proxy, VPN or Tor usage"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"proxy"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }
            }
        };

        node<bool> is_mobile
        {
            .desc{"Mobile connection usage"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"mobile"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }

            }
        };

        node<std::string> currency
        {
            .desc{"Currency name"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"currency"}
                    }
                }
            }
        };

        node<std::string> currency_code
        {
            .desc{"Currency code"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"currency"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"currency_code"}
                    }
                }
            }
        };

        node<std::string> currency_symbol
        {
            .desc{"Currency symbol"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"currency_symbol"}
                    }
                }
            }
        };

        node<double> currency_rates
        {
            .desc{"Currency exchange rate to USD"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"currency_rates"}
                    }
                }
            }
        };

        node<std::string> currency_plural
        {
            .desc{"Currency plural"},
            .cont
            {
                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{"currency_plural"}
                    }
                },

                {
                    ipinfo::constants::AVAILABLE_HOSTS.at(
                            ipinfo::constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{"currency_plural"}
                    }
                }
            }
        };
};

#endif
