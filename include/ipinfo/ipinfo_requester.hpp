#ifndef IPINFO_REQUESTER_HPP
    #define IPINFO_REQUESTER_HPP

#include "ipinfo_types.hpp"
#include "ipinfo_aliases.hpp"

#include <string>

namespace ipinfo::srv
{
    class requester;
}

class ipinfo::srv::requester
{
  private:
    std::string __get_info_fields(const std::string &host) const;

    std::string __get_lang(
        const std::string &host,
        const std::string &lang) const;

  public:
    std::string request(const srv::types::request_attributes &ra) const;
    usr::types::error get_last_error() const;
};

#endif // IPINFO_REQUESTER_HPP
