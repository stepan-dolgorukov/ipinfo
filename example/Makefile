.PHONY:
	prepare \
	clean

PROJECT := ipinfo
EXE_BIN := $(PROJECT)_xmpl

DEBUG_MODE := 1

OBJ_DIR     := ./obj
SRC_DIR     := ./src
INCLUDE_DIR := ./include
TARGET_DIR  := ./target

TARG := $(TARGET_DIR)/$(EXE_BIN)
SRCS := $(shell find $(SRC_DIR) -name "*.cpp" -type f -printf "%P ")
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

RM    := rm
CP    := cp
CXX   := g++
MKDIR := mkdir
TEST  := test
ECHO  := echo

CXXFLAGS := \
	-std=c++2a         \
	-Wall              \
	-Wextra            \
	-Wpedantic         \
	-Wconversion       \
	-Wunreachable-code \
	-Wsign-conversion  \
	-Wlogical-op       \
	-pipe

ifeq ($(DEBUG_MODE), 1)
	CXXFLAGS += -g3 -O0
else
	CXXFLAGS += -Os -flto -march=native
endif

LDFLAGS := \
	-Wl,-rpath=$(PREFIX)/lib   \
	-Wl,-rpath=./lib           \
	-Wl,-rpath=/usr/lib        \
	-Wl,-rpath=/usr/local/lib

LDLIBS := \
	-lipinfo \
	-lfmt

$(TARG): $(OBJS)
	@ $(ECHO) "linking objects"
	@ $(CXX) \
	$(LDFLAGS) \
	$(LDLIBS) \
	$? \
	-o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@ $(ECHO) "compiling $<"
	@ $(CXX) \
	$(CXXFLAGS) \
	-I$(INCLUDE_DIR) \
	-c $< \
	-o $@

prepare:
	@ ($(TEST) -d $(OBJ_DIR) && \
		$(ECHO) "$(OBJ_DIR) already exists") || \
		($(ECHO) "creating $(OBJ_DIR)" && $(MKDIR) $(OBJ_DIR))

	@ $(TEST) -d $(TARGET_DIR) && \
		$(ECHO) "$(TARGET_DIR) already exists" || \
		($(ECHO) "creating $(TARGET_DIR)" && $(MKDIR) $(TARGET_DIR))

clean:
	@ ($(TEST) -d $(TARGET_DIR) && \
		$(ECHO) "deleting $(TARGET_DIR)" && $(RM) -r $(TARGET_DIR)) || \
		($(ECHO) "$(TARGET_DIR) doesn't exist")

	@ ($(TEST) -d $(OBJ_DIR) && \
		$(ECHO) "deleting $(OBJ_DIR)" && $(RM) -r $(OBJ_DIR)) || \
		($(ECHO) "$(OBJ_DIR) doesn't exist")
