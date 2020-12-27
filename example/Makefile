.PHONY: copy \
        clean

DEBUG_MODE := 1

OBJ_DIR     := obj
SRC_DIR     := src
LIB_DIR     := lib
INCLUDE_DIR := include
TARGET_DIR  := target

TARGET := $(TARGET_DIR)/ipinfo_xmpl

RM :=   /usr/bin/rm
CP :=   /usr/bin/cp
CXX :=  /usr/bin/g++

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
                -march=native \
                -flto
endif

LDFLAGS := -L$(LIB_DIR) \
           -l:libipinfo.so \
           -l:libcurl.so.7.74.0 \
           -l:libcjson.so.1.7.14 \
           -Wl,-rpath=lib

$(TARGET): $(OBJ_DIR)/main.o
	$(CXX) \
	$(LDFLAGS) \
	$? \
	-o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) \
	$(CXXFLAGS) \
	-c $? \
	-o $@

copy:
	$(CP) -r ../lib/ .
	$(CP) -r ../include .
	$(CP) ../target/* $(LIB_DIR)


clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(TARGET)
