#!/bin/bash

make="/usr/bin/make"

$make prepare &&
$make --always-make
