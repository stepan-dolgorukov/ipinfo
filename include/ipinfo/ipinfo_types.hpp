#ifndef IPINFO_TYPES_HPP
    #define IPINFO_TYPES_HPP

#include "ipinfo_constants.hpp"
#include "ipinfo_aliases.hpp"

#include <map>     // std::map
#include <string>  // std::string
#include <cstdint> // std::uint8_t, std::int32_t

namespace ipinfo::usr::types{}
namespace ipinfo::srv::types{}

struct ipinfo::usr::types::error
{
    std::uint8_t code{ 0u };
    std::string  desc{};
};

template<typename T> struct ipinfo::usr::types::node
{
    bool        is_parsed : (1u) { false };
    T           val{};
    std::string host{};
    std::string desc{};
};

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
                bool              is_parsed : (1u) { false };
                T                 val{};
                const std::string json_name{};
            };

            const std::string                 desc{};
            std::map<const std::string, data> cont{};

        };

    public:
        node<std::string> ip
        {
            .desc{ "IP address" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "query" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "ip" }
                    }
                }
            }
        };

        node<std::string> ip_type
        {
            .desc{ "IP address type" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "type" }
                    }
                }
            }
        };

        node<std::string> continent
        {
            .desc{ "Continent name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "continent" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "continent" }
                    }
                }
            }
        };

        node<std::string> continent_code
        {
            .desc{ "Continent code" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "continentCode" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "continent_code" }
                    }
                }
            }
        };

        node<std::string> country
        {
            .desc{ "Country name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "country" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "country" }
                    }
                }
            }
        };

        node<std::string> country_code
        {
            .desc{ "Country code" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "countryCode" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "country_code" }
                    }
                }
            }
        };

        node<std::string> country_capital
        {
            .desc{ "The capital of country" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "country_capital" }
                    }
                }
            }
        };

        node<std::string> country_ph_code
        {
            .desc{ "Country phone code" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "country_phone" }
                    }
                }
            }
        };

        node<std::string> country_neighbors
        {
            .desc{ "Neighboring countries" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "country_neighbours" }
                    }
                }
            }
        };

        node<std::string> region
        {
            .desc{ "Region name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "regionName" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "region" }
                    }
                }
            }
        };

        node<std::string> region_code
        {
            .desc{ "Region code" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "region" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }
            }
        };

       node<std::string> city
        {
            .desc{ "City name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "city" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "city" }
                    }
                }
            }
        };

        node<std::string> city_district
        {
            .desc{ "City district" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "district" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }
            }
        };

        node<std::string> zip_code
        {
            .desc{ "ZIP code" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "zip" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                },
            }
        };

        node<double> latitude
        {
            .desc{ "Latitude" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "lat" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "latitude" }
                    }
                }
            }
        };

        node<double> longitude
        {
            .desc{ "Longitude" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "lon" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "longitude" }
                    }
                }
            }
        };

        node<std::string> city_timezone
        {
            .desc{ "City timezone" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "timezone" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "timezone" }
                    }
                }
            }
        };

        node<std::string> timezone
        {
            .desc{ "Full timezone name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "timezone_name" }
                    }
                }

            }
        };

        node<std::int32_t> gmt_offset
        {
            .desc{ "UTC offset" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "offset" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "timezone_gmtOffset" }
                    }
                }
            }
        };

        node<std::int32_t> dst_offset
        {
            .desc{ "DST offset" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "timezone_dstOffset" }
                    }
                }
            }
        };

        node<std::string> timezone_gmt
        {
            .desc{ "Timezone GMT" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "timezone_gmt" }
                    }
                }
            }
        };

        node<std::string> isp
        {
            .desc{ "Internet Service Provider" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "isp" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "isp" }
                    }
                }
            }
        };

        node<std::string> as
        {
            .desc{ "Autonomous system" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "as" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "as" }
                    }
                }
            }
        };

        node<std::string> org
        {
            .desc{ "Organization name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "org" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "org" }
                    }
                }
            }
        };

        node<std::string> reverse_dns
        {
            .desc{ "Reverse DNS of the IP" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "reverse" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }

            }
        };

        node<bool> is_hosting
        {
            .desc{ "Hosting, colocated or data center" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "hosting" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }

            }
        };

        node<bool> is_proxy
        {
            .desc{ "Proxy, VPN or Tor usage" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "proxy" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }
            }
        };

        node<bool> is_mobile
        {
            .desc{ "Mobile connection usage" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "mobile" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{}
                    }
                }

            }
        };

        node<std::string> currency
        {
            .desc{ "Currency name" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "currency" }
                    }
                }
            }
        };

        node<std::string> currency_code
        {
            .desc{ "Currency code" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "currency" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "currency_code" }
                    }
                }
            }
        };

        node<std::string> currency_symbol
        {
            .desc{ "Currency symbol" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "currency_symbol" }
                    }
                }
            }
        };

        node<double> currency_rates
        {
            .desc{ "Currency exchange rate to USD" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{}
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "currency_rates" }
                    }
                }
            }
        };

        node<std::string> currency_plural
        {
            .desc{ "Currency plural" },
            .cont
            {
                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IP_API_COM),
                    {
                        .json_name{ "currency_plural" }
                    }
                },

                {
                    constants::AVAILABLE_HOSTS.at(
                            constants::AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
                    {
                        .json_name{ "currency_plural" }
                    }
                }
            }
        };
};

#endif // IPINFO_TYPES_HPP
