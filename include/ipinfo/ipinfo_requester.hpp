#ifndef IPINFO_REQUESTER_HPP
    #define IPINFO_REQUESTER_HPP

#include "ipinfo_types.hpp"
#include "ipinfo_aliases.hpp"

#include <string>

namespace ipinfo::srv{ class requester; }
class ipinfo::srv::requester
{
    private:
        const als::str __get_ready_request_info_fields(const als::str &host) const;
        const als::str __get_ready_request_lang(
                                const als::str &host,
                                const als::str &lang) const;
    public:
        als::str request(const als::req_attrs &req_attrs) const;
        als::err get_last_error(void)                     const;
};

#endif // IPINFO_REQUESTER_HPP
