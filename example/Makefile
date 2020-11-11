.PHONY: copy \
        clean


DEBUG_MODE := 1

BIN_DIR     := bin
OBJ_DIR     := obj
SRC_DIR     := src
LIB_DIR     := lib
INCLUDE_DIR	:= include


RM := /usr/bin/rm
CP := /usr/bin/cp


CXX := /usr/bin/g++
CXXFLAGS := -std=c++2a \
            -Wall \
            -Wextra \
            -Wpedantic \
            -Wunreachable-code \
            -pipe


ifeq ($(DEBUG_MODE), 1)
    CXXFLAGS += -g3 \
                -O0
else
    CXXFLAGS += -Os \
                -march=native
endif


LDFLAGS := -L$(LIB_DIR) \
           -l:libipinfo.so \
           -l:libcurl.so.4.7.0 \
           -l:libcjson.so.1.7.14 \
           -Wl,-rpath=lib


$(BIN_DIR)/ipinfo: $(OBJ_DIR)/main.o \
                   $(LIB_DIR)/libipinfo.so
	$(CXX) \
	$(LDFLAGS) \
	$? \
	-o $@


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) \
	$(CXXFLAGS) \
	-c $? \
	-o $@


copy:
	$(CP) ../lib/libcjson.so.1                  $(LIB_DIR)
	$(CP) ../lib/libcjson.so.1.7.14             $(LIB_DIR)
	$(CP) ../lib/libcurl.so.4.7.0               $(LIB_DIR)
	$(CP) ../lib/libipinfo.so                   $(LIB_DIR)
	$(CP) ../include/ipinfo/ipinfo.hpp          $(INCLUDE_DIR)/ipinfo
	$(CP) ../include/ipinfo/ipinfo_user.hpp     $(INCLUDE_DIR)/ipinfo
	$(CP) ../include/ipinfo/ipinfo_print.hpp    $(INCLUDE_DIR)/ipinfo
	$(CP) ../include/ipinfo/ipinfo_types.hpp    $(INCLUDE_DIR)/ipinfo
	$(CP) ../include/ipinfo/ipinfo_values.hpp   $(INCLUDE_DIR)/ipinfo


clean:
	$(RM) $(OBJ_DIR)/*.o
