.PHONY: prepare, \
        clean

DEBUG_MODE := 1

CURR_D := $(shell pwd)
OBJ_D  := $(CURR_D)/obj

TARG := ipinfo_test

RM    := /usr/bin/rm
CP    := /usr/bin/cp
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test
ECHO  := /usr/bin/echo

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

$(TARG): $(OBJ_D)/test.o
	@ $(ECHO) "building $(TARG)"
	@ $(CXX) \
	$(LDLIBS) \
	$? \
	-o $@

$(OBJ_D)/%.o:%.cpp
	@ $(ECHO) "compiling $<"
	@ $(CXX) \
	$(CXXFLAGS) \
	-c $< \
	-o $@

prepare:
	@ ($(TEST) -d $(OBJ_D) && \
		$(ECHO) "$(OBJ_D) already exists") || \
		($(ECHO) "creating $(OBJ_D)" && $(MKDIR) $(OBJ_D))

clean:
	@ ($(TEST) -d $(OBJ_D) && \
		$(ECHO) "deleting $(OBJ_D)" && $(RM) -r $(OBJ_D)) || \
		($(ECHO) "$(OBJ_D) doesn't exist")
