#ifndef __IPINFO__UTILER__HPP__
    #define __IPINFO__UTILER__HPP__

    #include <cstdint>
    #include <string>
    #include <vector>

    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __utiler
        {
            public:
                static void
                set_error(ipinfo::error &error,
                          const std::uint8_t code,
                          const std::string &&desc,
                          const std::string &&func);

                void        clear_info(ipinfo::__info &info);
                double      round_double(const double value,
                                         const std::uint8_t places) const;

                static bool is_host_supported(const std::string &host);
                static bool is_host_supported(const std::uint8_t host_id);
                static bool is_lang_correct(const std::string &lang,
                                            const std::string &host);

                std::string str_to_lower_case(const std::string &s);
                static bool is_host_excluded(const std::string &host,
                                             const std::vector<std::string> &excl_hosts);
        };
    }

#endif
