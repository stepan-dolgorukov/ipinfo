.PHONY: prepare, clean

DEBUG_MODE := 1

CURR_D := $(shell pwd)
OBJ_D  := $(CURR_D)/obj
LIB_D  := $(CURR_D)/lib
INCL_D := $(CURR_D)/include

TARG := ipinfo_test

RM    := /usr/bin/rm
CP    := /usr/bin/cp
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test

CXXFLAGS := -std=c++2a \
            -Wall \
            -Wextra \
            -Wpedantic \
            -Wconversion \
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

$(TARG): $(OBJ_D)/test.o
	$(CXX) \
	$(LDFLAGS) \
	$? \
	-o $@ \
	$(LDLIBS)

$(OBJ_D)/%.o: %.cpp
	$(CXX) \
	-I$(INCL_D)/ipinfo \
	$(CXXFLAGS) \
	-c $? \
	-o $@

prepare:
	$(TEST) -d $(OBJ_D) || $(MKDIR) $(OBJ_D)
	$(CP) -r ../lib/ .
	$(CP) -r ../include .
	$(CP) ../target/libipinfo.so $(LIB_D)

clean:
	$(RM) $(OBJ_D)/*.o
	$(RM) $(TARG)
