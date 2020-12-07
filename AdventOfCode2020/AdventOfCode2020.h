#pragma once
#include "Passport.h"
#include "Day7.h"
#include <vector>
#include <string>

namespace aoc {
	enum class Day3Grid {
		Open,
		Tree
	};

	enum class BoardingPassDirection {
		Forward,
		Backward,
		Left,
		Right
	};

	void day1_opt(std::vector<int> numbers, int* results);
	void day2_opt(std::vector<std::string> passwords, int* result);
	void day3_opt(std::vector<std::vector<Day3Grid>> grid, int* result);
	void day4_opt(std::vector<Passport> passports, int* result);
	void day5_opt(std::vector<std::vector<aoc::BoardingPassDirection>> boarding_passes, int* result);
	void day6_opt(std::vector<std::vector<int>> answers, int* results);
	void day7_opt(std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& bag_map, int* results);
	bool find_shiny_gold(const std::string& bag_to_check, std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& map);
	int find_number_bags(const std::string& bag_to_check, std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& map);
}

namespace aoc_util {
	std::vector<std::vector<aoc::Day3Grid>> read_grid_file(std::string filename);
	void day3_grid_display(std::vector<std::vector<aoc::Day3Grid>> grid);
	std::vector<Passport> day4_read(std::string filename);
	std::vector<std::vector<aoc::BoardingPassDirection>> day5_boarding_pass_process(std::string filename);
	std::vector<std::vector<int>> day6_read(std::string);
}