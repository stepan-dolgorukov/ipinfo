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

TARG := $(TARGET_DIR)/lib$(PROJECT).so
SRCS := \
  $(shell find $(SRC_DIR)/ipinfo \
  -iname "*.cpp" \
  -type f \
  -printf "%P ")

OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

PREFIX ?= /usr/local
INSTALL_LIB_DIR := $(DESTDIR)$(PREFIX)/lib
INSTALL_INCLUDE_DIR := $(DESTDIR)$(PREFIX)/include/ipinfo

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
	&& echo \"$(1)\" "alr exists") \
	|| (echo "cr8" \"$(1)\" && mkdir $(1))
endef

define rmv_dir
@ (test -d $(1) \
	&& (echo "rmv" \"$(1)\" && rm -r $(1))) \
	|| (echo \"$(1)\" "doesn't exist")
endef

all: prepare $(TARG)
	@ echo "bld" $(TARG)

$(TARG): $(OBJS)
	@ $(foreach obj, \
		$(shell find $(OBJ_DIR) -iname "*.cpp.o" -type f), \
		echo "lnk" $(obj); )

	@ $(CXX) \
	$(LDFLAGS) \
	$(LDLIBS) \
	-shared \
	$^ \
	-o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/$(PROJECT)/%.cpp
	@ echo "cmpl $<"

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

install: $(TARG)
	@ mkdir -p $(INSTALL_LIB_DIR)
	@ mkdir -p $(INSTALL_INCLUDE_DIR)

	@ echo "cp" $(TARG) "to" $(INSTALL_LIB_DIR)
	@ cp $(TARG) $(INSTALL_LIB_DIR)

	@ $(foreach header, \
		$(INSTALL_HDRS), \
		echo "cp" $(header) "to" $(INSTALL_INCLUDE_DIR) && \
		cp $(header) $(INSTALL_INCLUDE_DIR); )

uninstall:
	@ (test -e "$(INSTALL_LIB_DIR)/lib$(PROJECT).so" \
		&& (echo "rmv $(INSTALL_LIB_DIR)/lib$(PROJECT).so" && \
			$(RM) "$(INSTALL_LIB_DIR)/lib$(PROJECT).so")) \
		|| (echo "$(INSTALL_LIB_DIR)/lib$(PROJECT).so doesn't exist")

	@ (test -d $(INSTALL_INCLUDE_DIR) \
		&& (echo "rmv $(INSTALL_INCLUDE_DIR)" && \
			$(RM) -r $(INSTALL_INCLUDE_DIR))) \
		|| (echo "$(INSTALL_INCLUDE_DIR) doesn't exist")
