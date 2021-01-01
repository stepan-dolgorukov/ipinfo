.PHONY: prepare, clean

DEBUG_MODE := 1

OBJ_DIR     := obj
LIB_DIR     := lib
INCLUDE_DIR := include

TARGET := ipinfo_test

RM    := /usr/bin/rm
CP    := /usr/bin/cp
CXX   := /usr/bin/g++
MKDIR := /usr/bin/mkdir
TEST  := /usr/bin/test

CXXFLAGS := -std=c++2a \
            -Wall \
            -Wextra \
            -Wpedantic \
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

LDFLAGS := -L$(LIB_DIR) \
           -Wl,-rpath=lib

LDLIBS := -l:libcurl.so.7.74.0 \
          -l:libcjson.so.1.7.14 \
          -l:libipinfo.so

$(TARGET): $(OBJ_DIR)/test.o
	$(CXX) \
	$(LDFLAGS) \
	$? \
	-o $@ \
	$(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) \
	$(CXXFLAGS) \
	-c $? \
	-o $@

prepare:
	$(TEST) -d $(OBJ_DIR) || $(MKDIR) $(OBJ_DIR)
	$(CP) -r ../lib/ .
	$(CP) -r ../include .
	$(CP) ../target/* $(LIB_DIR)

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(TARGET)
