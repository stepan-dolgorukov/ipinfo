TARGET = ipinfo
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2 -march-native

LINKER = -lcurl
IPINFO = sources/ipinfo/ipinfo.cpp -DDEBUG_MODE
CJSON = sources/cJSON/cJSON.c
SPDLOG = -I"sources/spdlog/include"

FILES = $(IPINFO) $(CJSON) $(SPDLOG) sources/main.cpp

$(TARGET):
	@echo "Let's build ipinfo as an application..."
	$(CXX) $(FLAGS) $(FILES) $(LINKER) -o ./binaries/$(TARGET)