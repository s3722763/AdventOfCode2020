// AdventOfCode2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>

#include "AdventOfCode2020.h"
#include "Utility.h"

#define DAY6_PEOPLE_INDEX 26

int main() {
	std::ifstream file("Day1.txt");
	int count = 0;
	std::vector<int> numbers;
	int number;

	while (file >> number) {
		count += 1;
		numbers.push_back(number);
	}

	int results[2];

	aoc::day1_opt(numbers, results);
	std::cout << "Part 1: " << results[0] << "\tPart 2: " << results[1] << std::endl;

	std::ifstream file_2("Day2.txt");
	std::vector<std::string> input;
	std::string line;

	while (getline(file_2, line)) {
		input.push_back(line);
	}

	int result[2] = { 0, 0 };

	aoc::day2_opt(input, result);
	std::cout << "Part 1: " << result[0] << " Part 2: " << result[1] << std::endl;

	std::vector<std::vector<aoc::Day3Grid>> day3_grid = aoc_util::read_grid_file("Day3.txt");
	int hit_trees[2] = { 0,0 };
	aoc::day3_opt(day3_grid, hit_trees);
	std::cout << "Part 1: " << hit_trees[0] << " Part 2: " << hit_trees[1] << std::endl;

	int valid_passports[2] = { 0,0 };
	std::vector<Passport> passports = aoc_util::day4_read("Day4.txt");
	aoc::day4_opt(passports, valid_passports);
	std::cout << "Part 1: " << valid_passports[0] << " Part 2: " << valid_passports[1] << std::endl;

	int day5_results[2] = { 0,0 };
	auto boarding_passes = aoc_util::day5_boarding_pass_process("Day5.txt");
	aoc::day5_opt(boarding_passes, day5_results);
	std::cout << "Part 1: " << day5_results[0] << " Part 2: " << day5_results[1] << std::endl;

	std::vector<std::vector<int>> answers = aoc_util::day6_read("Day6.txt");
	int day6_results[2] = {};
	aoc::day6_opt(answers, day6_results);
	std::cout << "Part 1: " << day6_results[0] << " Part 2: " << day6_results[1] << std::endl;

	auto map = aoc_util::string_to_bag_map("Day7.txt");

	/*for (auto a = map.begin(); a != map.end(); a++) {
		std::cout << a->first << " contain ";

		for (auto &bag : a->second) {
			char plural = bag.second > 1 ? 's' : ' ';
			std::cout << bag.second << " " << bag.first << plural << " ";
		}

		std::cout << std::endl;
	}*/

	int day7_results[2] = {};
	aoc::day7_opt(map, day7_results);
	std::cout << "Part 1: " << day7_results[0] << " Part 2: " << day7_results[1] << std::endl;

	int day8_results[2] = {};
	Day8Computer day_8_computer;
	day_8_computer.file_to_memory("Day8.txt");
	aoc::day8_opt(day_8_computer, day8_results);
	std::cout << "Part 1: " << day8_results[0] << " Part 2: " << day8_results[1] << std::endl;
}

namespace aoc {
	void day1_opt(std::vector<int> numbers, int* results) {
		int count = numbers.size();
		int product = 0;

		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count; j++) {
				int number = numbers[i] + numbers[j];

				if (number == 2020) {
					product = numbers[i] * numbers[j];
					break;
				}
			}

