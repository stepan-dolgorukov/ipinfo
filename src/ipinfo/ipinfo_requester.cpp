#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_constants.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cpr/cpr.h>

#include <cstddef>    // std::size_t
#include <functional> // std::function (for lambdas)
#include <numeric>    // std::accumulate

const std::string
ipinfo::service::requester::__get_ready_request_info_fields(const std::string &host)
{
    const auto &fields{ipinfo::constants::REQUEST_INFO_FIELDS.at(host)};
    const auto itemize {
        [](const std::string &chain, const std::string &elem) {
            return std::move(chain + ',' + elem);
        }
    };

    return std::accumulate(std::next(fields.begin()), fields.end(), fields.at(0u), itemize);
}

const std::string
ipinfo::service::requester::__get_ready_request_lang(
        const std::string &host,
        const std::string &lang)
{
    const auto &langs{ipinfo::constants::HOSTS_AVAILABLE_LANGS.at(host)};
    const auto find_result{langs.find(lang)};

    if (find_result != langs.end())
    {
        // return a language code
        return find_result->second;
    }

    return {};
}

std::string
ipinfo::service::requester::request(
    const ipinfo::service::types::req_attrs &req_attrs)
{
    const std::string &path {
        ipinfo::constants::REQUEST_START_PATHS.at(req_attrs.host)
    };

    const auto &param_titles {
        ipinfo::constants::REQUEST_PARAMETERS_TITLES.at(req_attrs.host)
    };

    cpr::Response   resp{};
    cpr::Url        url{};
    cpr::Parameters params{};

    url = path + req_attrs.ip;

    params = {
        {
            param_titles.at("fields"),
            this->__get_ready_request_info_fields(req_attrs.host)
        },

        {
            param_titles.at("lang"),
            this->__get_ready_request_lang(req_attrs.host, req_attrs.lang)
        },

        {
            param_titles.at("api_key"),
            req_attrs.api_key
        }
    };

    resp = cpr::Get(url, params);

    if (200u != resp.status_code)
    {
        // error
        return {};
    }

    if (resp.text.empty())
    {
        // error
        return {};
    }

    return resp.text;
}

ipinfo::user::types::error
ipinfo::service::requester::get_last_error() const
{
    return {}; // !!!
}
