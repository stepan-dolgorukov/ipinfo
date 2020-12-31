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
                static void
                set_error(error_t &error,
                          const std::uint8_t code,
                          const std::string &&description,
                          const std::string &&function_name);

                void
                clear_info(ipinfo::__info_t &info);

                double
                round_double(const double value,
                             const std::uint8_t places) const;

                static bool
                is_host_correct(const std::string &host);

                static bool
                is_host_correct(const std::uint8_t host_id);

                static bool
                is_lang_correct(const std::string &host,
                                const std::string &language);

                std::string
                str_to_lower_case(const std::string &s);
        };
    }

#endif
