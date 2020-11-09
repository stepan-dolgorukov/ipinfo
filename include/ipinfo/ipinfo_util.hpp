#ifndef __IPINFO__UTIL__HPP__
    #define __IPINFO__UTIL__HPP__

    #include <cstdint>
#include <iostream>
    #include <string>

    #include "ipinfo.hpp"



    namespace ipinfo
    {
        void \
            set_error(ipinfo::error_t &error, \
                      const std::uint8_t code, \
                      const std::string &description, \
                      const std::string &function_name);


        void \
            clear_info(ipinfo::info_t &info);


        ipinfo::dbl \
            round_dbl(const double value, \
                      const std::uint8_t places);


        bool \
            is_host_avail(const std::string &host);


        bool \
            is_lang_avail(const std::string &host, \
                          const std::string &lang);

        bool \
            is_status_success(const ipinfo::info_t &info);
    }

#endif
