#ifndef __IPINFO__PARSER__HPP__
    #define __IPINFO__PARSER__HPP__

    #include <string>

    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __parser
        {
            public:
                void parse_data(const std::string &host,
                                const std::string &json,
                                ipinfo::__info_t &info);
        };
   }

#endif
