#ifndef __IPINFO__PRINT__HPP__
    #define __IPINFO__PRINT__HPP__

    #include "ipinfo.hpp"


    namespace ipinfo
    {
        template <typename T> void
            print_node(const node<T> &node)
        {
            for (const auto &host : ipinfo::avail_hosts)
            {
                const auto &current_node
                {
                    node.content.at(host)
                };
            
                if ((current_node.is_parsed) &&
                    (!(node.description.empty())))
                {
                    std::cout << (node.description) <<
                                (" [") << (host) << ("]: ") <<
                                (current_node.value) << std::endl;
                    return;
                }
            }

            std::cout << (node.description) << 
                        (": N/A") << std::endl;

            return;
        }
    }

#endif