.PHONY:
	prepare \
	clean \
	install \
	uninstall

PROJECT    := ipinfo
DEBUG_MODE := 1

OBJ_DIR     := obj
SRC_DIR     := src
INCLUDE_DIR := include
TARGET_DIR  := target

TARG := $(TARGET_DIR)/lib$(PROJECT).so
SRCS := $(shell find $(SRC_DIR)/ipinfo \
		-name "*.cpp" \
		-type f \
		-printf "%P ")

OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

PREFIX              ?= /usr/local
INSTALL_LIB_DIR     := $(DESTDIR)$(PREFIX)/lib
INSTALL_INCLUDE_DIR := $(DESTDIR)$(PREFIX)/include/ipinfo

# There are only headers needed by user will be installed.
INSTALL_HDRS := \
	$(shell find $(INCLUDE_DIR)/ipinfo \
	\( ! -name "*requester*" \) -and \
	\( ! -name "*parser*" \) -and \
	\( ! -name "*utiler*" \) -and \
	-name "*.hpp" -type f -printf "%p ")

CXX      := g++
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

all: prepare $(TARG)
	@ echo "bld" $(TARG)

$(TARG): $(OBJS)
	@ $(foreach obj, \
		$(shell find $(OBJ_DIR) -name "*.cpp.o" -type f), \
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
	@ (test -d $(OBJ_DIR) \
		&& echo \"$(OBJ_DIR)\" "already exists") \
		|| (echo "CRT" \"$(OBJ_DIR)\" && mkdir $(OBJ_DIR))

	@ (test -d $(TARGET_DIR) \
		&& echo \"$(TARGET_DIR)\" "already exists") \
		|| (echo "CRT" \"$(TARGET_DIR)\" && mkdir $(TARGET_DIR))

clean:
	@ (test "-d" $(TARGET_DIR) \
		&& (echo "RM" \"$(TARGET_DIR)\" && \
			rm "-r" $(TARGET_DIR))) \
		|| (echo \"$(TARGET_DIR)\" "doesn't exist")

	@ (test "-d" $(OBJ_DIR)  \
		&& (echo "RM" \"$(OBJ_DIR)\" && \
			rm -r $(OBJ_DIR))) \
		|| (echo \"$(OBJ_DIR)\" "doesn't exist")

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
	@ ($(TEST) "-e" $(INSTALL_LIB_DIR)"/lib$(PROJECT).so" \
		&& (echo "RM $(INSTALL_LIB_DIR)/lib$(PROJECT).so" && \
			$(RM) "$(INSTALL_LIB_DIR)/lib$(PROJECT).so")) \
		|| (echo "$(INSTALL_LIB_DIR)/lib$(PROJECT).so doesn't exist")

	@ ($(TEST) "-d" $(INSTALL_INCLUDE_DIR) \
		&& (echo "RM" $(INSTALL_INCLUDE_DIR) && \
			$(RM) "-r" $(INSTALL_INCLUDE_DIR))) \
		|| (echo $(INSTALL_INCLUDE_DIR) "doesn't exist")
