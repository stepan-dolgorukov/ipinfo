#ifndef IPINFO_CONSTANTS_HPP
    #define IPINFO_CONSTANTS_HPP

#include "ipinfo_aliases.hpp"

#include <map>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace ipinfo::constants
{
    const std::array<std::string, 2u> AVAILABLE_HOSTS
    {
        "ip-api.com",
        "ipwhois.app"
    };

    const std::array<std::string, 8u> AVAILABLE_LANGS
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

    enum AVAILABLE_HOSTS_IDS : std::uint8_t
    {
        IP_API_COM = 0u,
        IPWHOIS_APP
    };

    enum AVAILABLE_LANGS_IDS : std::uint8_t
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

    enum ERRORS_IDS : std::uint8_t
    {
        NO_ERRORS = 0u,
        UNSUPPORTED_HOST,
        EXCLUDED_HOST,
        EMPTY_HOST,
        UNSUCCESSFULL_RESPONSE_STATUS_CODE,
        EMPTY_REQUEST_ANSWER,
        EMPTY_JSON_STRING,
        FAILED_JSON_PARSING
    };

    const std::map<als::str, std::map<als::str, als::str>> HOSTS_AVAILABLE_LANGS
    {
        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IP_API_COM),
            {
                {
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::ENGLISH),    "en"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::GERMAN),     "de"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::SPANISH),    "es"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::PORTUGUESE), "pt-BR" },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::FRENCH),     "fr"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::JAPANESE),   "ja"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::CHINESE),    "zh-CN" },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::RUSSIAN),    "ru"    }
                }
            }
        },

        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
            {
                {
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::ENGLISH),    "en"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::GERMAN),     "de"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::SPANISH),    "es"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::PORTUGUESE), "pt-BR" },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::FRENCH),     "fr"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::JAPANESE),   "ja"    },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::CHINESE),    "zh-CN" },
                    { AVAILABLE_LANGS.at(AVAILABLE_LANGS_IDS::RUSSIAN),    "ru"    }
                }
            }
        }
    };

    const std::map<std::string, std::string> REQUEST_START_PATHS
    {
        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IP_API_COM),
            {
                "http://" +
                AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IP_API_COM) +
                "/json/"
            }
        },

        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
            {
                "http://" +
                AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IPWHOIS_APP) +
                "/json/"
            }
        }
    };

    const std::map<als::str, std::map<als::str, als::str>> REQUEST_PARAMETERS_TITLES
    {
        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IP_API_COM),
            {
                { "fields",  "fields" },
                { "lang",    "lang" },
                { "api_key", "key" }
            }
        },

        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
            {
                { "fields",  "objects" },
                { "lang",    "lang" },
                { "api_key", "key" }
            }
        }
    };

    const std::map<std::string, std::vector<std::string>> REQUEST_INFO_FIELDS
    {
        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IP_API_COM),
            {
                "query",
                "continent",
                "gcontinentCode",
                "country",
                "countryCode",
                "region",
                "regionName",
                "city",
                "district",
                "zip",
                "lat",
                "lon",
                "timezone",
                "offset",
                "currency",
                "isp",
                "org",
                "as",
                "asname",
                "reverse",
                "mobile",
                "proxy",
                "hosting"
            }
        },

        {
            AVAILABLE_HOSTS.at(AVAILABLE_HOSTS_IDS::IPWHOIS_APP),
            {
                "ip",
                "type",
                "continent",
                "continent_code",
                "country",
                "country_code",
                "country_capital",
                "country_phone",
                "country_neighbours",
                "region",
                "city",
                "latitude",
                "longitude",
                "as",
                "org",
                "isp",
                "timezone",
                "timezone_name",
                "timezone_dstOffset",
                "timezone_gmtOffset",
                "timezone_gmt",
                "currency",
                "currency_code",
                "currency_symbol",
                "currency_rates",
                "currency_plural"
            }
        }
    };
}

#endif // IPINFO_CONSTANTS_HPP
