#include "../../include/ipinfo/ipinfo_types.hpp"
#include "../../include/ipinfo/ipinfo_constants.hpp"
#include "../../include/ipinfo/ipinfo_requester.hpp"
#include "../../include/ipinfo/ipinfo_utiler.hpp"

#include <cpr/cpr.h>

#include <string>
#include <cstddef>      // std::size_t
#include <functional>
#include <numeric>      // std::accumulate

std::string
ipinfo::service::requester::__get_ready_request_info_fields(const std::string &host)
{
    std::string result{};
    const auto &fields{ipinfo::constants::REQUEST_INFO_FIELDS.at(host)};

    result = std::accumulate(
                std::next(fields.begin()),
                fields.end(),
                fields.at(0u),
                [](const std::string &chain, const std::string &elem) {
                    return std::move(chain + "," + elem);
                });

    return result;
}

std::string
ipinfo::service::requester::__get_ready_request_lang(
        const std::string &host,
        const std::string &lang)
{
    const auto &langs{ipinfo::constants::HOSTS_AVAILABLE_LANGS.at(host)};
    const auto find_result{langs.find(lang)};

    if (find_result != langs.end())
    {
        return find_result->second;
    }

    return {};
}

std::string
ipinfo::service::requester::request(
        const std::string &host,
        const std::string &ip,
        const std::string &lang,
        const std::string &api_key)
{
    cpr::Response resp{};

    const auto &path{ipinfo::constants::REQUEST_START_PATHS.at(host)};
    const auto &param_titles{ipinfo::constants::REQUEST_PARAMETERS_TITLES.at(host)};

    resp = cpr::Get(
        cpr::Url(path + ip),
        cpr::Parameters{
            {param_titles.at("fields"), this->__get_ready_request_info_fields(host)},
            {param_titles.at("lang"), this->__get_ready_request_lang(host, lang)},
            {param_titles.at("api_key"), api_key}
        });

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

ipinfo::types::error
ipinfo::service::requester::get_last_error() const
{
    return {}; // !!!
}
