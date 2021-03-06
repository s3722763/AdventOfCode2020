#include "pch.h"
#include "CppUnitTest.h"
#include "..\AdventOfCode2020\AdventOfCode2020.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(UnitTests) {
public:
	TEST_METHOD(TestDay1) {
		std::vector<int> numbers = { 1721, 979, 366, 299, 675, 1456 };
		int results[2];

		aoc::day1_opt(numbers, results);

		Assert::AreEqual(514579, results[0]);
		Assert::AreEqual(241861950, results[1]);
	}
	TEST_METHOD(TestDay3) {
		std::vector<std::vector<aoc::Day3Grid>> grid = aoc_util::read_grid_file("Day3Test.txt");
		Assert::AreNotEqual((size_t)0, grid.size());

		int results[2] = { 0, 0 };
		aoc::day3_opt(grid, results);
		Assert::AreEqual(7, results[0]);
		Assert::AreEqual(336, results[1]);
	}
	TEST_METHOD(TestDay4) {
		std::vector<Passport> passports = aoc_util::day4_read("Day4Test.txt");
		int valid_passports[2] = { 0, 0 };
		aoc::day4_opt(passports, valid_passports);
		Assert::AreEqual(8, valid_passports[0]);
		Assert::AreEqual(4, valid_passports[1]);
	}
	TEST_METHOD(TestDay5) {
		std::vector<std::vector<aoc::BoardingPassDirection>> boarding_passes = aoc_util::day5_boarding_pass_process("Day5Test.txt");
		int results[2] = { 0,0 };
		aoc::day5_opt(boarding_passes, results);
		Assert::AreEqual(357, results[0]);
	}
	TEST_METHOD(TestDay6) {
		std::vector<std::vector<int>> answers = aoc_util::day6_read("Day6Test.txt");
		int results[2] = {};
		aoc::day6_opt(answers, results);
		Assert::AreEqual(11, results[0]);
		Assert::AreEqual(6, results[1]);
	}
	TEST_METHOD(TestDay7) {
		auto map = aoc_util::string_to_bag_map("Day7Test.txt");
		int results[2] = {};
		aoc::day7_opt(map, results);
		Assert::AreEqual(5, results[0]);
	}	
	TEST_METHOD(TestDay8) {
		Day8Computer computer;
		computer.file_to_memory("Day8Test.txt");
		int results[2] = {};
		aoc::day8_opt(computer, results);
		Assert::AreEqual(5, results[0]);
		Assert::AreEqual(8, results[1]);
	}
	TEST_METHOD(TestDay9) {
		std::vector<int> numbers = aoc_util::day9_read("Day9Test.txt");
		int results[2] = {};
		aoc::day9_opt(numbers, 5, results);
		Assert::AreEqual(127, results[0]);
		Assert::AreEqual(62, results[1]);
	}
	};
}
