.PHONY: clean


DEBUG_MODE := 1


OBJ_DIR     := obj
SRC_DIR     := src
LIB_DIR     := lib
INCLUDE_DIR := include


TARGET :=  $(LIB_DIR)/libipinfo.so


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
           -l:libcurl.so.4.7.0 \
           -l:libcjson.so.1.7.14 \
           -Wl,-rpath=lib


$(TARGET): $(OBJ_DIR)/ipinfo_main.o \
           $(OBJ_DIR)/ipinfo_parse.o \
           $(OBJ_DIR)/ipinfo_request.o \
           $(OBJ_DIR)/ipinfo_util.o
	$(CXX) \
	$? \
	-fPIC \
	-o $@ \
	-shared \
	$(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/ipinfo/%.cpp
	$(CXX) \
	$(CXXFLAGS) -fPIC \
	-c $< \
	-o $@


clean:
	$(RM) $(OBJ_DIR)/*.o
