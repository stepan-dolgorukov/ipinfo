.PHONY: clean


DEBUG_MODE := 1


OBJ_DIR := obj
SRC_DIR := src
LIB_DIR := lib
INCLUDE_DIR := include


RM := /usr/bin/rm


CXX := /usr/bin/g++
CXXFLAGS := -std=c++2a \
            -Wall \
            -Wextra \
            -Wpedantic \
            -Wunreachable-code \
            -pipe \


ifeq ($(DEBUG_MODE), 1)
    CXXFLAGS += -g3 \
                -O0
else
    CXXFLAGS += -Os \
                -march=native
endif


LDFLAGS := -L$(LIB_DIR) \
           -l:libcurl.so.4.7.0 \
           -l:libcjson.so.1.7.14 \
           -Wl,-rpath=lib


$(LIB_DIR)/libipinfo.so: $(OBJ_DIR)/ipinfo_main.o \
                         $(OBJ_DIR)/ipinfo_parse.o \
                         $(OBJ_DIR)/ipinfo_util.o \
                         $(OBJ_DIR)/ipinfo_request.o
	$(CXX) \
	$? \
	-o $@ \
	-shared \
	$(LDFLAGS)


$(OBJ_DIR)/cJSON.o: $(SRC_DIR)/cJSON/cJSON.c
	$(CXX) \
	$(CXXFLAGS) -fPIC \
	-c $? \
	-o $@ \


$(OBJ_DIR)/ipinfo_main.o: $(SRC_DIR)/ipinfo/ipinfo_main.cpp
	$(CXX) \
	$(CXXFLAGS) -fPIC \
	-c $? \
	-o $@


$(OBJ_DIR)/ipinfo_parse.o: $(SRC_DIR)/ipinfo/ipinfo_parse.cpp
	$(CXX) \
	$(CXXFLAGS) -fPIC \
	-c $? \
	-o $@


$(OBJ_DIR)/ipinfo_request.o: $(SRC_DIR)/ipinfo/ipinfo_request.cpp
	$(CXX) \
	$(CXXFLAGS) -fPIC \
	-c $? \
	-o $@


$(OBJ_DIR)/ipinfo_util.o: $(SRC_DIR)/ipinfo/ipinfo_util.cpp
	$(CXX) \
	$(CXXFLAGS) -fPIC \
	-c $? \
	-o $@


clean:
	$(RM) $(OBJ_DIR)/*.o
