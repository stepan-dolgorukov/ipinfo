#ifndef IPINFO_REQUESTER_HPP
    #define IPINFO_REQUESTER_HPP

#include "ipinfo_types.hpp"
#include <string>

namespace ipinfo::service
{
    class requester
    {
        private:
            std::string __get_ready_request_info_fields(const std::string &host);
            std::string __get_ready_request_lang(const std::string &host,
                                                 const std::string &lang);

        public:
            std::string request(
                    const std::string &host,
                    const std::string &ip,
                    const std::string &lang,
                    const std::string &api_key);

            ipinfo::types::error get_last_error(void) const;
    };
}

#endif
