.PHONY: clean, prepare

DEBUG_MODE := 1

OBJ_DIR     := obj
SRC_DIR     := src
LIB_DIR     := lib
INCLUDE_DIR := include
TARGET_DIR  := target

TARGET :=  $(TARGET_DIR)/libipinfo.so

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

LDFLAGS := -L$(LIB_DIR) \
           -Wl,-rpath=lib

LDLIBS := -l:libcjson.so \
          -l:libcurl.so

ifeq ($(DEBUG_MODE), 1)
    CXXFLAGS += -g3 \
                -O0
else
    CXXFLAGS += -Os \
                -flto \
                -march=native
endif

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

prepare:
	$(TEST) -d $(OBJ_DIR) || $(MKDIR) $(OBJ_DIR)
	$(TEST) -d $(TARGET_DIR) || $(MKDIR) $(TARGET_DIR)

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(TARGET)
