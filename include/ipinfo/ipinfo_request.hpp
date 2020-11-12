#ifndef __IPINFO__REQUEST__HPP__
    #define __IPINFO__REQUEST__HPP__

    #include <math.h>
    #include <string>


    #include "ipinfo_types.hpp"


    namespace ipinfo
    {
        void \
            set_req_info_fields(const std::string &host, \
                                std::string &url, \
                                ipinfo::error_t &error);


        void \
            set_req_lang(const std::string &host, \
                        std::string &full_url, \
                        const std::string &lang, \
                        ipinfo::error_t &error);


        void \
            get_full_url(const std::string &host, \
                         const std::string &ip, \
                         const std::string &lang, \
                         std::string &full_url, \
                         ipinfo::error_t &error);


        void \
            get_data(const std::string &full_url, \
                     std::string &answer, \
                     ipinfo::error_t &error);
    }

#endif
