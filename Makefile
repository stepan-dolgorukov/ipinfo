.PHONY: prepare \
        clean \
        install \
        uninstall

DEBUG_MODE := 1

CURR_D := $(shell pwd)
OBJ_D  := $(CURR_D)/obj
SRC_D  := $(CURR_D)/src
INCL_D := $(CURR_D)/include
TARG_D := $(CURR_D)/target

TARG :=  $(TARG_D)/libipinfo.so

RM    := /usr/bin/rm
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test
CP    := /usr/bin/cp
ECHO  := /usr/bin/echo

INSTALL_LIB_D  := /usr/lib
INSTALL_INCL_D := /usr/include

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

$(TARG): $(OBJ_D)/ipinfo_informer.o \
         $(OBJ_D)/ipinfo_parser.o \
         $(OBJ_D)/ipinfo_requester.o \
         $(OBJ_D)/ipinfo_utiler.o
	@ $(ECHO) "building $(TARG)"
	@ $(CXX) \
	$(LDLIBS) \
	-shared \
	$^ \
	-o $@

$(OBJ_D)/%.o: $(SRC_D)/ipinfo/%.cpp
	@ $(ECHO) "compiling $<"
	@ $(CXX) \
	-I$(INCL_D)/ipinfo \
	$(CXXFLAGS) \
	-fPIC \
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

install: $(TARG)
	@ $(ECHO) "copying $(TARG) to $(INSTALL_LIB_D)"
	@ $(CP) $(TARG) $(INSTALL_LIB_D)

	# !!!
	$(MKDIR) -p $(INSTALL_INCL_D)/ipinfo
	$(CP) $(INCL_D)/ipinfo/ipinfo.hpp $(INSTALL_INCL_D)/ipinfo
	$(CP) $(INCL_D)/ipinfo/ipinfo_types.hpp $(INSTALL_INCL_D)/ipinfo
	$(CP) $(INCL_D)/ipinfo/ipinfo_constants.hpp $(INSTALL_INCL_D)/ipinfo
	$(CP) $(INCL_D)/ipinfo/ipinfo_informer.hpp $(INSTALL_INCL_D)/ipinfo

uninstall:
	@ ($(TEST) -e $(INSTALL_LIB_D)/libipinfo.so && \
		($(ECHO) "remove $(INSTALL_LIB_D)/libipinfo.so" && \
		$(RM) $(INSTALL_LIB_D)/libipinfo.so)) || \
		($(ECHO) "$(INSTALL_LIB_D)/libipinfo.so doesn't exist")

	@ ($(TEST) -d $(INSTALL_INCL_D)/ipinfo && \
		($(ECHO) "remove $(INSTALL_INCL_D)/ipinfo" && \
		$(RM) -r $(INSTALL_INCL_D)/ipinfo)) || \
		($(ECHO) "$(INSTALL_INCL_D)/ipinfo doesn't exist")
