#!/bin/bash

(make copy) &&
(make --jobs=4 --always-make --makefile=Makefile)