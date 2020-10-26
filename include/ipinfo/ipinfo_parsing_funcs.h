#ifndef __IPINFO__PARSING__FUNCS__H__
    #define __IPINFO__PARSING__FUNCS__H__


    #include "ipinfo.h"
    #include "../cJSON/cJSON.h"


    namespace ipinfo
    {

        template<typename T> void
            parse_json_node(const cJSON &data,
                            const std::string &host,
                            ipinfo::node<T> &node,
                            ipinfo::error_t &error);

        
        template<> void
            parse_json_node(const cJSON &data,
                            const std::string &host,
                            ipinfo::node<std::string> &node,
                            ipinfo::error_t &error);


        void
            parse_data(const std::string &host,
                      const std::string &json,
                      ipinfo::info_t &info,
                      ipinfo::error_t &error);


        void
            fill_ui32_node(const cJSON &item,
                           const std::string &host,
                           void * const node,
                           ipinfo::error_t &error);


        void
            fill_i32_node(const cJSON &item,
                           const std::string &host,
                           void * const node,
                           ipinfo::error_t &error);


        void
            fill_dbl_node(const cJSON &item,
                          const std::string &host,
                          void * const node,
                          ipinfo::error_t &error);

        void
            fill_bl_node(const cJSON &item,
                         const std::string &host,
                         void * const node,
                         ipinfo::error_t &error);
    }

#endif