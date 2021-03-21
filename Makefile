.PHONY:
	prepare \
	clean \
	install \
	uninstall

PROJECT := ipinfo
DEBUG_MODE := 1

OBJ_DIR := obj
SRC_DIR := src
INCLUDE_DIR := include
TARGET_DIR := target
LIB_EXTENSION := so

TARG := $(TARGET_DIR)/lib$(PROJECT).$(LIB_EXTENSION)

SRCS := \
  $(shell find $(SRC_DIR)/ipinfo \
  -iname "*.cpp" \
  -type f \
  -printf "%P ")

OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

PREFIX ?= /usr/local
INSTALL_LIB_DIR := $(DESTDIR)$(PREFIX)/lib
INSTALL_INCLUDE_DIR := $(DESTDIR)$(PREFIX)/include/ipinfo

INSTALL_LIB_RIGHTS := 755
INSTALL_INCLUDE_RIGHTS := 644

INSTALL_LIB := $(TARG)
UNINSTALL_LIB := $(INSTALL_LIB_DIR)/$(shell basename $(INSTALL_LIB))

# There are only headers needed
# by user will be installed.

INSTALL_HDRS := \
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
	CXXFLAGS += -g3 -O0 -DDEBUG_MODE
else
	CXXFLAGS += -Os -flto -march=native
endif

LDFLAGS := \
  -Wl,-rpath=$(PREFIX)/lib \
  -Wl,-rpath=./lib \
  -Wl,-rpath=/usr/lib \
  -Wl,-rpath=/usr/local/lib

LDLIBS := \
  -lcjson \
  -lcpr

define chq_dir
@ (test -d $(1) \
	&& printf "%s dir alr exists\n" $(1)) \
	|| (printf "cr8 %s dir\n" $(1) && \
		mkdir $(1))
endef

define rmv_dir
@ (test -d $(1) \
	&& (printf "rmv %s\n" $(1) && \
		rm -r $(1))) \
	|| (printf "%s\n doesnt' exist" $(1))
endef

all: build

build: prepare $(TARG)
	@ printf "bld %s\n" $(TARG)

$(TARG): $(OBJS)
	@ $(foreach obj, \
		$(shell find $(OBJ_DIR) -iname "*.cpp.o" -type f), \
		printf "lnk %s\n" $(obj); )

	@ $(CXX) \
	$(LDFLAGS) \
	$(LDLIBS) \
	-shared \
	$^ \
	-o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/$(PROJECT)/%.cpp
	@ printf "cmpl %s\n" $<

	@ $(CXX) \
	$(CXXFLAGS) \
	-I$(INCLUDE_DIR) \
	-fPIC \
	-c $< \
	-o $@

prepare:
	$(call chq_dir,$(OBJ_DIR))
	$(call chq_dir,$(TARGET_DIR))

clean:
	$(call rmv_dir,$(OBJ_DIR))
	$(call rmv_dir,$(TARGET_DIR))

install: build
	@ mkdir -p $(INSTALL_LIB_DIR)
	@ mkdir -p $(INSTALL_INCLUDE_DIR)

	@ printf "%s\n" "installation..."

	@ printf "dir: %s\n" $(INSTALL_LIB_DIR)
	@ printf "\t%s\n" $(shell basename $(INSTALL_LIB))
	@ install \
		-Dm$(INSTALL_LIB_RIGHTS) \
		$(INSTALL_LIB) \
		$(INSTALL_LIB_DIR)

	@ printf "dir: %s\n" $(INSTALL_INCLUDE_DIR)
	@ $(foreach header, \
		$(INSTALL_HDRS), \
		printf "\t%s\n" $(shell basename $(header)) && \
		install \
			-Dm=$(INSTALL_INCLUDE_RIGHTS) \
			$(header) \
			$(INSTALL_INCLUDE_DIR); )

uninstall:
	@ printf "%s\n" "deinstallation..."

	@ (test -f $(UNINSTALL_LIB) \
		&& (printf "rmv %s\n" $(UNINSTALL_LIB) && \
			rm $(UNINSTALL_LIB))) \
		|| (printf "%s doesn't exist\n" $(UNINSTALL_LIB))

	@ (test -d $(INSTALL_INCLUDE_DIR) \
		&& (printf "rmv %s\n" $(INSTALL_INCLUDE_DIR) && \
			rm -r $(INSTALL_INCLUDE_DIR))) \
		|| (printf "%s doesn't exist\n" $(INSTALL_INCLUDE_DIR))
