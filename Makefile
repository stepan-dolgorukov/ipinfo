.PHONY: prepare \
        clean \
        install \
        uninstall

DEBUG_MODE := 1

CURR_DIR    := $(shell pwd)
OBJ_DIR     := $(CURR_DIR)/obj
SRC_DIR     := $(CURR_DIR)/src
INCLUDE_DIR := $(CURR_DIR)/include/ipinfo
TARGET_DIR  := $(CURR_DIR)/target

TARG :=  $(TARGET_DIR)/libipinfo.so

RM    := /usr/bin/rm
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test
CP    := /usr/bin/cp
ECHO  := /usr/bin/echo

PREFIX              ?= /usr/local
INSTALL_LIB_DIR     := $(DESTDIR)$(PREFIX)/lib
INSTALL_INCLUDE_DIR := $(DESTDIR)$(PREFIX)/include/ipinfo

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
                -flto \
                -march=native
endif

$(TARG): $(OBJ_DIR)/ipinfo_informer.o \
         $(OBJ_DIR)/ipinfo_parser.o \
         $(OBJ_DIR)/ipinfo_requester.o \
         $(OBJ_DIR)/ipinfo_utiler.o
	@ $(ECHO) "building $(TARG)"
	@ $(CXX) \
	-shared \
	$^ \
	-o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/ipinfo/%.cpp
	@ $(ECHO) "compiling $<"
	@ $(CXX) \
	-I$(INCLUDE_DIR) \
	$(CXXFLAGS) \
	-fPIC \
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

install: $(TARG)
	@ $(ECHO) "copying $(TARG) to $(INSTALL_LIB_DIR)"
	@ $(CP) $(TARG) $(INSTALL_LIB_DIR)

	@ $(MKDIR) -p $(INSTALL_INCLUDE_DIR)

	@ $(ECHO) "copying $(INCLUDE_DIR)/ipinfo.hpp to $(INSTALL_INCLUDE_DIR)"
	@ $(CP) $(INCLUDE_DIR)/ipinfo.hpp $(INSTALL_INCLUDE_DIR)

	@ $(ECHO) "copying $(INCLUDE_DIR)/ipinfo_types.hpp to $(INSTALL_INCLUDE_DIR)"
	@ $(CP) $(INCLUDE_DIR)/ipinfo_types.hpp $(INSTALL_INCLUDE_DIR)

	@ $(ECHO) "copying $(INCLUDE_DIR)/ipinfo_constants.hpp to $(INSTALL_INCLUDE_DIR)"
	@ $(CP) $(INCLUDE_DIR)/ipinfo_constants.hpp $(INSTALL_INCLUDE_DIR)

	@ $(ECHO) "copying $(INCLUDE_DIR)/ipinfo_informer.hpp to $(INSTALL_INCLUDE_DIR)"
	@ $(CP) $(INCLUDE_DIR)/ipinfo_informer.hpp $(INSTALL_INCLUDE_DIR)

uninstall:
	@ ($(TEST) -e "$(INSTALL_LIB_DIR)/libipinfo.so" && \
		($(ECHO) "removing $(INSTALL_LIB_DIR)/libipinfo.so" && \
		$(RM) "$(INSTALL_LIB_DIR)/libipinfo.so")) || \
		($(ECHO) "$(INSTALL_LIB_DIR)/libipinfo.so doesn't exist")

	@ ($(TEST) -d $(INSTALL_INCLUDE_DIR) && \
		($(ECHO) "removing $(INSTALL_INCLUDE_DIR)" && \
			$(RM) -r $(INSTALL_INCLUDE_DIR)) || \
			($(ECHO) "$(INSTALL_INCLUDE_DIR) doesn't exist"))
