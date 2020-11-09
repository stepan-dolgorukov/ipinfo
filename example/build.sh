#!/bin/bash


(make copy --makefile=Makefile) && \
(make --jobs=8 --always-make --makefile=Makefile)
