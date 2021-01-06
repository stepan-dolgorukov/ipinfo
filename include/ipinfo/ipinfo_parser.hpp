#ifndef __IPINFO__PARSER__HPP__
    #define __IPINFO__PARSER__HPP__

    #include <string>
    #include <cjson/cJSON.h>

    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __parser
        {
            private:
                ::cJSON   *__data{};
                error_t   __error{};

            public:
                void    put_json(const std::string &json);
                void    deserialize_json(__info_t &info,
                                         const std::string &host) const;

                error_t get_last_error(void) const;
        };
   }

#endif
