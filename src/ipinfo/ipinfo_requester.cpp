#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_aliases.hpp"
#include "../../include/ipinfo/ipinfo_constants.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"

#include <cpr/cpr.h>

#include <cstddef>    // std::size_t
#include <functional> // std::function (for lambdas)
#include <numeric>    // std::accumulate

const std::string
ipi::srv::requester::__get_ready_request_info_fields(const als::str &host) const
{
    const auto &fields{ constants::REQUEST_INFO_FIELDS.at(host) };
    const auto itemize {
        [](const std::string &chain, const std::string &elem) {
            return std::move(chain + ',' + elem);
        }
    };

    return std::accumulate(std::next(fields.begin()),
            fields.end(), fields.at(0u), itemize);
}

const std::string
ipinfo::srv::requester::__get_ready_request_lang(
        const std::string &host,
        const std::string &lang) const
{
    const auto &langs{ constants::HOSTS_AVAILABLE_LANGS.at(host) };
    const auto res{ langs.find(lang) };

    return (res != langs.end()) ? res->second : "";
}

std::string
ipi::srv::requester::request(const als::req_attrs &req_attrs) const
{
    const std::string &path{
        constants::REQUEST_START_PATHS.at(req_attrs.host)};

    const auto &param_titles{
        constants::REQUEST_PARAMETERS_TITLES.at(req_attrs.host)
    };

    const cpr::Url url{ path + req_attrs.ip };
    const cpr::Parameters params = {
        {param_titles.at("fields"), this->__get_ready_request_info_fields(req_attrs.host)},
        {param_titles.at("lang"), this->__get_ready_request_lang(req_attrs.host, req_attrs.lang)},
        {param_titles.at("api_key"), req_attrs.api_key}
    };

    const cpr::Response resp{ cpr::Get(url, params) };

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

ipinfo::usr::types::error
ipinfo::srv::requester::get_last_error() const
{
    return {}; // !!!
}
