#ifndef __IPINFO__UTIL__HPP__
    #define __IPINFO__UTIL__HPP__

    #include <cstdint>
    #include <iostream>
    #include <string>

    #include "ipinfo_types.hpp"


    namespace ipinfo
    {
        void \
            set_error(ipinfo::error_t &error, \
                      const std::uint8_t code, \
                      const std::string &description, \
                      const std::string &function_name);


        void \
            clear_info(ipinfo::info_t &info);


        double \
            round_double(const double value, \
                         const std::uint8_t places);


        bool \
            is_host_correct(const std::string &host, \
                            ipinfo::error_t &error);


        bool \
            is_lang_correct(const std::string &host, \
                            const std::string &lang, \
                            ipinfo::error_t &error);


        bool \
            is_status_success(const ipinfo::info_t &info);
    }

#endif
