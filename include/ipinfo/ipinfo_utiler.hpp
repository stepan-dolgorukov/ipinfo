#ifndef IPINFO_UTILER_HPP
    #define IPINFO_UTILER_HPP

#include "ipinfo_types.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace ipinfo::service
{
    class utiler
    {
        private:
            template<template<typename ...> class T, typename sub_T> void
            __clear_node(T<sub_T> &node) const;

        public:
            void clear_info(ipinfo::service::types::info &info) const;

            double round_val(
                    const double v,
                    const std::uint8_t places) const;

            bool is_host_supported(const std::string &host) const;
            bool is_host_supported(const std::uint8_t host_id) const;

            bool is_lang_supported(
                    const std::string &lang,
                    const std::string &host) const;

            std::string to_lower_case(const std::string &s) const;

            bool is_host_excluded(
                    const std::string &host,
                    const std::vector<std::string> &excl_hosts) const;
    };
}

#endif
