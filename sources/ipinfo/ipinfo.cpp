// 1. Project: ipinfo
// 2. Author: DolgorukovGTA
// 3. Repository: https://github.com/DolgorukovGTA/ipinfo

// Add -DDEBUG_MODE to the compiler flags to turn 
// ON the debug mode, or just add #define DEBUG_MODE.

#include <iostream>
#include <typeinfo>

#include "ipinfo.h"
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

#ifdef DEBUG_MODE
#include "spdlog/spdlog.h"
#endif


static std::size_t receive_data(const char * const str,
                                const std::size_t length,
                                const std::size_t nmemb,
                                std::string * const data)
{
    if (nullptr != data &&
        nullptr != str)
    {
        const std::size_t size{length * nmemb};
        data->append(str, size);
        
        return size;
    }
    
    return 0u; // Error.
}


static std::pair<std::uint8_t,
                 std::string> get_data(const std::string * const ip)
{
    CURL *curl{nullptr};
    std::string res_data{};
    std::string url{"http://ipwhois.app/json/"};

    if (nullptr != ip &&
        0u != ip->length())
    {
        url.append(ip->c_str());
    }
    
    curl = curl_easy_init();

    if (nullptr == curl)
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Starting libcurl session "
                      "failed.", __FILE__, __LINE__, __FUNCTION__);
        #endif

        return std::make_pair(1u, std::string{});
    }

    #ifdef DEBUG_MODE
    spdlog::info("[{} | {} | {}] Session of libcurl started "
                 "successfully.", __FILE__, __LINE__, __FUNCTION__);
    #endif

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_data);
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP);
    curl_easy_setopt(curl, CURLOPT_PORT, 80);

    if (CURLE_OK != curl_easy_perform(curl))
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Couldn't send the data to {}.",
                      __FILE__, __LINE__, __FUNCTION__, url);

        #endif
        return std::make_pair(1u, std::string{0});
    }

    #ifdef DEBUG_MODE
    spdlog::info("[{} | {} | {}] Successfully data sending to {}.",
                 __FILE__, __LINE__, __FUNCTION__, url);
    #endif

    curl_easy_cleanup(curl);
    
    return std::make_pair(0u, res_data);
}


template<typename T>
static std::uint8_t parse_node(const cJSON * const data,
                               node<T> * const node)
{
    if (nullptr == data ||
        0u == node->json_name.length())
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Unacceptable function parameters.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
        return EXIT_FAILURE;
    }

    if (0u == node->description.length())
    {
        #ifdef DEBUG_MODE
        spdlog::warn("[{} | {} | {}] Description on the node is empty.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
    }

    const cJSON *item{nullptr};
    const char *item_name{nullptr};
    const std::type_info &node_type{typeid(T)};
    
    item_name = node->json_name.c_str();
    item = cJSON_GetObjectItemCaseSensitive(data, item_name);

    if (nullptr == item)
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Couldn't find the node with "
                      "the name <{}> ({}) in the JSON object.",
                      __FILE__, __LINE__, __FUNCTION__,
                      node->json_name, node->description);
        #endif
        return EXIT_FAILURE;
    }

    if (node_type.hash_code() == typeid(bool).hash_code())
    {
        if (!cJSON_IsBool(item))
        {
            #ifdef DEBUG_MODE
            spdlog::error("[{} | {} | {}] Couldn't correctly "
                          "parse the <{}> ({}) JSON node.",
                          __FILE__, __LINE__, __FUNCTION__,
                          node->json_name, node->description);
            #endif
            return EXIT_FAILURE;
        }

        node->value = item->valueint;
    }

    // Numeric types are implemented as
    // a strings in our JSON object.

    if (node_type.hash_code() == typeid(std::int32_t).hash_code() ||
        node_type.hash_code() == typeid(double).hash_code())
    {
        const char * const &s = item->valuestring;

        if (!cJSON_IsString(item) ||
            nullptr == s ||
            0u == std::string(s).length())
        {
            #ifdef DEBUG_MODE
            spdlog::error("[{} | {} | {}] Couldn't correctly "
                          "parse the <{}> ({}) JSON node.",
                          __FILE__, __LINE__, __FUNCTION__,
                          node->json_name, node->description);
            #endif
            return EXIT_FAILURE;
        }

        if (node_type.hash_code() == typeid(std::int32_t).hash_code())
        {
            node->value = std::stoi(s);
        }
        
        else
        {
            node->value = std::stod(s);
        }
    }

    #ifdef DEBUG_MODE
    spdlog::info("[{} | {} | {}] Node <{}> ({}) has "
                 "been parsed successfully.",
                  __FILE__, __LINE__, __FUNCTION__,
                  node->json_name, node->description);
    #endif
    return EXIT_SUCCESS;
}


