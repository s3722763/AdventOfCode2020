#include "Passport.h"
#include <fstream>
#include <iostream>
#include "Utility.h"

void Passport::process_data(std::vector<std::string> data) {
	std::string section_delimiter = " ";
	std::string part_delimiter = ":";

	for (auto line = data.begin(); line != data.end(); line++) {
		auto sections = split(&(*line), &section_delimiter);

		for (auto section = sections.begin(); section != sections.end(); section++) {
			auto parts = split(&(*section), &part_delimiter);

			if (parts[0] == "byr") {
				this->byr = std::stoi(parts[1]);
			} else if (parts[0] == "iyr") {
				this->iyr = std::stoi(parts[1]);
			} else if (parts[0] == "eyr") {
				this->eyr = std::stoi(parts[1]);
			} else if (parts[0] == "hgt") {
				this->hgt = parts[1];
			} else if (parts[0] == "hcl") {
				this->hcl = parts[1];
			} else if (parts[0] == "ecl") {
				this->ecl = parts[1];
			} else if (parts[0] == "pid") {
				this->pid = parts[1];
			} else if (parts[0] == "cid") {
				this->cid = std::stoi(parts[1]);
			}
		}
	}
}

bool Passport::is_valid(bool check_numbers) {
	//this->print();

	if (this->byr == INVALID_PASSPORT_NUMBER || this->iyr == INVALID_PASSPORT_NUMBER || this->eyr == INVALID_PASSPORT_NUMBER 
		|| this->hgt.empty() || this->hcl.empty() || this->ecl.empty() || this->pid.empty() /*|| this->cid == INVALID_PASSPORT_NUMBER*/ ) {
		return false;
	}

	if (check_numbers) {
		if (this->byr < 1920 || this->byr > 2002) {
			//std::cout << "BYR: " << this->byr << std::endl;
			return false;
		}

		if (this->iyr < 2010 || this->iyr > 2020) {
			//std::cout << "IYR: " << this->iyr << std::endl;
			return false;
		}

		if (this->eyr < 2020 || this->eyr > 2030) {
			//std::cout << "EYR: " << this->eyr << std::endl;
			return false;
		}

		if (this->hgt.find("in") != std::string::npos) {
			this->hgt.erase(std::remove(this->hgt.begin(), this->hgt.end(), 'i'), this->hgt.end());
			this->hgt.erase(std::remove(this->hgt.begin(), this->hgt.end(), 'n'), this->hgt.end());
			int amount = std::stoi(this->hgt);

			if (amount < 59 || amount > 76) {
				//std::cout << "HGT: " << this->hgt << "in" << std::endl;
				return false;
			}
		} else if (this->hgt.find("cm") != std::string::npos) {
			this->hgt.erase(std::remove(this->hgt.begin(), this->hgt.end(), 'c'), this->hgt.end());
			this->hgt.erase(std::remove(this->hgt.begin(), this->hgt.end(), 'm'), this->hgt.end());
			int amount = std::stoi(this->hgt);

			if (amount < 150 || amount > 193) {
				//std::cout << "HGT: " << this->hgt << "cm" << std::endl;
				return false;
			}
		} else {
			return false;
		}

		if (this->hcl.at(0) != '#' || this->hcl.length() != 7) {
			return false;
		}

		for (int i = 1; i < 7; i++) {
			char c = this->hcl.at(i);
		
			if (!std::isdigit(c) && c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f') {
				//std::cout << "HCL: " << this->hcl << std::endl;
				return false;
			}
		}

		if (this->ecl != "amb" && this->ecl != "blu" && this->ecl != "brn" && this->ecl != "gry" && this->ecl != "grn" 
			&& this->ecl != "hzl" && this->ecl != "oth") {
			//std::cout << "HCL: " << this->ecl << std::endl;
			return false;
		}

		if (this->pid.find("#") == std::string::npos) {
			if (this->pid.length() > 9) {
				//std::cout << "PID: " << this->pid << std::endl;
				return false;
			}

			for (auto c = this->pid.begin(); c != this->pid.end(); c++) {
				if (!std::isdigit(*c)) {
					return false;
				}
			}
		} else {
			//std::cout << "PID: " << this->pid << std::endl;
			return false;
		}
	}

	return true;
}

void Passport::print() {
	std::cout << this->byr << " " << this->iyr << " " << this->eyr << " " << this->hcl << " " << this->ecl << " " 
		<< this->pid << " " << this->cid << " " << this->hgt << std::endl;
}

namespace aoc_util {
	std::vector<Passport> day4_read(std::string filename) {
		std::ifstream input(filename);
		std::string line;
		std::vector<std::string> passport_lines;
		std::vector<Passport> passports;

		while (getline(input, line)) {
			if (line.empty()) {
				Passport passport;
				passport.process_data(passport_lines);
				passports.push_back(passport);
				passport_lines.clear();
			} else {
				passport_lines.push_back(line);
			}
		}

		if (!passport_lines.empty()) {
			Passport passport;
			passport.process_data(passport_lines);
			passports.push_back(passport);
		}

		return passports;
	}
}
