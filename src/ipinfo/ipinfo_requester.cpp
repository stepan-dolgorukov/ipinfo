#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_aliases.hpp"
#include "../../include/ipinfo/ipinfo_constants.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"

#include <cpr/cpr.h>

#include <cstddef>    // std::size_t
#include <numeric>    // std::accumulate

std::string
ipinfo::srv::requester::__get_info_fields(const std::string &host) const
{
    const auto &fields{ constants::REQUEST_INFO_FIELDS.at(host) };
    const auto itemize {
        [](const std::string &s, const std::string &elem) -> std::string {
            return s + ',' + elem;
        }
    };

    return std::accumulate(
        std::next(fields.begin()),
        fields.end(), fields.at(0u), itemize);
}

std::string
ipinfo::srv::requester::__get_lang(
    const std::string &host,
    const std::string &lang) const
{
    const auto &langs{ constants::HOSTS_AVAILABLE_LANGS.at(host) };
    const auto res{ langs.find(lang) };

    if (res != langs.end())
    {
        return res->second;
    }

    return {};
}

std::string
ipinfo::srv::requester::request(const srv::types::request_attributes &ra) const
{
    const std::string &path {
        constants::REQUEST_START_PATHS.at(ra.host)};

    const auto &param_titles {
        constants::REQUEST_PARAMETERS_TITLES.at(ra.host)
    };

    const std::string
        fields{ __get_info_fields(ra.host) },
        lang{ __get_lang(ra.host, ra.lang) };

    const cpr::Parameters params = {
        { param_titles.at("fields"), fields },
        { param_titles.at("lang"), lang },
        { param_titles.at("api_key"), ra.api_key }
    };

    const cpr::Url url{ path + ra.ip };
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
