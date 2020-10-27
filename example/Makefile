.PHONY: copy clean


DEBUG_MODE = 1


BIN_DIR :=		bin
OBJ_DIR :=		obj
SRC_DIR :=		src
LIB_DIR :=		lib
INCLUDE_DIR :=	include


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


LDFLAGS := -L$(LIB_DIR) \
			-lipinfo \
			-Wl,-rpath=lib


$(BIN)/ipinfo: $(OBJ_DIR)/main.o \
			   $(LIB_DIR)/libipinfo.so
	$(CXX) \
	$(LDFLAGS) \
	$(OBJ_DIR)/main.o \
	-o $(BIN_DIR)/ipinfo


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) \
	$(CXXFLAGS) \
	-c $(SRC_DIR)/main.cpp \
	-o $(OBJ_DIR)/main.o


copy:
	# copying library and header files \
	# from project directory
	cp ../lib/libipinfo.so $(LIB_DIR)
	cp ../include/ipinfo/ipinfo.hpp $(INCLUDE_DIR)/ipinfo
	cp ../include/ipinfo/ipinfo_user.hpp $(INCLUDE_DIR)/ipinfo
	cp ../include/ipinfo/ipinfo_print.hpp $(INCLUDE_DIR)/ipinfo
	cp ../include/ipinfo/ipinfo_types.hpp $(INCLUDE_DIR)/ipinfo
	cp ../include/ipinfo/ipinfo_values.hpp $(INCLUDE_DIR)/ipinfo


clean:
	rm $(OBJ_DIR)/*.o