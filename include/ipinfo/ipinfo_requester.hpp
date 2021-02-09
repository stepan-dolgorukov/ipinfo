#ifndef IPINFO_REQUESTER_HPP
    #define IPINFO_REQUESTER_HPP

#include "ipinfo_types.hpp"
#include <string>

namespace ipinfo::service
{
    class requester
    {
        private:
            const std::string __get_ready_request_info_fields(const std::string &host);
            const std::string __get_ready_request_lang(
                                    const std::string &host,
                                    const std::string &lang);
        public:
            std::string request(const ipinfo::service::types::req_attrs &req_attrs);
            ipinfo::user::types::error get_last_error(void) const;
    };
}

#endif
