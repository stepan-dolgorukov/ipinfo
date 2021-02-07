.PHONY:
	prepare   \
	clean     \
	install   \
	uninstall

PROJECT    := ipinfo
DEBUG_MODE := 1

OBJ_DIR     := obj
SRC_DIR     := src
INCLUDE_DIR := include
TARGET_DIR  := target

TARG := $(TARGET_DIR)/lib$(PROJECT).so
SRCS := $(shell find $(SRC_DIR)/ipinfo -name "*.cpp" \
                                       -type f       \
                                       -printf "%P ")
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

RM    := rm
CXX   := g++
MKDIR := mkdir
TEST  := test
CP    := cp
ECHO  := echo

PREFIX              ?= /usr/local
INSTALL_LIB_DIR     := $(DESTDIR)$(PREFIX)/lib
INSTALL_INCLUDE_DIR := $(DESTDIR)$(PREFIX)/include/ipinfo

# There are only headers needed by user will be installed.
INSTALL_HDRS := \
    $(shell find $(INCLUDE_DIR)/ipinfo        \
             \( ! -name "*requester*" \) -and \
             \( ! -name "*parser*" \)    -and \
             \( ! -name "*utiler*" \)         \
                  -name "*.hpp"               \
                  -type f                     \
                  -printf "%p ")
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
    CXXFLAGS += -g3 \
                -O0
else
    CXXFLAGS += -Os   \
                -flto \
                -march=native
endif

LDFLAGS := \
    -Wl,-rpath=$(PREFIX)/lib   \
    -Wl,-rpath=./lib           \
    -Wl,-rpath=/usr/lib        \
    -Wl,-rpath=/usr/local/lib

LDLIBS := \
   -lcjson \
   -lcpr

all: prepare $(TARG)

$(TARG): $(OBJS)
	@ $(foreach obj,                                    \
      $(shell find $(OBJ_DIR) -name "*.cpp.o" -type f), \
      $(ECHO) "LNK" $(obj); )

	@ $(CXX)   \
    $(LDFLAGS) \
    $(LDLIBS)  \
    -shared    \
    $^         \
    -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/$(PROJECT)/%.cpp
	@ $(ECHO) "CMP $<"

	@ $(CXX)         \
    $(CXXFLAGS)      \
    -I$(INCLUDE_DIR) \
    -fPIC            \
    -c $<            \
    -o $@

prepare:
	@ ($(TEST) "-d" $(OBJ_DIR)                    \
      && $(ECHO) \"$(OBJ_DIR)\" "already exists") \
      || ($(ECHO) "CRT" \"$(OBJ_DIR)\" && $(MKDIR) $(OBJ_DIR))

	@ ($(TEST) "-d" $(TARGET_DIR)                    \
      && $(ECHO) \"$(TARGET_DIR)\" "already exists") \
      || ($(ECHO) "CRT" \"$(TARGET_DIR)\" && $(MKDIR) $(TARGET_DIR))

clean:
	@ ($(TEST) "-d" $(TARGET_DIR)            \
       && ($(ECHO) "RM" \"$(TARGET_DIR)\" && \
           $(RM) "-r" $(TARGET_DIR)))        \
       || ($(ECHO) \"$(TARGET_DIR)\" "doesn't exist")

	@ ($(TEST) "-d" $(OBJ_DIR)            \
       && ($(ECHO) "RM" \"$(OBJ_DIR)\" && \
           $(RM) -r $(OBJ_DIR)))          \
       || ($(ECHO) \"$(OBJ_DIR)\" "doesn't exist")

install: $(TARG)
	@ $(MKDIR) -p $(INSTALL_LIB_DIR)
	@ $(MKDIR) -p $(INSTALL_INCLUDE_DIR)

	@ $(ECHO) "CP" $(TARG) "->" $(INSTALL_LIB_DIR)
	@ $(CP) $(TARG) $(INSTALL_LIB_DIR)

	@ $(foreach header, \
      $(INSTALL_HDRS),  \
      $(ECHO) "CP" $(header) "->" $(INSTALL_INCLUDE_DIR) && \
      $(CP) $(header) $(INSTALL_INCLUDE_DIR); )

uninstall:
	@ ($(TEST) "-e" $(INSTALL_LIB_DIR)"/lib$(PROJECT).so"      \
       && ($(ECHO) "RM $(INSTALL_LIB_DIR)/lib$(PROJECT).so" && \
           $(RM) "$(INSTALL_LIB_DIR)/lib$(PROJECT).so"))       \
       || ($(ECHO) "$(INSTALL_LIB_DIR)/lib$(PROJECT).so doesn't exist")

	@ ($(TEST) "-d" $(INSTALL_INCLUDE_DIR)        \
       && ($(ECHO) "RM" $(INSTALL_INCLUDE_DIR) && \
           $(RM) "-r" $(INSTALL_INCLUDE_DIR)))    \
       || ($(ECHO) $(INSTALL_INCLUDE_DIR) "doesn't exist")
