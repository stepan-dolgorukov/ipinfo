.PHONY: clean, \
        prepare

DEBUG_MODE := 1

CURR_D := $(shell pwd)
OBJ_D  := $(CURR_D)/obj
SRC_D  := $(CURR_D)/src
LIB_D  := $(CURR_D)/lib
INCL_D := $(CURR_D)/include
TARG_D := $(CURR_D)/target

TARG :=  $(TARG_D)/libipinfo.so

RM    := /usr/bin/rm
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

LDFLAGS := -L$(LIB_D) \
           -Wl,-rpath=$(LIB_D)

LDLIBS := -l:libcjson.so.1.7.14 \
          -l:libcurl.so.7.74.0

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
	$(CXX) \
	$(LDFLAGS) \
	-shared \
	$^ \
	-o $@ \
	$(LDLIBS)

$(OBJ_D)/%.o: $(SRC_D)/ipinfo/%.cpp
	$(CXX) \
	-I$(INCL_D)/ipinfo \
	$(CXXFLAGS) \
	-fPIC \
	-c $< \
	-o $@

prepare:
	$(TEST) -d $(OBJ_D) || $(MKDIR) $(OBJ_D)
	$(TEST) -d $(TARG_DIR) || $(MKDIR) $(TARG_DIR)

clean:
	$(RM) $(OBJ_D)/*.o
	$(RM) $(TARG)
