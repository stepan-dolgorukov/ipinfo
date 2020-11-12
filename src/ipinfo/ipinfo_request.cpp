#include <iostream>
#include <string>
#include <cstddef>


#include "../include/curl/curl.h"

#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_util.hpp"
#include "../../include/ipinfo/ipinfo_request.hpp"


namespace ipinfo
{
    static std::size_t \
        recv_data(const char * const data, \
                  std::size_t char_size, \
                  std::size_t chars_amount, \
                  std::string * const answer)
    {
        if (0u < chars_amount && \
            0u < char_size && \
            nullptr != data && \
            nullptr != answer)
        {
            const auto total_bytes{char_size * chars_amount};
            answer->append(data, total_bytes);

            return total_bytes;
        }

        return 0u;
    }


    void \
        set_req_info_fields(const std::string &host, \
                            std::string &url, \
                            ipinfo::error_t &error)
    {
       if (!(ipinfo::is_host_correct(host, error)))
       {
           return;
       }

        if (url.empty())
        {
            ipinfo::set_error(error, 1u, \
                              {"Empty URL string"}, \
                              {__func__});
            return;
        }

        url += req_prefixes.at(host).at("fields");

        const auto &params
        {
            ipinfo::req_params.at(host)
        };

        const auto max_idx
        {
            params.size() - 1u
        };

        for (auto i{0u}; max_idx >= i; i++)
        {
            url.append(params.at(i));

            if (max_idx != i)
            {
                url.append(",");
            }
        }

        return;
    }


    void \
        set_req_lang(const std::string &host, \
                     std::string &full_url, \
                     const std::string &lang, \
                     ipinfo::error_t &error)
    {
        if (!(ipinfo::is_host_correct(host, error)))
        {
            ipinfo::set_error(error, 1u, \
                              {"Unavailable host"}, \
                              {__func__});
            return;
        }

        if (full_url.empty())
        {
            ipinfo::set_error(error, 1u, \
                              {"Empty URL string"},
                              {__func__});
            return;
        }

        if (ipinfo::is_lang_correct(host, lang, error))
        {
            full_url += req_prefixes.at(host).at("lang");

            for (const auto &pair : ipinfo::avail_langs.at(host))
            {
                if (lang == pair.first)
                {
                    full_url += ipinfo::avail_langs.at(host).at(lang);
                    return;
                }
            }
        }

        return;
    }


    void \
        get_full_url(const std::string &host, \
                     const std::string &ip, \
                     const std::string &lang, \
                     std::string &full_url, \
                     ipinfo::error_t &error)
    {
        if (!(ipinfo::is_host_correct(host, error)))
        {
            return;
        }

        if (!(ipinfo::is_lang_correct(host, lang, error)))
        {
            return;
        }

        full_url.clear();
        full_url += req_paths.at(host);

        if (!(ip.empty()))
        {
            full_url += ip;
        }

        ipinfo::set_req_info_fields(host, full_url, error);
        ipinfo::set_req_lang(host, full_url, lang, error);

        return;
    }


    void \
        get_data(const std::string &full_url, \
                 std::string &answer, \
                 ipinfo::error_t &error)
    {

        if (full_url.empty())
        {
            ipinfo::set_error(error, 1u, \
                              {"Empty full URL string"}, \
                              { __func__});
            return;
        }

        CURLcode code{};
        CURL * const session
        {
            curl_easy_init()
        };

        if (nullptr == session)
        {
            ipinfo::set_error(error, 1u, \
                              {"Start of a libcurl " \
                                          "session failed"}, \
                              {__func__});
            return;
        }

        answer.clear();

        curl_easy_setopt(session, \
                         CURLOPT_URL, \
                         full_url.c_str());

        curl_easy_setopt(session, \
                         CURLOPT_WRITEDATA, \
                         (&answer));

        curl_easy_setopt(session, \
                         CURLOPT_WRITEFUNCTION,\
                         (&recv_data));

        curl_easy_setopt(session, \
                         CURLOPT_PROTOCOLS, \
                         CURLPROTO_HTTP);

        curl_easy_setopt(session, \
                         CURLOPT_PORT,
                         80);

        curl_easy_setopt(session, \
                         CURLOPT_USERAGENT, \
                         "ipinfo module");

        code = curl_easy_perform(session);

        if (CURLcode::CURLE_OK != code)
        {
            ipinfo::set_error(error, 1u, \
                              {"Data sending got fail"}, \
                              {__func__});
        }

        curl_easy_cleanup(session);
        return;
    }
}
