#ifndef IPINFO_UTILER_HPP
    #define IPINFO_UTILER_HPP

#include "ipinfo_types.hpp"
#include "ipinfo_aliases.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace ipinfo::srv{ class utiler; }
class ipinfo::srv::utiler
{
    private:
        template<template<typename ...> class T, typename sub_T> void
        __clear_node(T<sub_T> &node) const;

    public:
        void clear_info(als::info &info) const;

        double   round_val(const double v, const std::uint8_t places) const;
        als::str to_lower_case(const std::string &s)                  const;

        bool is_host_supported(const std::string &host)    const;
        bool is_host_supported(const std::uint8_t host_id) const;

        bool is_lang_supported(const std::string &lang)    const;
        bool is_lang_supported(const std::uint8_t lang_id) const;
        bool is_lang_supported(const als::str &lang,
                               const als::str &host)       const;
};

#endif // IPINFO_UTILER_HPP
