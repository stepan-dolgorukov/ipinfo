#/usr/bin/bash

make="/usr/bin/make"
nproc="/usr/bin/nproc"
let "n=$(nproc) * 2"

$make --makefile=Makefile prepare &&
$make --makefile=Makefile -j$n