template<>
std::uint8_t parse_node(const cJSON * const data,
                        node<std::string> * const node)
{    
    if (nullptr == data ||
        0u == node->json_name.length())
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Unacceptable function parameters.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
        return EXIT_FAILURE;
    }

    if (0u == node->description.length())
    {
        #ifdef DEBUG_MODE
        spdlog::warn("[{} | {} | {}] Description on the node is empty.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
    }

    const cJSON *item{nullptr};
    const char *item_name{nullptr};

    item_name = node->json_name.c_str();
    item = cJSON_GetObjectItemCaseSensitive(data, item_name);

    if (nullptr == item)
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Couldn't find the "
                      "node with the name \"{}\" in the JSON.",
                      __FILE__, __LINE__, __FUNCTION__,
                      node->json_name);
        #endif
        return EXIT_FAILURE;
    }

    if (!cJSON_IsString(item) ||
        nullptr == item->valuestring ||
        0u == std::string(item->valuestring).length())
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Couldn't correctly "
                      "parse the \"{}\" JSON node.",
                      __FILE__, __LINE__, __func__,
                      node->json_name);
        #endif
        return EXIT_FAILURE;
    }

    #ifdef DEBUG_MODE
    spdlog::info("[{} | {} | {}] Node \"{}\" ({}) has "
                 "been parsed successfully.",
                 __FILE__, __LINE__, __func__,
                 node->json_name, node->description);
    #endif

    node->value = item->valuestring;
    return EXIT_SUCCESS;
}


static std::uint8_t parse_data(const std::string * const json,
                               ip_info_t * const ip_info)
{
    if (nullptr == json ||
        nullptr == ip_info ||
        0u == json->length())
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Invalid function parameters.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
        return EXIT_FAILURE;
    }

    cJSON *data{nullptr};
    data = cJSON_Parse(json->c_str());

    if (nullptr == data)
    {
        #ifdef DEBUG_MODE
        const char* const error = cJSON_GetErrorPtr();
        
        spdlog::error("[{} | {} | {}] Couldn't parse the JSON "
                      "object.", __FILE__, __LINE__, __FUNCTION__);

        
        if (nullptr != error)
        {
            spdlog::debug("[{} | {} | {}] JSON parsing error near \"{}\".",
                          __FILE__, __LINE__, __FUNCTION__, error);
        }

        else
        {
            spdlog::error("[{} | {} | {}] Couldn't get the error "
                          "details of the JSON object parsing.",
                         __FILE__, __LINE__, __FUNCTION__);
        }
        #endif
        return EXIT_FAILURE;
    }

    if (0u != parse_node<bool>(data, &ip_info->success) ||
        !ip_info->success.value)
    {
        #ifdef DEBUG_MODE
        if (0u == parse_node<std::string>(data, &ip_info->err_msg))
        {
            spdlog::debug("[{} | {} | {}] Server error message (from the "
                          "JSON): \"{}\".", __FILE__, __LINE__, __FUNCTION__,
                          ip_info->err_msg.value);
        }

        else
        {
            spdlog::error("[{} | {} | {}] Couldn't get from the "
                          "JSON object the server error message.",
                          __FILE__, __LINE__, __FUNCTION__);
        }
        #endif

        return EXIT_FAILURE;
    }
    
    parse_node<std::string>(data, &ip_info->ip);
    parse_node<std::string>(data, &ip_info->ip_type);
    
    parse_node<std::string>(data, &ip_info->continent);
    parse_node<std::string>(data, &ip_info->continent_code);
    
    parse_node<std::string>(data, &ip_info->country);
    parse_node<std::string>(data, &ip_info->country_code);
    parse_node<std::string>(data, &ip_info->country_capital);
    parse_node<std::string>(data, &ip_info->country_phone);
    parse_node<std::string>(data, &ip_info->county_neighbors);

    parse_node<std::string>(data, &ip_info->region);
    parse_node<std::string>(data, &ip_info->city);

    parse_node<double>(data, &ip_info->lat);
    parse_node<double>(data, &ip_info->lon);
    
    parse_node<std::string>(data, &ip_info->asn);
    parse_node<std::string>(data, &ip_info->org);
    parse_node<std::string>(data, &ip_info->isp);

    parse_node<std::string>(data, &ip_info->city_timezone);
    parse_node<std::string>(data, &ip_info->timezone_name);
    parse_node<std::int32_t>(data, &ip_info->tz_dst_offset);
    parse_node<std::int32_t>(data, &ip_info->tz_gmt_offset);
    parse_node<std::string>(data, &ip_info->timezone_gmt);

    parse_node<std::string>(data, &ip_info->currency);
    parse_node<std::string>(data, &ip_info->currency_code);
    parse_node<std::string>(data, &ip_info->currency_symbol);
    parse_node<double>(data, &ip_info->currency_rates);
    parse_node<std::string>(data, &ip_info->currency_plural);

    return EXIT_SUCCESS;
}


