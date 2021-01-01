#!/bin/bash

make="/usr/bin/make"
echo="/usr/bin/echo"

ipinfo_test="./ipinfo_test"

declare -a colors=(
    "\e[1;31m" # light red
    "\e[0m"    # reset
)

declare -a test_bundles=(
    "8.8.8.8 russian 1"
    "1.1.1.1 english 2"
    "256.256.256.256 vim 42"
    "777.3.122 english 1"
    "5.5.5.5 chinese 0"
)

$make prepare &&
$make &&

for bundle in "${test_bundles[@]}"
do
    $echo -e "${colors[0]}\"$bundle\"${colors[1]}:"
    $ipinfo_test $bundle
done