			if (product != 0) {
				break;
			}
		}

		results[0] = product;
		product = 0;

		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count; j++) {
				for (int k = 0; k < count; k++) {
					int number = numbers[i] + numbers[j] + numbers[k];

					if (number == 2020) {
						product = numbers[i] * numbers[j] * numbers[k];
						break;
					}
				}

				if (product != 0) {
					break;
				}
			}
			if (product != 0) {
				break;
			}
		}

		results[1] = product;
	}

	void day2_opt(std::vector<std::string> input, int* result) {
		for (std::vector<std::string>::iterator line_itr = input.begin(); line_itr != input.end(); line_itr++) {
			//std::cout << *line_itr << std::endl;
			std::string delimiter = " ";
			std::string min_max_delimiter = "-";
			int count = 0;

			auto tokens = split(&(*line_itr), &delimiter);
			char character = tokens[1].at(0);
			//std::cout << "Character: " << character << " -> ";
			auto min_max = split(&tokens[0], &min_max_delimiter);

			for (char& c : tokens[2]) {
				//std::cout << c;
				if (c == character) {
					count += 1;
				}
			}

			//std::cout << " " << count << std::endl;

			std::stringstream min_str(min_max[0]);
			std::stringstream max_str(min_max[1]);

			int min, max;
			min_str >> min;
			max_str >> max;

			if (count >= min && count <= max) {
				result[0] += 1;
			}

			bool is_pos = false;

			if (tokens[2].at(min - 1) == character && !(tokens[2].at(max - 1) == character)) {
				result[1] += 1;
			}
			else if (!(tokens[2].at(min - 1) == character) && tokens[2].at(max - 1) == character) {
				result[1] += 1;
			}
		}
	}

	void day3_opt(std::vector<std::vector<Day3Grid>> grid, int* result) {
		int width = grid[0].size();
		int depth = grid.size();

		int x_change_settings[5] = { 1, 3, 5, 7, 1 };
		int y_change_settings[5] = { 1, 1, 1, 1, 2 };

		for (int i = 0; i < 5; i++) {
			int x = 0;
			int y = 0;
			int hit_trees = 0;

			int x_change = x_change_settings[i];
			int y_change = y_change_settings[i];

			while (y < depth) {
				auto object_at = grid[y][x % width];

				if (object_at == aoc::Day3Grid::Tree) {
					hit_trees += 1;
				}

				x += x_change;
				y += y_change;
			}

			if (i == 0) {
				//First so multipling by trees == 0 so we just set result[1] to it
				result[1] = hit_trees;
			}
			else if (i == 1) {
				//This is the first part of this day
				result[0] = hit_trees;
				result[1] *= hit_trees;
			}
			else {
				result[1] *= hit_trees;
			}
		}
	}

	void day4_opt(std::vector<Passport> passports, int* result) {
		for (auto passport = passports.begin(); passport != passports.end(); passport++) {
			if (passport->is_valid(false)) {
				result[0] += 1;
			}

			if (passport->is_valid(true)) {
				result[1] += 1;

				//passport->print();
			}
		}
	}

	void day5_opt(std::vector<std::vector<aoc::BoardingPassDirection>> boarding_passes, int* results) {
		int highest = 0;
		int seats[1024] = {};

		for (auto boarding_pass = boarding_passes.begin(); boarding_pass != boarding_passes.end(); boarding_pass++) {
			int low_r = 0;
			int high_r = 127;
			int low_c = 0;
			int high_c = 7;

			for (auto direction = boarding_pass->begin(); direction != boarding_pass->end(); direction++) {
				int middle_r = (low_r + high_r) / 2;
				int middle_c = (low_c + high_c) / 2;
				bool round_r = false;
				bool round_c = false;

				if ((low_r + high_r) % 2 == 1) {
					round_r = true;
				}

				if ((low_c + high_c) % 2 == 1) {
					round_c = true;
				}

				if (*direction == aoc::BoardingPassDirection::Forward) {
					high_r = middle_r;
				}
				else if (*direction == aoc::BoardingPassDirection::Backward) {
					low_r = middle_r;

					if (round_r) {
						low_r += 1;
					}
				}
				else if (*direction == aoc::BoardingPassDirection::Left) {
					high_c = middle_c;
				}
				else if (*direction == aoc::BoardingPassDirection::Right) {
					low_c = middle_c;

					if (round_c) {
						low_c += 1;
					}
				}

				//std::cout << low_r << ":" << high_r << " " << low_c << ":" << high_c << std::endl;
			}

			assert(low_c == high_c);
			assert(low_r == high_r);

			int id = (low_r * 8) + low_c;

			if (id > highest) {
				highest = id;
			}

			seats[id] = 1;
		}

		results[0] = highest;

		for (int i = 8; i < 1024; i++) {
			if (seats[i] == 0 && seats[i - 8] == 1 && seats[i + 8] == 1) {
				results[1] = i;
				return;
			}
		}
	}

	void day6_opt(std::vector<std::vector<int>> answers, int* results) {
		results[0] = 0;
		int everyone_answers[26] = {};

		for (auto answer_set = answers.begin(); answer_set != answers.end(); answer_set++) {
			int sum = 0;

			for (int i = 0; i < 26; i++) {
				if ((*answer_set)[i] >= 1) {
					//std::cout << ((char)(i + 97)) << " ";
					everyone_answers[i] = 1;
					sum += 1;
				}

				if ((*answer_set)[i] == (*answer_set)[DAY6_PEOPLE_INDEX]) {
					//std::cout << ((char)(i + 97)) << " ";
					results[1] += 1;
				}
			}

			//std::cout << std::endl;
			//std::cout << " count: " << sum << std::endl;
			results[0] += sum;
		}
	}

	void day7_opt(std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& bag_map, int* results) {
		//Part 1
		for (auto& start_bag : bag_map) {
			//std::cout << start_bag.first << "------" << std::endl;
			if (find_shiny_gold(start_bag.first, bag_map)) {
				results[0] += 1;
			}

			//std::cout << std::endl;
		}

		results[1] = find_number_bags("shiny gold bag", bag_map);
	}

	bool find_shiny_gold(const std::string &bag_to_check, std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> &map) {
		if (map.find(bag_to_check) != map.end()) {
			for (auto& bag : map.at(bag_to_check)) {
				//std::cout << bag.first << std::endl;
				if (bag.first.find("shiny gold") != std::string::npos) {
					return true;
				}

				if (find_shiny_gold(bag.first, map)) {
					return true;
				}
			}
		}
		return false;
	}

	int find_number_bags(const std::string& bag_to_check, std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& map) {
		int amount = 0;

		if (map.find(bag_to_check) != map.end()) {
			for (auto& bag : map.at(bag_to_check)) {

				int inside_amount = find_number_bags(bag.first, map);
				if (inside_amount != 0) {
					amount += (bag.second * inside_amount) + bag.second;
				}
				else {
					amount += bag.second;
				}
				
			}
		}

		return amount;
	}

	bool check_loop(Day8Computer &computer) {
		std::vector<int> pc_accessed;
		bool at_end = false;

		while (!at_end) {
			pc_accessed.push_back(computer.pc);
			computer.cycle();

			if (std::find(pc_accessed.begin(), pc_accessed.end(), computer.pc) != pc_accessed.end()) {
				return false;
			}
			else if (computer.pc == computer.memory.size()) {
				return true;
			}
		}

		return true;
	}

	void day8_opt(Day8Computer &computer, int* results) {
		std::vector<int> pc_accessed;
		bool loop_found = false;
		
		while (!loop_found) {
			pc_accessed.push_back(computer.pc);
			int old_accumulator = computer.accumulator;
			computer.cycle();

			if (std::find(pc_accessed.begin(), pc_accessed.end(), computer.pc) != pc_accessed.end()) {
				results[0] = old_accumulator;
				loop_found = true;
			}
		}

		for (int i = 0; i < computer.memory.size(); i++) {
			if (computer.memory[i].first == Instruction::JMP) {
				//Change to NOP
				computer.memory[i].first = Instruction::NOP;

				if (check_loop(computer)) {
					results[1] = computer.accumulator;
				}

				computer.memory[i].first = Instruction::JMP;
			}
			else if (computer.memory[i].first == Instruction::NOP) {
				//Change to JMP
				computer.memory[i].first = Instruction::JMP;

				if (check_loop(computer)) {
					results[1] = computer.accumulator;
				}

				computer.memory[i].first = Instruction::NOP;
			}

			computer.reset();
		}
	}
}

