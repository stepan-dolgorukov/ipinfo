#!/bin/bash

make copy --makefile=Makefile &&
make --makefile=Makefile \
     --always-make
