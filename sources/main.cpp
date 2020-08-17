// 1. Project: ipinfo
// 2. Author: DolgorukovGTA
// 3. Repository: https://github.com/DolgorukovGTA/ipinfo

#include <iostream>

#include "ipinfo/ipinfo.h"
#include "spdlog/spdlog.h"
#include "ipinfo/ipinfo.h"

// Using example.
int main(int argc, char* argv[])
{
    std::string ip{};

    if (2 <= argc)
    {
        ip = std::string(argv[1]);
    }

    ip_info_t ip_info{};

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
