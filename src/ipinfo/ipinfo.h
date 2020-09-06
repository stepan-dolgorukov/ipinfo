// 1. Project: ipinfo
// 2. Author: DolgorukovGTA
// 3. Repository: https://github.com/DolgorukovGTA/ipinfo


#pragma once
#include <string>

template <typename T>
struct node
{
    const std::string json_name;
    const std::string description;
    T value;
};

typedef struct ip_info
{
    struct node <bool> success
    {
        .json_name = "success",
        .description = "Request status"
    };

    struct node <std::string> err_msg
    {
        .json_name = "message",
        .description = "Error message"
    };
    
    struct node <std::string> ip 
    {
        .json_name = "ip",
        .description = "IP"
    };
    
    struct node <std::string> ip_type
    {
        .json_name = "type",
        .description = "IP type"
    };

    struct node <std::string> continent
    {
        .json_name = "continent",
        .description = "Continent"
    };
    
    struct node <std::string> continent_code
    {
        .json_name = "continent_code",
        .description = "Two-letter continent Code"
    };
    
    struct node <std::string> country
    {
        .json_name = "country",
        .description = "Country"
    };

    struct node <std::string> country_code
    {
        .json_name = "country_code",
        .description = "Two-letter country code"
    };
    
    struct node <std::string> country_capital
    {
        .json_name = "country_capital",
        .description = "The capital of country"
    };
    
    struct node <std::string> country_phone
    {
        .json_name = "country_phone",
        .description = "Country phone code"
    };
    
    struct node <std::string> county_neighbors
    {
        .json_name = "country_neighbours",
        .description = "Neighboring countries"
    };

    struct node <std::string> region
    {
        .json_name = "region",
        .description = "Region/state"
    };
    
    struct node <std::string> city
    {
        .json_name = "city",
        .description = "City"
    };

    struct node <double> lat
    {
        .json_name = "latitude",
        .description = "Latitude"
    };
    
    struct node <double> lon
    {
        .json_name = "longitude",
        .description = "Longitude"
    };

    struct node <std::string> asn
    {
        .json_name = "asn",
        .description = "AS number"
    };
    
    struct node <std::string> org
    {
        .json_name = "org",
        .description = "Organization name"
    };
    
    struct node <std::string> isp
    {
        .json_name = "isp",
        .description = "ISP name"
    };

    struct node <std::string> city_timezone
    {
        .json_name = "timezone",
        .description = "City timezone"
    };
    
    struct node <std::string> timezone_name
    {
        .json_name = "timezone_name",
        .description = "Full timezone name"
    };
    
    struct node <std::int32_t> tz_dst_offset
    {
        .json_name = "timezone_dstOffset",
        .description = "Daylight-savings time offset (sec)"
    };
    
    struct node <std::int32_t> tz_gmt_offset
    {
        .json_name = "timezone_gmtOffset",
        .description = "Location UTC offset (sec)"
    };
    
    struct node <std::string> timezone_gmt
    {
        .json_name = "timezone_gmt",
        .description = "Timezone GMT"
    };

    struct node <std::string> currency
    {
        .json_name = "currency",
        .description = "Currency name"
    };
    
    struct node <std::string> currency_code
    {
        .json_name = "currency_code",
        .description = "Currency code"
    };
    
    struct node <std::string> currency_symbol
    {
        .json_name = "currency_symbol",
        .description = "Currency symbol"
    };
    
    struct node <double> currency_rates
    {
        .json_name = "currency_rates",
        .description = "Currency exchange rate to US dollar"
    };
    
    struct node <std::string> currency_plural
    {
        .json_name = "currency_plural",
        .description = "Currency plural"
    };

} ip_info_t;


std::uint8_t    get_ip_info(ip_info_t * const ip_info,
                            const std::string * const ip);

void            print_ip_info(const ip_info_t * const ip_info);