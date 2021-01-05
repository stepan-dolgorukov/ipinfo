#!/bin/bash

make="/usr/bin/make"

$make --makefile=Makefile prepare &&
$make --makefile=Makefile --always-make
