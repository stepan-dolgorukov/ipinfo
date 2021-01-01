#!/bin/bash

echo="/usr/bin/echo"
cppcheck="/usr/bin/cppcheck "

check_flags="--std=c++20 \
             --enable=all"

check_platforms="unix32 \
                 unix64"

check_files="src/ipinfo/*cpp include/ipinfo/*hpp"

for platform in $check_platforms
do
    $echo -e "\e[1;36mChecking for \"$platform\"...\e[0m"
    $cppcheck $check_files $check_flags $platform
done
