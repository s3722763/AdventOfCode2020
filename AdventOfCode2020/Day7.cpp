#include "Day7.h"
#include <fstream>

std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> aoc_util::string_to_bag_map(std::string filename) {
	std::ifstream input(filename);
	std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> map;
	std::string line;
	std::vector<std::string> lines;

	while(getline(input, line) && !line.empty()) {
		std::string parts_delimiter = " contain ";
		auto parts = split(&line, &parts_delimiter);

		std::string name = parts[0];

		if (name.at(name.length() - 1) == 's') {
			name.pop_back();
		}

		std::string contains_bags_delimiter = ", ";
		auto contains_bags = split(&parts[1], &contains_bags_delimiter);
		std::vector<std::pair<std::string, int>> bags_can_contain;

		for (auto contains_bag = contains_bags.begin(); contains_bag != contains_bags.end(); contains_bag++) {
			int digit = std::atoi(&contains_bag->at(0));

			std::string bag_name = contains_bag->substr(2, contains_bag->length() - 1);

			bag_name.erase(std::remove(bag_name.begin(), bag_name.end(), '.'), bag_name.end());

			if (bag_name.at(bag_name.length() - 1) == 's') {
				bag_name.pop_back();
			}

			if (bag_name != "other bag") {
				bags_can_contain.push_back(std::pair<std::string, int>(bag_name, digit));
			}
		}

		map.insert(std::pair<std::string, std::vector<std::pair<std::string, int>>>(name, bags_can_contain));
		line = "";
	}

	return map;
}