// AdventOfCode2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "AdventOfCode2020.h"
#include "Utility.h"

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

			for (char &c : tokens[2]) {
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
			} else if (!(tokens[2].at(min - 1) == character) && tokens[2].at(max - 1) == character) {
				result[1] += 1;
			}
		}
	}

	void day3_opt(std::vector<std::vector<Day3Grid>> grid, int* result) {
		int width = grid[0].size();
		int depth = grid.size();

		int x_change_settings[5] = {1, 3, 5, 7, 1};
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
			} else if (i == 1) {
				//This is the first part of this day
				result[0] = hit_trees;
				result[1] *= hit_trees;
			} else {
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
				} else if (c == '#') {
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
				} else if (grid[y][x] == aoc::Day3Grid::Tree) {
					std::cout << '#';
				}
			}

			std::cout << std::endl;
		}
	}
}