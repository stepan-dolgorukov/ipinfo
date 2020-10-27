#include "../include/ipinfo/ipinfo.hpp"


int main(void)
{
    ipinfo::info_t info{};
    ipinfo::error_t error{};
    
    ipinfo::get_info(info, {"8.8.8.8"}, {"English"}, error);
    ipinfo::print_info(info);
    
    return (0);
}