#include "Utility.h"
#include "Day8.h"
#include <fstream>

void Day8Computer::file_to_memory(const char* filename) {
	std::ifstream file(filename);
	std::string line;
	std::string delimiter = " ";

	while (getline(file, line) && !line.empty()) {
		auto parts = split(&line, &delimiter);
		std::pair<Instruction, int> instruction;

		if (parts[0] == "nop") {
			instruction.first = Instruction::NOP;
		}
		else if (parts[0] == "acc") {
			instruction.first = Instruction::ACC;
		}
		else if (parts[0] == "jmp") {
			instruction.first = Instruction::JMP;
		}

		instruction.second = std::stoi(parts[1]);

		this->memory.push_back(instruction);
	}
}

void Day8Computer::cycle() {
	auto &instruction = this->memory[this->pc];

	if (instruction.first == Instruction::ACC) {
		this->accumulator += instruction.second;
		this->pc += 1;
	}
	else if (instruction.first == Instruction::JMP) {
		this->pc += instruction.second;
	}
	else if (instruction.first == Instruction::NOP) {
		this->pc += 1;
	}
}

void Day8Computer::reset() {
	this->pc = 0;
	this->accumulator = 0;
}