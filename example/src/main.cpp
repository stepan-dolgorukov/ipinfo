#include <string>

#include "../include/ipinfo/ipinfo.hpp"


int main(void)
{
    ipinfo::info_t info{};
    ipinfo::error_t error{};

    ipinfo::get_info(info, \
                     std::string{"8.8.8.8"}, \
                     std::string{"English"}, \
                     error);

    ipinfo::print_info(info);

    return int{0};
}
