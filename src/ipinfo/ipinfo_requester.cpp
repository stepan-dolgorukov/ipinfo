#include <string>
#include <cstddef>
#include <curl/curl.h>

#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_values.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

namespace ipinfo
{
    static std::size_t recv(
            const char * const data,
            std::size_t ch_size,
            std::size_t ch_nums,
            std::string * const res);

    static std::string
    get_ready_request_info_fields(const std::string &host);

    static std::string
    get_ready_request_lang(const std::string &host,
                           const std::string &lang);
}

std::size_t
ipinfo::recv(const char * const data,
             std::size_t ch_size,
             std::size_t ch_nums,
             std::string * const res)
{
    const std::size_t total_bytes{ch_size * ch_nums};

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
    const auto &curr_avail_langs{
        ipinfo::hosts_avail_langs_codes.at(host)};

    for (auto &&[__lang, __] : curr_avail_langs)
    {
        if (__lang == lang)
        {
            return curr_avail_langs.at(lang);
        }
    }

    return {};
}

void
ipinfo::__requester::create_request_url(const std::string &host,
                                        const std::string &ip,
                                        const std::string &lang,
                                        const std::string &api_key)
{
    __request_url.clear();

    __request_url += req_start_paths.at(host);
    __request_url += ip;

    __request_url += "?";

    __request_url += req_param_titles.at(host).at("fields");
    __request_url += "=";

    __request_url += get_ready_request_info_fields(host);

    __request_url += "&";

    __request_url += req_param_titles.at(host).at("lang");
    __request_url += "=";
    __request_url += get_ready_request_lang(host, lang);

    if (api_key.empty())
    {
        return;
    }

    __request_url += "&";
    __request_url += req_param_titles.at(host).at("api_key");
    __request_url += "=";
    __request_url += api_key;

    return;
}

void
ipinfo::__requester::send_request()
{
    __request_answer.clear();

    ::CURL * const session{::curl_easy_init()};

    if (nullptr == session)
    {
        __utiler::set_error(
                __error,
                FAILED_START_LIBCURL_SESSION,
                "Failed to start a libcurl session",
                __func__);

        return;
    }

    ::curl_easy_setopt(session, ::CURLOPT_URL, __request_url.c_str());
    ::curl_easy_setopt(session, ::CURLOPT_WRITEDATA, &__request_answer);
    ::curl_easy_setopt(session, ::CURLOPT_USERAGENT, "ipinfo module");
    ::curl_easy_setopt(session, ::CURLOPT_WRITEFUNCTION, &recv);

    if (::CURLcode::CURLE_OK != ::curl_easy_perform(session))
    {
        __utiler::set_error(
                __error,
                FAILED_REQUEST_SENDING,
                "Failed to send a request",
                __func__);
    }

    if (__request_answer.empty())
    {
        __utiler::set_error(
                __error,
                EMPTY_REQUEST_ANSWER,
                "Empty request answer",
                __func__);
    }

    ::curl_easy_cleanup(session);
    return;
}

std::string
ipinfo::__requester::get_request_answer() const
{
    return __request_answer;
}

ipinfo::error
ipinfo::__requester::get_last_error() const
{
    return __error;
}
