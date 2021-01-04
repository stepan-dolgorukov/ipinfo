.PHONY: prepare, \
        clean

DEBUG_MODE := 1

PWD    := $(shell pwd)
OBJ_D  := $(PWD)/obj
SRC_D  := $(PWD)/src
LIB_D  := $(PWD)/lib
INCL_D := $(PWD)/include
TARG_D := $(PWD)/target

TARG := $(TARG_D)/ipinfo_xmpl

RM    := /usr/bin/rm
CP    := /usr/bin/cp
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test

CXXFLAGS := -std=c++2a \
            -Wall \
            -Wextra \
            -Wpedantic \
            -Wunreachable-code \
            -Wsign-conversion \
            -Wlogical-op \
            -pipe

ifeq ($(DEBUG_MODE), 1)
    CXXFLAGS += -g3 \
                -O0
else
    CXXFLAGS += -Os \
                -march=native \
                -flto
endif

 LDFLAGS := -L$(LIB_D) \
            -Wl,-rpath=$(LIB_D)

LDLIBS := -l:libcurl.so.7.74.0 \
          -l:libcjson.so.1.7.14 \
          -l:libipinfo.so

$(TARG): $(OBJ_D)/main.o
	$(CXX) \
	$(LDFLAGS) \
	$? \
	-o $@ \
	$(LDLIBS)

$(OBJ_D)/%.o: $(SRC_D)/%.cpp
	$(CXX) \
	-I$(INCL_D) \
	$(CXXFLAGS) \
	-c $? \
	-o $@

prepare:
	$(TEST) -d $(OBJ_D) || $(MKDIR) $(OBJ_D)
	$(TEST) -d $(TARG_D) || $(MKDIR) $(TARG_D)
	$(CP) -r ../lib/ .
	$(CP) -r ../include .
	$(CP) ../target/libipinfo.so $(LIB_D)

clean:
	$(RM) $(OBJ_D)/*.o
	$(RM) $(TARG)
