#ifndef IPINFO_UTILER_HPP
    #define IPINFO_UTILER_HPP

#include "ipinfo_types.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace ipinfo::srv
{
    class utiler;
}

class ipinfo::srv::utiler
{
  private:
    template<template<typename ...> class T, typename sub_T>
        void __clear_node(T<sub_T> &node) const;

  public:
    double round_val(
        const double value,
        const std::uint8_t places) const;

    void clear_info(ipinfo::srv::types::info &info) const;
    std::string to_lower_case(const std::string &s) const;

    bool is_host_supported(const std::string &host) const;
    bool is_host_supported(const std::uint8_t host_id) const;

    bool is_lang_supported(const std::string &lang) const;
    bool is_lang_supported(const std::uint8_t lang_id) const;

    bool is_lang_supported(
        const std::string &lang,
        const std::string &host) const;
};

#endif // IPINFO_UTILER_HPP
