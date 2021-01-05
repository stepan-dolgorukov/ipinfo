.PHONY: prepare, \
		clean

DEBUG_MODE := 1

CURR_D := $(shell pwd)
OBJ_D  := $(CURR_D)/obj
SRC_D  := $(CURR_D)/src
INCL_D := $(CURR_D)/include
TARG_D := $(CURR_D)/target

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

LDLIBS := -lipinfo

$(TARG): $(OBJ_D)/main.o
	$(CXX) \
	$(LDLIBS) \
	$? \
	-o $@ \
	$(LDLIBS)

$(OBJ_D)/%.o: $(SRC_D)/%.cpp
	$(CXX) \
	$(CXXFLAGS) \
	-c $? \
	-o $@

prepare:
	# TODO: check existing
	$(TEST) -d $(OBJ_D) || $(MKDIR) $(OBJ_D)
	$(TEST) -d $(TARG_D) || $(MKDIR) $(TARG_D)

clean:
	# TODO: check existing
	$(RM) $(OBJ_D)/*o
	$(RM) $(TARG)
