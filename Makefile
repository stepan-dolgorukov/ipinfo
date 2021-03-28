.PHONY:
	prepare \
	clean \
	install \
	uninstall

PROJECT_NAME := ipinfo
DEBUG_MODE := 1

OBJ_DIR := obj
SRC_DIR := src
INCLUDE_DIR := include
TARGET_DIR := target

MAJOR_LIB_VER := 1
MINOR_LIB_VER := 0
PATCH_LIB_VER := 0

FULL_LIB_VER := $(MAJOR_LIB_VER).$(MINOR_LIB_VER).$(PATCH_LIB_VER)

LIB_FILE_EXTENSION := so
LIB_FILE_NAME_NO_VER := lib$(PROJECT_NAME).$(LIB_FILE_EXTENSION)
TARGET := $(TARGET_DIR)/$(LIB_FILE_NAME_NO_VER).$(FULL_LIB_VER)

SRCS := \
  $(shell find $(SRC_DIR)/ipinfo \
  -iname "*.cpp" \
  -type f \
  -printf "%P ")

OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

PREFIX ?= /usr/local
INSTALL_LIB_DIR := $(DESTDIR)$(PREFIX)/lib
INSTALL_INCLUDE_DIR := $(DESTDIR)$(PREFIX)/include/ipinfo

INSTALL_LIB_FILE_RIGHTS := 755
INSTALL_HEADER_FILES_RIGHTS := 644

INSTALL_LIB_FILE := $(TARGET)
UNINSTALL_LIB_FILE := $(INSTALL_LIB_DIR)/$(shell basename $(INSTALL_LIB_FILE))

# There are only headers needed
# by user will be installed.

INSTALL_HEADER_FILES := \
  $(shell find $(INCLUDE_DIR)/ipinfo \
  \( ! -name "*requester*" \) -and \
  \( ! -name "*parser*" \) -and \
  \( ! -name "*utiler*" \) -and \
  -iname "*.hpp" -type f -printf "%p ")

CXX := g++
CXXFLAGS := \
  -std=c++20 \
  -Wall \
  -Wextra \
  -Wpedantic \
  -Wconversion \
  -Wunreachable-code \
  -Wsign-conversion \
  -Wlogical-op \
  -pipe

ifeq ($(DEBUG_MODE), 1)
	CXXFLAGS += -g3
	CXXFLAGS += -O0
	CXXFLAGS += -DIPINFO_DEBUG_MODE
else
	CXXFLAGS += -Os
	CXXFLAGS += -flto
	CXXFLAGS += -march=native
endif

LDFLAGS := \
  -Wl,-rpath=$(PREFIX)/lib \
  -Wl,-rpath=./lib \
  -Wl,-rpath=/usr/lib \
  -Wl,-rpath=/usr/local/lib

LDLIBS := \
  -lcjson \
  -lcpr

create_dir = @ (test -d $(1)) || mkdir -p $(1)
remove_dir = @ (test -d $(1) && rm -r $(1)) || true

create_link = @ ln -sf $(1) $(2)
remove_link = @ (test -L $(1) && unlink $(1)) || true

remove_file = @ (test -f $(1) && rm $(1)) || true

all: build

build: prepare $(TARGET)
	$(info build of the $(shell basename $(TARGET)) is completed)

$(TARGET): $(OBJS)
	@ $(foreach obj, \
		$(shell find $(OBJ_DIR) -iname "*.cpp.o" -type f), \
		$(info link $(shell basename $(obj))))

	@ $(CXX) \
	$(LDFLAGS) \
	$(LDLIBS) \
	-shared \
	$^ \
	-o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/$(PROJECT_NAME)/%.cpp
	$(info compile $(shell basename $<))

	@ $(CXX) \
	$(CXXFLAGS) \
	-I$(INCLUDE_DIR) \
	-fPIC \
	-c $< \
	-o $@

prepare:
	$(info create build directories)
	$(call create_dir,$(OBJ_DIR))
	$(call create_dir,$(TARGET_DIR))

clean:
	$(info remove build diectories)
	$(call remove_dir,$(OBJ_DIR))
	$(call remove_dir,$(TARGET_DIR))

install: build
	$(info create installation folders)
	$(call create_dir,$(INSTALL_LIB_DIR))
	$(call create_dir,$(INSTALL_INCLUDE_DIR))

	$(info install library to $(INSTALL_LIB_DIR))
	@ install -Dm$(INSTALL_LIB_FILE_RIGHTS) \
		$(INSTALL_LIB_FILE) \
		$(INSTALL_LIB_DIR)

	$(info install headers to $(INSTALL_INCLUDE_DIR))
	@ $(foreach header,\
		$(INSTALL_HEADER_FILES),\
		install -Dm=$(INSTALL_HEADER_FILES_RIGHTS) \
			$(header) \
			$(INSTALL_INCLUDE_DIR); )

	$(info create soft links in $(INSTALL_LIB_DIR))
	$(call create_link,\
		$(INSTALL_LIB_DIR)/$(LIB_FILE_NAME_NO_VER).$(FULL_LIB_VER),\
		$(INSTALL_LIB_DIR)/$(LIB_FILE_NAME_NO_VER).$(MAJOR_LIB_VER))

	$(call create_link,\
		$(INSTALL_LIB_DIR)/$(LIB_FILE_NAME_NO_VER).$(MAJOR_LIB_VER),\
		$(INSTALL_LIB_DIR)/$(LIB_FILE_NAME_NO_VER))

uninstall:
	$(info remove library: $(UNINSTALL_LIB_FILE))
	$(call remove_file,$(UNINSTALL_LIB_FILE))

	$(info remove headers directory: $(INSTALL_INCLUDE_DIR))
	$(call remove_dir,$(INSTALL_INCLUDE_DIR))

	$(info remove soft links from $(INSTALL_LIB_DIR))
	$(call remove_link,\
		$(INSTALL_LIB_DIR)/$(LIB_FILE_NAME_NO_VER).$(MAJOR_LIB_VER))

	$(call remove_link,$(INSTALL_LIB_DIR)/$(LIB_FILE_NAME_NO_VER))
