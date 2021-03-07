// This file mustn't include other files
// of the ipinfo project. The file provides
// entity aliases to make code compact in
// situations where you really need it.

#ifndef IPINFO_ALIASES_HPP
    #define IPINFO_ALIASES_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace ipinfo::constants{}
namespace ipi = ipinfo;

namespace ipinfo::srv
{
    class requester;
    class parser;
    class utiler;
}

// We couldn't include 'ipinfo_types.hpp' to
// 'ipinfo_aliases.hpp', 'coz one already
// depends from one. Thus we need to just
// copy types definitions here.

namespace ipinfo::srv::types
{
    struct info;
    struct request_attributes;
}

namespace ipinfo::usr::types
{
    struct error;
    template<typename T> struct node;
}

namespace ipinfo::als
{
    namespace C = constants;

    using info = srv::types::info;
    using req_attrs = srv::types::request_attributes;
    using err = usr::types::error;

    using u8 = std::uint8_t;
    using str = std::string;

    template <typename T>
        using u_node = usr::types::node<T>;

    template<typename T, const std::size_t N>
        using arr = std::array<T, N>;

    template<typename K, typename V>
        using map = std::map<K, V>;

    template<typename T>
        using vec = std::vector<T>;
}

#endif // IPINFO_ALIASES_HPP
