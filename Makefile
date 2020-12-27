.PHONY: clean

DEBUG_MODE := 1

OBJ_DIR     := obj
SRC_DIR     := src
LIB_DIR     := lib
INCLUDE_DIR := include
TARGET_DIR := target

TARGET :=  $(TARGET_DIR)/libipinfo.so

RM  := /usr/bin/rm
CXX := /usr/bin/g++

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

LDFLAGS := -L$(LIB_DIR) \
           -Wl,-rpath=lib

LDLIBS := -l:libcjson.so.1.7.14 \
          -l:libcurl.so.7.74.0

$(TARGET): $(OBJ_DIR)/ipinfo_informer.o \
		   $(OBJ_DIR)/ipinfo_parser.o \
		   $(OBJ_DIR)/ipinfo_requester.o \
		   $(OBJ_DIR)/ipinfo_utiler.o
	$(CXX) \
	-shared \
	$(LDFLAGS) \
	$^ \
	-o $@ \
	$(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/ipinfo/%.cpp
	$(CXX) \
	$(CXXFLAGS) \
	-fPIC \
	-c $< \
	-o $@

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(TARGET)
