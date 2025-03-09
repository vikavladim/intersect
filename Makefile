CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -Werror
FLAGS_TEST = -lgtest
INCLUDES = -I /usr/include/eigen3
BUILD_DIR = build
APP_LIB_PATH = $(BUILD_DIR)/segment3d.a

all: clean run_tests
# all: clean run

run: build
	./$(BUILD_DIR)/main

run_tests: build_tests
	./$(BUILD_DIR)/tests

build: main.cc $(APP_LIB_PATH)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cc -o $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BUILD_DIR)/main.o $(APP_LIB_PATH) -o ./$(BUILD_DIR)/main

build_tests: $(APP_LIB_PATH)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c tests.cc -o $(BUILD_DIR)/tests.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BUILD_DIR)/tests.o $(APP_LIB_PATH) $(FLAGS_TEST) -o ./$(BUILD_DIR)/tests

clean:
	rm -rf $(BUILD_DIR)

$(APP_LIB_PATH): segment3d.cc
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c segment3d.cc -o $(BUILD_DIR)/segment3d.o
	ar rcs $@ $(BUILD_DIR)/segment3d.o

.PHONY: run run_tests build build_tests clean