std::uint8_t get_ip_info(ip_info_t * const ip_info,
                         const std::string * const ip)
{
    #ifdef DEBUG_MODE
    spdlog::set_level(spdlog::level::debug);
    #endif

    const std::pair<std::uint8_t, std::string> r_pair = get_data(ip);
    
    const std::uint8_t &status = r_pair.first;
    const std::string &json = r_pair.second;

    if (0u != status ||
        0u == json.length())
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Couldn't get "
                      "an answer from the server.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
        return EXIT_FAILURE;
    }
    
    #ifdef DEBUG_MODE
    spdlog::debug("[{} | {} | {}] Received JSON object: \"{}\".",
                  __FILE__, __LINE__, __FUNCTION__, json);
    #endif

    return parse_data(&json, ip_info);
}


void print_ip_info(const ip_info_t * const ip_info)
{
    if (nullptr == ip_info)
    {
        #ifdef DEBUG_MODE
        spdlog::error("[{} | {} | {}] Invalid pointer to "
                      "the IP information structure.",
                      __FILE__, __LINE__, __FUNCTION__);
        #endif
    }

    std::cout << ip_info->ip.description << ": "
              << ip_info->ip.value << std::endl;

    std::cout << ip_info->ip_type.description << ": "
              << ip_info->ip_type.value << std::endl;

    std::cout << ip_info->continent.description << ": "
              << ip_info->continent.value << std::endl;

    std::cout << ip_info->continent_code.description << ": "
              << ip_info->continent_code.value << std::endl;
    
    std::cout << ip_info->country.description << ": "
              << ip_info->country.value << std::endl;

    std::cout << ip_info->country_code.description << ": "
              << ip_info->country_code.value << std::endl;

    std::cout << ip_info->country_capital.description << ": "
              << ip_info->country_capital.value << std::endl;

    std::cout << ip_info->country_phone.description << ": "
              << ip_info->country_phone.value << std::endl;

    std::cout << ip_info->county_neighbors.description << ": "
              << ip_info->county_neighbors.value << std::endl;

    std::cout << ip_info->region.description << ": "
              << ip_info->region.value << std::endl;

    std::cout << ip_info->city.description << ": "
              << ip_info->city.value << std::endl;
    
    std::cout << ip_info->lat.description << ": "
             << ip_info->lat.value << std::endl;

    std::cout << ip_info->lon.description << ": "
              << ip_info->lon.value << std::endl;

    std::cout << ip_info->asn.description << ": "
              << ip_info->asn.value << std::endl;
    
    std::cout << ip_info->org.description << ": "
              << ip_info->org.value << std::endl;

    std::cout << ip_info->isp.description << ": "
              << ip_info->isp.value << std::endl;

    std::cout << ip_info->city_timezone.description << ": "
              << ip_info->city_timezone.value << std::endl;

    std::cout << ip_info->timezone_name.description << ": "
              << ip_info->timezone_name.value << std::endl;

    std::cout << ip_info->tz_dst_offset.description << ": "
              << ip_info->tz_dst_offset.value << std::endl;

    std::cout << ip_info->tz_gmt_offset.description << ": "
              << ip_info->tz_gmt_offset.value << std::endl;

    std::cout << ip_info->timezone_gmt.description << ": "
              << ip_info->timezone_gmt.value << std::endl;

    std::cout << ip_info->currency.description << ": "
              << ip_info->currency.value << std::endl;
    
    std::cout << ip_info->currency_code.description << ": "
              << ip_info->currency_code.value << std::endl;

    std::cout << ip_info->currency_symbol.description << ": "
              << ip_info->currency_symbol.value << std::endl;

    std::cout << ip_info->currency_rates.description << ": "
              << ip_info->currency_rates.value << std::endl;

    std::cout << ip_info->currency_plural.description << ": "
              << ip_info->currency_plural.value << std::endl;

    return;
}