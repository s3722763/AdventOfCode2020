#pragma once
#include <vector>
#include <string>

const int INVALID_PASSPORT_NUMBER = -1;

class Passport {
public:
	int byr = INVALID_PASSPORT_NUMBER;
	int iyr = INVALID_PASSPORT_NUMBER;
	int eyr = INVALID_PASSPORT_NUMBER;
	std::string hgt;
	std::string hcl;
	std::string ecl;
	std::string pid;
	int cid = INVALID_PASSPORT_NUMBER;

public:
		void process_data(std::vector<std::string> data);
		bool is_valid(bool check_numbers);
		void print();
};