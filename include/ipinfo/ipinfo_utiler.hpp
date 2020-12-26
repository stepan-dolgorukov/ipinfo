#ifndef __IPINFO__UTILER__HPP__
    #define __IPINFO__UTILER__HPP__

    #include <string>
    #include <cstdint>

    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __utiler
        {
            public:
                // 06/12/20: add this function usage to the code
                void
                set_error(ipinfo::__error_t &error,
                          const std::uint8_t code,
                          const std::string &&description,
                          const std::string &&function_name);

                void
                clear_info(ipinfo::__info_t &info);

                double
                round_double(const double value,
                             const std::uint8_t places) const;

                // 04/12/20 TODO: add this function usage to the code
                bool
                is_host_correct(const std::string &host,
                                ipinfo::__error_t &error);

                // 04/12/20 TODO: add this function usage to the code
                bool
                is_language_correct(const std::string &host,
                                    const std::string &language,
                                    ipinfo::__error_t &error);

                std::string
                str_to_lower_case(const std::string &s);
        };
    }

#endif
