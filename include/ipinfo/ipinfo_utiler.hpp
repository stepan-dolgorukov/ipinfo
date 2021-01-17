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
            void clear_info(ipinfo::service::types::info &info);

            double round_val(
                    const double v,
                    const std::uint8_t places) const;

            bool is_host_supported(const std::string &host);
            bool is_host_supported(const std::uint8_t host_id);

            bool is_lang_supported(
                    const std::string &lang,
                    const std::string &host);

            std::string to_lower_case(const std::string &s);

            bool is_host_excluded(
                    const std::string &host,
                    const std::vector<std::string> &excl_hosts);
    };
}

#endif
