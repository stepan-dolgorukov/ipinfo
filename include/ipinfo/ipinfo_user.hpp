#ifndef __IPINFO__USER__HPP__
    #define __IPINFO__USER__HPP__


    #include <string>


    #include "ipinfo_types.hpp"


    namespace ipinfo
    {
        void
            get_info(ipinfo::info_t &info,
                     const std::string &ip,
                     const std::string &lang,
                     ipinfo::error_t &error);

        void
            print_info(const ipinfo::info_t &info);
    }

#endif