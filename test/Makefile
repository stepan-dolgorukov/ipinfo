.PHONY: prepare, \
        clean

DEBUG_MODE := 1

CURR_DIR    := $(shell pwd)
OBJ_DIR     := $(CURR_DIR)/obj
SRC_DIR     := $(CURR_DIR)/src
INCLUDE_DIR := $(CURR_DIR)/include
TARGET_DIR  := $(CURR_DIR)/target

TARG := $(TARGET_DIR)/ipinfo_test

RM    := /usr/bin/rm
CP    := /usr/bin/cp
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test
ECHO  := /usr/bin/echo

CXXFLAGS := -std=c++20 \
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

LDFLAGS := -Wl,-rpath=/usr/local/lib
LDLIBS := -lipinfo -lfmt

$(TARG): $(OBJ_DIR)/test.o
	@ $(ECHO) "building $(TARG)"
	@ $(CXX) \
	$(LDFLAGS) \
	$(LDLIBS) \
	$? \
	-o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@ $(ECHO) "compiling $<"
	@ $(CXX) \
	$(CXXFLAGS) \
	-c $< \
	-o $@

prepare:
	@ ($(TEST) -d $(OBJ_DIR) && \
		$(ECHO) "$(OBJ_DIR) already exists") || \
		($(ECHO) "creating $(OBJ_DIR)" && $(MKDIR) $(OBJ_DIR))

	@ $(TEST) -d $(TARGET_DIR) && \
		$(ECHO) "$(TARGET_DIR) already exists" || \
		($(ECHO) "creating $(TARGET_DIR)" && $(MKDIR) $(TARGET_DIR))

clean:
	@ ($(TEST) -d $(TARGET_DIR) && \
		$(ECHO) "deleting $(TARGET_DIR)" && $(RM) -r $(TARGET_DIR)) || \
		($(ECHO) "$(TARGET_DIR) doesn't exist")

	@ ($(TEST) -d $(OBJ_DIR) && \
		$(ECHO) "deleting $(OBJ_DIR)" && $(RM) -r $(OBJ_DIR)) || \
		($(ECHO) "$(OBJ_DIR) doesn't exist")
