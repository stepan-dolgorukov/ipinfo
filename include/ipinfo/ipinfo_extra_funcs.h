#ifndef __IPINFO__EXTRA__FUNCS__H__
    #define __IPINFO__EXTRA__FUNCS__H__


    #include "ipinfo.h"
    #include <iostream>


    namespace ipinfo
    {
        void
            set_error(ipinfo::error_t &error,
                      const ipinfo::ui8 code,
                      const std::string &description,
                      const std::string &function_name);


        void
            clear_info(ipinfo::info_t &info);


        ipinfo::dbl
            round_dbl(const ipinfo::dbl val,
                      const ipinfo::sz places);


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