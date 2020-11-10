#include <string>
#include <cstddef>

//#include <curl/curl.h>
//#include <curl/easy.h>

#include "../include/curl/curl.h"

#include "../../include/ipinfo/ipinfo.hpp"
#include "../../include/ipinfo/ipinfo_util.hpp"
#include "../../include/ipinfo/ipinfo_request.hpp"


namespace ipinfo
{
    static ipinfo::sz \
        recv_data(const char * const data, \
                const ipinfo::sz char_size, \
                const ipinfo::sz amount, \
                std::string * const answer)
    {
        if ((ipinfo::sz{0u} < amount) && \
            (ipinfo::sz{0u} < char_size) && \
            (std::nullptr_t{nullptr} != data) && \
            (std::nullptr_t{nullptr} != answer))
        {
            const ipinfo::sz total_bytes{char_size * amount};
            answer->append(data, total_bytes);

            return (total_bytes);
        }

        return ipinfo::sz{0u};
    }


    void \
        set_req_info_fields(const std::string &host, \
                            std::string &url, \
                            ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (url.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty URL string"}, \
                              std::string{__func__});
            return;
        }

        url.append(req_prefixes.at(host).at(std::string{"fields"}));

        const auto &params{ipinfo::req_params.at(host)};
        const ipinfo::sz max_idx{params.size() - ipinfo::sz{1u}};

        for (ipinfo::sz i{0u}; max_idx >= i; i++)
        {
            url.append(params.at(i));

            if (max_idx != i)
            {
                url.append(std::string{","});
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
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Unavailable host"}, \
                              std::string{__func__});
            return;
        }

        if (full_url.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty URL string"},
                              std::string{__func__});
            return;
        }

        if (lang.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty language string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_lang_avail(host, lang)))
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Unavailable language"}, \
                              std::string{__func__});
            return;
        }

        full_url.append(req_prefixes.at(host).at(std::string{"lang"}));

        for (const auto &pair : ipinfo::avail_langs.at(host))
        {
            if (int{0} == lang.compare(pair.first))
            {
                full_url.append(ipinfo::avail_langs.at(host).at(lang));
                return;
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
        if (host.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty host string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_host_avail(host)))
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Unavailable host"}, \
                              std::string{__func__});
            return;
        }

        if (lang.empty())
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty language string"}, \
                              std::string{__func__});
            return;
        }

        if (!(ipinfo::is_lang_avail(host, lang)))
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Unavailable language"}, \
                              std::string{__func__});
            return;
        }

        full_url.clear();
        full_url.append(req_paths.at(host));

        if (!(ip.empty()))
        {
            full_url.append(ip);
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
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Empty full URL string"}, \
                              std::string{ __func__});
            return;
        }

        CURL * const session{curl_easy_init()};
        CURLcode code{CURLcode::CURLE_OK};

        if (std::nullptr_t{nullptr} == session)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Start of a libcurl " \
                                          "session failed"}, \
                              std::string{__func__});
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
                         CURLOPT_PORT, ipinfo::ui32{80});

        curl_easy_setopt(session, \
                         CURLOPT_USERAGENT, \
                         "ipinfo module");

        code = curl_easy_perform(session);

        if (CURLcode::CURLE_OK != code)
        {
            ipinfo::set_error(error, \
                              ipinfo::ui8{1u}, \
                              std::string{"Data sending using " \
                                          "libcurl got fail."}, \
                              std::string{__func__});
        }

        curl_easy_cleanup(session);
        return;
    }
}
