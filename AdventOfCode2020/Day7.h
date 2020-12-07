#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Utility.h"


namespace aoc_util {
	std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> string_to_bag_map(std::string input);
}
