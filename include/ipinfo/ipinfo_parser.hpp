#ifndef __IPINFO__PARSER__HPP__
    #define __IPINFO__PARSER__HPP__

    #include <string>

    #include "../cJSON/cJSON.h"
    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __parser
        {
            private:
                ::cJSON   *__data;
                error_t   __error;

            public:
                void            put_json(const std::string &s);
                void            deserialize_json(ipinfo::__info_t &i,
                                                 const std::string &host) const;
                error_t         get_last_error(void) const;
        };
   }

#endif
