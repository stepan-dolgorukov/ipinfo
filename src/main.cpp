// 1. Project: ipinfo
// 2. Author: DolgorukovGTA
// 3. Repository: https://github.com/DolgorukovGTA/ipinfo

#include <iostream>

#include "ipinfo/ipinfo.h"
#include "spdlog/spdlog.h"
#include "ipinfo/ipinfo.h"

// Using example (as an app).
// I recommend you to OFF the debug mode in this case.

int main(int argc, char* argv[])
{
    for (size_t i = 0u; i < argc; i++)
    {
        if (0 == std::string(argv[i]).compare("--help") ||
            0 == std::string(argv[i]).compare("-h"))
        {
            std::cout << "How to use ipinfo as application? "
                         "Easy: (./)ipinfo [ip]." << std::endl;

            std::cout << "If [ip] option is empty, you'll get the "
                         "information about your outside machine IP." << std::endl;

            return 0;
        }
    }

    std::string ip{};
    ip_info_t ip_info{};

    if (2 <= argc)
    {
        ip.append(argv[1]);
    }

    switch (get_ip_info(&ip_info, ip.empty() ? nullptr : &ip))
    {
        case 0u:
            print_ip_info(&ip_info);
            break;
        
        default:
            std::cout << "Couldn't get the information about IP.\n"
                         "Server doesn't response or inputted IP "
                         "is incorrect.\n" << std::endl;
    }

    return 0;
}
