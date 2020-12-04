#include "Utility.h"

std::vector<std::string> split(std::string* line, std::string* delimiter) {
	size_t start = 0;
	size_t end = 0;
	std::string token;
	std::vector<std::string> components;

	while ((end = line->find(*delimiter, start)) != std::string::npos) {
		token = line->substr(start, end - start);
		components.push_back(token);
		start = end + delimiter->size();
	}

	components.push_back(line->substr(start, end));

	return components;
}