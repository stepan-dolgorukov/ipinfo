#ifndef IPINFO_PARSER_HPP__
    #define IPINFO_PARSER_HPP

#include "ipinfo_types.hpp"

#include <cjson/cJSON.h>
#include <cstdint>
#include <string>

namespace ipinfo::service
{
    class parser
    {
        private:
            ::cJSON* __prepare(const std::string &json);

            template<template<typename ...> class T, typename sub_T> void
            __catch_node(
                    const ::cJSON &data,
                    T<sub_T> &node,
                    const std::string &host);

            template<template<typename ...> class T> void
            __fill_node(
                    T<std::string> &node,
                    const ::cJSON &item,
                    const std::string &host);

            template<template<typename ...> class T> void
            __fill_node(
                    T<std::int32_t> &node,
                    const ::cJSON &item,
                    const std::string &host);

            template<template<typename ...> class T> void
            __fill_node(
                    T<double> &node,
                    const ::cJSON &item,
                    const std::string &host);

            template<template<typename ...> class T> void
            __fill_node(
                    T<bool> &node,
                    const ::cJSON &item,
                    const std::string &host);
        public:
            void parse(
                    const std::string &json,
                    ipinfo::service::types::info &info,
                    const std::string &host);

            ipinfo::types::error get_last_error(void) const;
    };
}

#endif
