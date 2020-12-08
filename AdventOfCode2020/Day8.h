#pragma once
#include <vector>

enum Instruction {
	NOP,
	ACC,
	JMP
};

struct Day8Computer {
public:
	int pc = 0;
	int accumulator = 0;
	std::vector<std::pair<Instruction, signed int>> memory;

	void cycle();
	void file_to_memory(const char* filename);
	void reset();
};