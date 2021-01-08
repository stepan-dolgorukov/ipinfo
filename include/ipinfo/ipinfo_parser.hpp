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
                ::cJSON         *__data{};
                ipinfo::error   __error{};

            public:
                void    put_json(const std::string &json);
                void    deserialize_json(ipinfo::__info &info,
                                         const std::string &host) const;

                ipinfo::error get_last_error(void) const;
        };
   }

#endif
