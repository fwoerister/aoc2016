CPP := clang++
BUILD_DIR := build
SRC_DIR := src

TARGETS := $(BUILD_DIR)/day01 $(BUILD_DIR)/day02 $(BUILD_DIR)/day03 $(BUILD_DIR)/day04 $(BUILD_DIR)/day05

all: $(TARGETS)

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/util/point.o: $(SRC_DIR)/util/point.cpp | $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/util
	$(CPP) -c $(SRC_DIR)/util/point.cpp -o $(BUILD_DIR)/util/point.o

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) -c $< -o $@

$(BUILD_DIR)/day01: $(BUILD_DIR)/day01.o $(BUILD_DIR)/util/point.o $(BUILD_DIR) | $(BUILD_DIR)
	$(CPP) -o $(BUILD_DIR)/day01 $(BUILD_DIR)/day01.o $(BUILD_DIR)/util/point.o

$(BUILD_DIR)/day02: $(BUILD_DIR)/day02.o $(BUILD_DIR)/util/point.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day03: $(BUILD_DIR)/day03.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day04: $(BUILD_DIR)/day04.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day05: $(BUILD_DIR)/day05.o $(BUILD_DIR)/util/md5.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

clean:
	rm -rf build