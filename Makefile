CPP := clang++
BUILD_DIR := build
SRC_DIR := src

TARGETS := $(BUILD_DIR)/day01 $(BUILD_DIR)/day02 $(BUILD_DIR)/day03 $(BUILD_DIR)/day04 $(BUILD_DIR)/day05 $(BUILD_DIR)/day06 $(BUILD_DIR)/day07 $(BUILD_DIR)/day08 $(BUILD_DIR)/day09 $(BUILD_DIR)/day10 $(BUILD_DIR)/day11 $(BUILD_DIR)/day12 $(BUILD_DIR)/day13 $(BUILD_DIR)/day14 $(BUILD_DIR)/day15 $(BUILD_DIR)/day16 $(BUILD_DIR)/day17 $(BUILD_DIR)/day18 $(BUILD_DIR)/day19 $(BUILD_DIR)/day20 $(BUILD_DIR)/day21 $(BUILD_DIR)/day22 $(BUILD_DIR)/day23 $(BUILD_DIR)/day24 $(BUILD_DIR)/day25

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

$(BUILD_DIR)/day06: $(BUILD_DIR)/day06.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day07: $(BUILD_DIR)/day07.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day08: $(BUILD_DIR)/day08.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day09: $(BUILD_DIR)/day09.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day10: $(BUILD_DIR)/day10.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day11: $(BUILD_DIR)/day11.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day12: $(BUILD_DIR)/day12.o $(BUILD_DIR)/util/emulator.o $(BUILD_DIR)/util/instructions.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day13: $(BUILD_DIR)/day13.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day14: $(BUILD_DIR)/day14.o $(BUILD_DIR)/util/md5.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day15: $(BUILD_DIR)/day15.o  | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day16: $(BUILD_DIR)/day16.o  | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day17: $(BUILD_DIR)/day17.o $(BUILD_DIR)/util/md5.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day18: $(BUILD_DIR)/day18.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day19: $(BUILD_DIR)/day19.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day20: $(BUILD_DIR)/day20.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day21: $(BUILD_DIR)/day21.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day22: $(BUILD_DIR)/day22.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day23: $(BUILD_DIR)/day23.o $(BUILD_DIR)/util/emulator.o $(BUILD_DIR)/util/instructions.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day24: $(BUILD_DIR)/day24.o $(BUILD_DIR)/util/point.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

$(BUILD_DIR)/day25: $(BUILD_DIR)/day25.o $(BUILD_DIR)/util/emulator.o $(BUILD_DIR)/util/instructions.o | $(BUILD_DIR)
	$(CPP) -o $@ $^

clean:
	rm -rf build