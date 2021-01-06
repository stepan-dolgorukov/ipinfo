#ifndef __IPINFO__VALUES__HPP__
    #define __IPINFO__VALUES__HPP__

    #include <map>
    #include <array>
    #include <string>
    #include <vector>
    #include <cstdint>

    namespace ipinfo
    {
        static const
        std::array<std::string, 2u> avail_hosts
        {
            "ip-api.com",
            "ipwhois.app"
        };

        static const
        std::array<std::string, 8u> avail_langs
        {
            "english",
            "german",
            "spanish",
            "portuguese",
            "french",
            "japanese",
            "chinese",
            "russian"
        };

        enum AVAIL_HOSTS_IDS : std::uint8_t
        {
            IP_API_COM = 0u,
            IPWHOIS_APP
        };

        enum AVAIL_LANGS_IDS : std::uint8_t
        {
            ENGLISH = 0u,
            GERMAN,
            SPANISH,
            PORTUGUESE,
            FRENCH,
            JAPANESE,
            CHINESE,
            RUSSIAN
        };

        enum ERRORS_IDS
        {
            NO_ERRORS = 0u,
            UNSUPPORTED_HOST,
            EXCLUDED_HOST,
            EMPTY_HOST,
            FAILED_START_LIBCURL_SESSION,
            FAILED_REQUEST_SENDING,
            EMPTY_REQUEST_ANSWER,
            EMPTY_JSON_STRING,
            FAILED_JSON_PARSING
        };

        static const
        std::map<std::string,
                 std::map<std::string,
                          std::string>> hosts_avail_langs_codes
        {
            {
                avail_hosts.at(ipinfo::AVAIL_HOSTS_IDS::IP_API_COM),
                {
                    {
                        {avail_langs.at(AVAIL_LANGS_IDS::ENGLISH),    "en"},
                        {avail_langs.at(AVAIL_LANGS_IDS::GERMAN),     "de"},
                        {avail_langs.at(AVAIL_LANGS_IDS::SPANISH),    "es"},
                        {avail_langs.at(AVAIL_LANGS_IDS::PORTUGUESE), "pt-BR"},
                        {avail_langs.at(AVAIL_LANGS_IDS::FRENCH),     "fr"},
                        {avail_langs.at(AVAIL_LANGS_IDS::JAPANESE),   "ja"},
                        {avail_langs.at(AVAIL_LANGS_IDS::CHINESE),    "zh-CN"},
                        {avail_langs.at(AVAIL_LANGS_IDS::RUSSIAN),    "ru"}
                    }
                }
            },

            {
                avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                {
                    {
                        {avail_langs.at(AVAIL_LANGS_IDS::ENGLISH),    "en"},
                        {avail_langs.at(AVAIL_LANGS_IDS::GERMAN),     "de"},
                        {avail_langs.at(AVAIL_LANGS_IDS::SPANISH),    "es"},
                        {avail_langs.at(AVAIL_LANGS_IDS::PORTUGUESE), "pt-BR"},
                        {avail_langs.at(AVAIL_LANGS_IDS::FRENCH),     "fr"},
                        {avail_langs.at(AVAIL_LANGS_IDS::JAPANESE),   "ja"},
                        {avail_langs.at(AVAIL_LANGS_IDS::CHINESE),    "zh-CN"},
                        {avail_langs.at(AVAIL_LANGS_IDS::RUSSIAN),    "ru"}
                     }
                }
            }
        };

        static const
        std::map<std::string, std::string> req_start_paths
        {
            {
                avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                {
                    "http://" +
                    avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM) +
                    "/json/"
                }
            },

            {
                avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                {
                    "http://" +
                    avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP) +
                    "/json/"
                }
            }
        };

        static const
        std::map<std::string,
                 std::map<std::string,
                          std::string>> req_param_titles
        {
            {
                avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                {
                    {"fields",  "fields"},
                    {"lang",    "lang"},
                    {"api_key", "key"} // not exactly correct
                }
            },

            {
                avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                {
                    {"fields",  "objects"},
                    {"lang",    "lang"},
                    {"api_key", "key"} // not exactly correct
                }
            }
        };

        static const
        std::map<std::string,
                 std::vector<std::string>> req_info_fields
        {
            {
                avail_hosts.at(AVAIL_HOSTS_IDS::IP_API_COM),
                {
                    {"query"},
                    {"continent"},
                    {"gcontinentCode"},
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
                avail_hosts.at(AVAIL_HOSTS_IDS::IPWHOIS_APP),
                {
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
                    {"currency_plural"}
                }
            }
        };
    }

#endif
