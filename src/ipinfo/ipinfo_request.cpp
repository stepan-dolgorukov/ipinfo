#include <curl/curl.h>


#include "../../include/ipinfo/ipinfo.h"
#include "../../include/ipinfo/ipinfo_request_funcs.h"
#include "../../include/ipinfo/ipinfo_extra_funcs.h"


namespace ipinfo
{
    static ipinfo::sz
        recv_data(const char * const data,
                const ipinfo::sz ch_sz,
                const ipinfo::sz amount,
                std::string * const answer)
    {
        if ((0u < amount) &&
            (0u < ch_sz) &&
            (nullptr != data) &&
            (nullptr != answer))
        {
            const ipinfo::sz total_bytes{ch_sz * amount};
            answer->append(data, total_bytes);
            return (total_bytes);
        }
        
        return (0u);
    }


    void
        set_req_info_fields(const std::string &host,
                            std::string &url,
                            ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty host string"), __func__);
            return;
        }

        if (url.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty URL string"), __func__);
            return;
        }

        url.append(req_prefixes.at(host).at("fields"));

        const auto &params{ipinfo::req_params.at(host)};
        const ipinfo::sz max_idx{params.size() - 1};

        for (ipinfo::sz i{0u}; max_idx >= i; i++)
        {
            url.append(params.at(i));

            if (max_idx != i)
            {
                url.append({","});
            }
        }

        return;
    }


    void
        set_req_lang(const std::string &host,
                     std::string &full_url,
                     const std::string &lang,
                     ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty host string"), __func__);
            return;
        }

        if (full_url.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty URL string"), __func__);
            return;
        }

        if (lang.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty language string"), __func__);
            return;
        }


        full_url.append(req_prefixes.at(host).at("lang"));
        
        for (const auto &p : ipinfo::avail_langs.at(host))
        {
            if (lang == p.first)
            {
                full_url.append(avail_langs.at(host).at(p.first));
                return;
            }
        }

        set_error(error, (1u), ("Unavailable request language. " \
                                "Auto switch to EN."), __func__);
        
        full_url.append(avail_langs.at(host).at("English"));

        return;
    }


    void
        get_full_url(const std::string &host,
                     const std::string &ip,
                     const std::string &lang,
                     std::string &full_url,
                     ipinfo::error_t &error)
    {
        if (host.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty host string"), __func__);
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


    void
        get_data(const std::string &full_url,
                 std::string &answer,
                 ipinfo::error_t &error)
    {

        if (full_url.empty())
        {
            ipinfo::set_error(error, (1u), ("Empty full URL string"), __func__);
            return;
        }

        CURL * const session{curl_easy_init()};
        CURLcode code{CURLcode::CURLE_OK};

        if (nullptr == session)
        {
            ipinfo::set_error(error, (1u), ("Start of a libcurl session failed"), __func__);
            return;
        }

        answer.clear();
        curl_easy_setopt(session, CURLOPT_URL, full_url.c_str());
        
        curl_easy_setopt(session, CURLOPT_WRITEDATA, &answer);
        curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, recv_data);
        
        curl_easy_setopt(session, CURLOPT_PROTOCOLS, CURLPROTO_HTTP);
        curl_easy_setopt(session, CURLOPT_PORT, (80));
        curl_easy_setopt(session, CURLOPT_USERAGENT, ("ipinfo module"));

        code = curl_easy_perform(session);

        if (CURLcode::CURLE_OK != code)
        {
            ipinfo::set_error(error, (1u), ("Data sending using " \
                                            "libcurl got fail."), __func__);
        }

        return;
    }

}
