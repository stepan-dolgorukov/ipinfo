#!/bin/bash

echo="/usr/bin/echo"
cppcheck="/usr/bin/cppcheck "

check_flags="--std=c++20 \
             --enable=all"

check_platforms="unix32 \
                 unix64"

check_files="src/ipinfo/*cpp include/ipinfo/*hpp"

declare -a colors=(
    "\e[1;32m" # green
    "\e[0m"    # reset
)

for platform in $check_platforms
do
    $echo -e "\e[${colors[0]}Checking for \"$platform\"${colors[1]}:"
    $cppcheck $check_files $check_flags $platform
done
