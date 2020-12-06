#include <bits/c++config.h>
#include <string>
#include <cstddef>
#include <functional>

#include "../include/curl/curl.h"
#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_values.hpp"

namespace ipinfo
{
    static std::size_t
    recv(const char * const data,
         std::size_t ch_size,
         std::size_t ch_nums,
         std::string * const res);

    static std::string
    get_ready_request_info_fields(const std::string &host);

    static std::string
    get_ready_request_lang(const std::string &host,
                           const std::string &lang);
}


std::size_t ipinfo::recv(const char * const data,
                         std::size_t ch_size,
                         std::size_t ch_nums,
                         std::string * const res)
{
    const auto total_bytes{ch_size * ch_nums};
    res->append(data, total_bytes);
    return total_bytes;
}


std::string
ipinfo::get_ready_request_info_fields(const std::string &host)
{
    std::string res{};
    const auto &fields{ipinfo::req_info_fields.at(host)};
    const auto max_idx{fields.size() - 1u};

    for (auto i{0u}; max_idx >= i; i++)
    {
        res.append(fields.at(i));

        if (max_idx != i)
        {
            res.append(",");
        }
    }

    return res;
}


std::string
ipinfo::get_ready_request_lang(const std::string &host,
                               const std::string &lang)
{
    std::string res{};
    const auto &avail_langs{ipinfo::avail_langs.at(host)};

    for (const auto &value_pair : avail_langs)
    {
        if (lang == value_pair.first)
        {
            res = avail_langs.at(lang);
            break;
        }
    }

    return res;
}


std::string
ipinfo::__requester::get_full_url(const std::string &host,
                                  const std::string &ip,
                                  const std::string &lang)
{
    std::string url{};

    url += ipinfo::req_start_paths.at(host);
    url += ip;

    url += "?" + ipinfo::req_param_titles.at(host).at("fields");
    url += "=";
    url += ipinfo::get_ready_request_info_fields(host);

    url += "&";
    url += ipinfo::req_param_titles.at(host).at("lang");
    url += "=";
    url += ipinfo::get_ready_request_lang(host, lang);

    return url;
}


std::string
ipinfo::__requester::make_request(const std::string &url)
{;
    std::string req_answ{};
    ::CURLcode status_code{};
    ::CURL * const session{curl_easy_init()};

    if (!session)
    {
        // log!
        return {};
    }

    ::curl_easy_setopt(session, ::CURLOPT_URL, url.c_str());
    ::curl_easy_setopt(session, ::CURLOPT_WRITEDATA, &req_answ);
    ::curl_easy_setopt(session, ::CURLOPT_USERAGENT, "ipinfo module");
    ::curl_easy_setopt(session, ::CURLOPT_WRITEFUNCTION, &recv);

    status_code = ::curl_easy_perform(session);

    if (CURLcode::CURLE_OK != status_code)
    {
        // log!
    }

    ::curl_easy_cleanup(session);
    return req_answ;
}
