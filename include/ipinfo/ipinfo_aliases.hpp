// This file must not include other files of the ipinfo project.
// The file provides entity aliases to save space in situations ...
// ... where you really need it.

#ifndef IPINFO_ALIASES_HPP
    #define IPINFO_ALIASES_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace ipinfo{}
namespace ipi = ipinfo;

namespace ipinfo::srv
{
    class requester;
    class parser;
    class utiler;
}

namespace ipinfo::srv::types
{
    struct info;
    struct req_attrs;
}

namespace ipinfo::usr::types
{
    struct error;
    template<typename T> struct node;
}

namespace ipinfo::als
{
    using info      = ipinfo::srv::types::info;
    using req_attrs = ipinfo::srv::types::req_attrs;
    using err       = ipinfo::usr::types::error;

    template <typename T> using u_node = ipinfo::usr::types::node<T>;

    using u8  = std::uint8_t;
    using str = std::string;

    template<typename T, std::size_t N> using arr = std::array<T, N>;
    template<typename K, typename V>    using map = std::map<K, V>;
    template<typename T>                using vec = std::vector<T>;
}

#endif // IPINFO_ALIASES_HPP
