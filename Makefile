.PHONY: clean


DEBUG_MODE = 1


OBJ_DIR = 	obj
SRC_DIR = 	src
LIB_DIR = 	lib


CXX = g++
CXXFLAGS = -std=c++2a \
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


LDFLAGS = -lcurl


$(LIB_DIR)/libipinfo.so: $(OBJ_DIR)/cJSON.o \
						 $(OBJ_DIR)/ipinfo.o \
						 $(OBJ_DIR)/ipinfo_extra.o \
						 $(OBJ_DIR)/ipinfo_parsing.o \
						 $(OBJ_DIR)/ipinfo_request.o
	$(CXX) \
	$(OBJ_DIR)/cJSON.o \
	$(OBJ_DIR)/ipinfo.o \
	$(OBJ_DIR)/ipinfo_extra.o \
	$(OBJ_DIR)/ipinfo_parsing.o \
	$(OBJ_DIR)/ipinfo_request.o \
	$(LDFLAGS) \
	-o $(LIB_DIR)/libipinfo.so \
	-shared $(LDFLAGS)


$(OBJ_DIR)/cJSON.o: $(SRC_DIR)/cJSON/cJSON.c
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/cJSON/cJSON.c \
	-o $(OBJ_DIR)/cJSON.o \
	-I $(INCLUDE_DIR)/cJSON


$(OBJ_DIR)/ipinfo.o: $(SRC_DIR)/ipinfo/ipinfo.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo.cpp \
	-o $(OBJ_DIR)/ipinfo.o \
	-I $(INCLUDE_DIR)/ipinfo


$(OBJ_DIR)/ipinfo_extra.o: $(SRC_DIR)/ipinfo/ipinfo_extra.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_extra.cpp \
	-o $(OBJ_DIR)/ipinfo_extra.o \
	-I $(INCLUDE_DIR)/ipinfo


$(OBJ_DIR)/ipinfo_parsing.o: $(SRC_DIR)/ipinfo/ipinfo_parsing.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_parsing.cpp \
	-o $(OBJ_DIR)/ipinfo_parsing.o \
	-I $(INCLUDE_DIR)/ipinfo


$(OBJ_DIR)/ipinfo_request.o: $(SRC_DIR)/ipinfo/ipinfo_request.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
	-c $(SRC_DIR)/ipinfo/ipinfo_request.cpp \
	-o $(OBJ_DIR)/ipinfo_request.o \
	-I $(INCLUDE_DIR)/ipinfo


clean:
	rm $(OBJ_DIR)/*.o