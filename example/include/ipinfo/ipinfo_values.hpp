#ifndef __IPINFO__VALUES__HPP__
    #define __IPINFO__VALUES__HPP__


    #include <string>
    #include <array>
    #include <vector>
    #include <map>


    namespace ipinfo
    {
        const std::array<const std::string, 2u> avail_hosts
        {
            "ip-api.com",
            "ipwhois.app"
        };

        
        const std::map<const std::string,
                       const std::map<const std::string,
                                      const std::string>> avail_langs
        {
            {
                ipinfo::avail_hosts.at(0u),
                {
                    {
                        {"English", "en"},
                        {"German", "de"},
                        {"Spanish", "es"},
                        {"Portuguese", "pt-BR"},
                        {"French", "fr"},
                        {"Japanese", "ja"},
                        {"Chinese", "zh-CN"},
                        {"Russian", "ru"}
                    }
                }
            },

            {
                ipinfo::avail_hosts.at(1u),
                {
                    {
                        {"English", "en"},
                        {"German", "de"},
                        {"Spanish", "es"},
                        {"Portuguese", "pt-BR"},
                        {"French", "fr"},
                        {"Japanese", "ja"},
                        {"Chinese", "zh-CN"},
                        {"Russian", "ru"}
                    }
                }
            }
        };

        const std::map<const std::string,
                       const std::string> req_paths
        {
            {
                ipinfo::avail_hosts.at(0u),
                ("http://" + avail_hosts.at(0u) + "/json/"),
            },

            {
                ipinfo::avail_hosts.at(1u),
                ("http://" + avail_hosts.at(1u) + "/json/")
            }
        };

        const std::map<const std::string,
                       const std::map<const std::string,
                                      const std::string>> req_prefixes
        {
            {
                ipinfo::avail_hosts.at(0u),
                {
                    {"lang", "&lang="},
                    {"fields", "?fields="}
                }
            },

            {
                ipinfo::avail_hosts.at(1u),
                {
                    {"lang", "&lang="},
                    {"fields", "?objects="}
                }
            }
        };


        const std::map<const std::string,
                       const std::vector<std::string>> req_params
        {
            {
                ipinfo::avail_hosts.at(0u),
                {
                    {"status"},
                    {"message"},
                    {"query"},
                    {"continent"},
                    {"continentCode"},
                    {"country"},
                    {"countryCode"},
                    {"region"},
                    {"regionName"},
                    {"city"},
                    {"district"},
                    {"zip"},
                    {"lat"},
                    {"lon"},
                    {"timezone"},
                    {"offset"},
                    {"currency"},
                    {"isp"},
                    {"org"},
                    {"as"},
                    {"asname"},
                    {"reverse"},
                    {"mobile"},
                    {"proxy"},
                    {"hosting"}
                }
            },

            {
                ipinfo::avail_hosts.at(1u),
                {
                    {"success"},
                    {"message"},
                    {"ip"},
                    {"type"},
                    {"continent"},
                    {"continent_code"},
                    {"country"},
                    {"country_code"},
                    {"country_capital"},
                    {"country_phone"},
                    {"country_neighbours"},
                    {"region"},
                    {"city"},
                    {"latitude"},
                    {"longitude"},
                    {"as"},
                    {"org"},
                    {"isp"},
                    {"timezone"},
                    {"timezone_name"},
                    {"timezone_dstOffset"},
                    {"timezone_gmtOffset"},
                    {"timezone_gmt"},
                    {"currency"},
                    {"currency_code"},
                    {"currency_symbol"},
                    {"currency_rates"},
                    {"currency_plural"},
                }
            }
        };
    }

#endif