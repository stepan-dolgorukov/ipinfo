#ifndef __IPINFO__PARSE__HPP__
    #define __IPINFO__PARSE__HPP__

    #include "ipinfo_types.hpp"

    #include "../cJSON/cJSON.h"


    namespace ipinfo
    {
        template<typename T> void \
            parse_json_node(const cJSON &data, \
                            const std::string &host, \
                            ipinfo::node<T> &node, \
                            ipinfo::error_t &error);


        template<> void \
            parse_json_node(const cJSON &data, \
                            const std::string &host, \
                            ipinfo::node<std::string> &node, \
                            ipinfo::error_t &error);


        void \
            parse_data(const std::string &host, \
                       const std::string &json, \
                       ipinfo::info_t &info, \
                       ipinfo::error_t &error);


        void \
            fill_uint32_node(const cJSON &item, \
                             const std::string &host, \
                             void * const node, \
                             ipinfo::error_t &error);


        void \
            fill_int32_node(const cJSON &item, \
                            const std::string &host, \
                            void * const node, \
                            ipinfo::error_t &error);


        void \
            fill_double_node(const cJSON &item, \
                             const std::string &host, \
                             void * const node, \
                             ipinfo::error_t &error);


        void \
            fill_bool_node(const cJSON &item, \
                           const std::string &host, \
                           void * const node, \
                           ipinfo::error_t &error);
    }

#endif
