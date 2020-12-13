#ifndef __IPINFO__UTILER__HPP__
    #define __IPINFO__UTILER__HPP__

    #include <string>
    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __utiler
        {
            public:
                // 06/12/20: add this function usage to the code
                static void
                set_error(ipinfo::__error_t &error,
                          const std::uint8_t code,
                          const std::string &&description,
                          const std::string &&function_name);

                static void
                clear_info(ipinfo::__info_t &info);

                static double
                round_double(const double value,
                             const std::uint8_t places);

                // 04/12/20 TODO: add this function usage to the code
                static bool
                is_host_correct(const std::string &host,
                                ipinfo::__error_t &error);

                // 04/12/20 TODO: add this function usage to the code
                static bool
                is_language_correct(const std::string &host,
                                    const std::string &language,
                                    ipinfo::__error_t &error);

                static std::string
                str_to_lower_case(const std::string &s);
        };
    }

#endif
