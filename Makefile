TARGET = ipinfo
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

LINKER = -lcurl
IPINFO = src/ipinfo/ipinfo.cpp -DDEBUG_MODE
CJSON = src/cJSON/cJSON.c
SPDLOG = -I"src/spdlog/include"

FILES = $(IPINFO) $(CJSON) $(SPDLOG) src/main.cpp

$(TARGET):
	@echo "Let's build ipinfo as an application..."
	$(CXX) $(FLAGS) $(FILES) $(LINKER) -o ./bin/$(TARGET)
