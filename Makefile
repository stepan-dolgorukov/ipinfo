.PHONY: clean


DEBUG_MODE := 1


OBJ_DIR := 	obj
SRC_DIR := 	src
LIB_DIR := 	lib


CXX := g++
CXXFLAGS := -std=c++2a \
			-Wall \
			-Wextra \
			-Wunreachable-code \
			-Wpedantic \
			-pipe


ifeq ($(DEBUG_MODE), 1)
	CXXFLAGS += -g3 \
				-O0
else
	CXXFLAGS += -O2 \
				-march=native
endif


LDFLAGS := -lcurl


$(LIB_DIR)/libipinfo.so: $(OBJ_DIR)/cJSON.o \
						 $(OBJ_DIR)/ipinfo_main.o \
						 $(OBJ_DIR)/ipinfo_util.o \
						 $(OBJ_DIR)/ipinfo_parse.o \
						 $(OBJ_DIR)/ipinfo_request.o
	$(CXX) \
	$(OBJ_DIR)/cJSON.o \
	$(OBJ_DIR)/ipinfo_main.o \
	$(OBJ_DIR)/ipinfo_util.o \
	$(OBJ_DIR)/ipinfo_parse.o \
	$(OBJ_DIR)/ipinfo_request.o \
	$(LDFLAGS) \
	-o $(LIB_DIR)/libipinfo.so \
	-shared $(LDFLAGS)


$(OBJ_DIR)/cJSON.o: $(SRC_DIR)/cJSON/cJSON.c
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/cJSON/cJSON.c \
	-o $(OBJ_DIR)/cJSON.o \
	-I $(INCLUDE_DIR)/cJSON


$(OBJ_DIR)/ipinfo_main.o: $(SRC_DIR)/ipinfo/ipinfo_main.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_main.cpp \
	-o $(OBJ_DIR)/ipinfo_main.o \
	-I $(INCLUDE_DIR)/ipinfo


$(OBJ_DIR)/ipinfo_util.o: $(SRC_DIR)/ipinfo/ipinfo_util.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_util.cpp \
	-o $(OBJ_DIR)/ipinfo_util.o \
	-I $(INCLUDE_DIR)/ipinfo


$(OBJ_DIR)/ipinfo_parse.o: $(SRC_DIR)/ipinfo/ipinfo_parse.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_parse.cpp \
	-o $(OBJ_DIR)/ipinfo_parse.o \
	-I $(INCLUDE_DIR)/ipinfo


$(OBJ_DIR)/ipinfo_request.o: $(SRC_DIR)/ipinfo/ipinfo_request.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_request.cpp \
	-o $(OBJ_DIR)/ipinfo_request.o \
	-I $(INCLUDE_DIR)/ipinfo


clean:
	rm $(OBJ_DIR)/*.o