namespace aoc_util {
	std::vector<std::vector<aoc::Day3Grid>> read_grid_file(std::string filename) {
		std::ifstream file(filename);

		std::string line;

		std::vector<std::vector<aoc::Day3Grid>> grid;

		while (getline(file, line)) {
			std::vector<aoc::Day3Grid> line_grid;

			for (int i = 0; i < line.length(); i++) {
				char c = line.at(i);

				if (c == '.') {
					line_grid.push_back(aoc::Day3Grid::Open);
				}
				else if (c == '#') {
					line_grid.push_back(aoc::Day3Grid::Tree);
				}
			}

			grid.push_back(line_grid);
		}

		return grid;
	}

	void day3_grid_display(std::vector<std::vector<aoc::Day3Grid>> grid) {
		for (int y = 0; y < grid.size(); y++) {
			for (int x = 0; x < grid[y].size(); x++) {
				if (grid[y][x] == aoc::Day3Grid::Open) {
					std::cout << '.';
				}
				else if (grid[y][x] == aoc::Day3Grid::Tree) {
					std::cout << '#';
				}
			}

			std::cout << std::endl;
		}
	}

	std::vector<std::vector<aoc::BoardingPassDirection>> day5_boarding_pass_process(std::string filename) {
		std::ifstream file(filename);
		std::string line;
		std::vector<std::vector<aoc::BoardingPassDirection>> boarding_passes;

		while (getline(file, line)) {
			std::vector<aoc::BoardingPassDirection> boarding_pass;

			for (char& c : line) {
				if (c == 'F') {
					boarding_pass.push_back(aoc::BoardingPassDirection::Forward);
				}
				else if (c == 'B') {
					boarding_pass.push_back(aoc::BoardingPassDirection::Backward);
				}
				else if (c == 'L') {
					boarding_pass.push_back(aoc::BoardingPassDirection::Left);
				}
				else if (c == 'R') {
					boarding_pass.push_back(aoc::BoardingPassDirection::Right);
				}
				else {
					std::cout << "Invalid Day 5 boarding pass: " << c << std::endl;
				}
			}

			boarding_passes.push_back(boarding_pass);
		}

		return boarding_passes;
	}

	std::vector<std::vector<int>> day6_read(std::string filename) {
		std::ifstream file(filename);
		std::string line;

		std::vector<std::vector<int>> question_answers;
		std::vector<int> answers;
		answers.reserve(27);

		for (int i = 0; i < 27; i++) {
			answers.push_back(0);
		}

		while (getline(file, line)) {
			if (line.empty()) {
				question_answers.push_back(answers);
				answers.clear();

				for (int i = 0; i < 27; i++) {
					answers.push_back(0);
				}
			}
			else {
				for (char& c : line) {
					answers[(int)c - 97] += 1;
				}

				answers[DAY6_PEOPLE_INDEX] += 1;
			}
		}

		for (char& c : line) {
			answers[(int)c - 97] += 1;
			answers[DAY6_PEOPLE_INDEX] += 1;
		}


		if (!answers.empty()) {
			question_answers.push_back(answers);
		}

		return question_answers;
	}
}