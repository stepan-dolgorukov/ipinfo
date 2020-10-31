#ifndef __IPINFO__UTIL__HPP__
    #define __IPINFO__UTIL__HPP__

    #include <iostream>
    #include <string>

    #include "ipinfo.hpp"



    namespace ipinfo
    {
        void \
            set_error(ipinfo::error_t &error, \
                      const ipinfo::ui8 code, \
                      const std::string &description, \
                      const std::string &function_name);


        void \
            clear_info(ipinfo::info_t &info);


        ipinfo::dbl \
            round_dbl(const ipinfo::dbl val, \
                      const ipinfo::sz places);
    }

#endif