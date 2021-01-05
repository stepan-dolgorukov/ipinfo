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

$(TARG): $(OBJ_D)/main.o
	@ $(ECHO) "building $(TARG)"
	@ $(CXX) \
	$(LDLIBS) \
	$? \
	-o $@

$(OBJ_D)/%.o: $(SRC_D)/%.cpp
	@ $(ECHO) "compiling $<"
	@ $(CXX) \
	$(CXXFLAGS) \
	-c $< \
	-o $@

prepare:
	@ ($(TEST) -d $(OBJ_D) && \
		$(ECHO) "$(OBJ_D) already exists") || \
		($(ECHO) "creating $(OBJ_D)" && $(MKDIR) $(OBJ_D))

	@ $(TEST) -d $(TARG_D) && \
		$(ECHO) "$(TARG_D) already exists" || \
		($(ECHO) "creating $(TARG_D)" && $(MKDIR) $(TARG_D))

clean:
	@ ($(TEST) -d $(TARG_D) && \
		$(ECHO) "deleting $(TARG_D)" && $(RM) -r $(TARG_D)) || \
		($(ECHO) "$(TARG_D) doesn't exist")

	@ ($(TEST) -d $(OBJ_D) && \
		$(ECHO) "deleting $(OBJ_D)" && $(RM) -r $(OBJ_D)) || \
		($(ECHO) "$(OBJ_D) doesn't exist")
