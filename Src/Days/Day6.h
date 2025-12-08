#pragma once

#include "./InputReader.h"

namespace Day6 {

	constexpr size_t NUMBER_OF_LINES = 4;

	inline unsigned long long star1(const char* path) noexcept {
		InputReader parser(path, "");

		std::vector<std::vector<unsigned long long>> numbers;

		// TODO: Work out the number of lines
		for (size_t i = 0; i < NUMBER_OF_LINES; i++) {
			numbers.push_back(std::vector<unsigned long long> ());
			parser.parseLine(numbers.back());
		}

		std::vector<char> operations;
		parser.parseLine(operations);

		unsigned long long total = 0;
		for (size_t i = 0; i < numbers[0].size(); i++) {
			if (operations[i] == '+') {
				for (size_t row = 0; row < numbers.size(); row++) {
					total += numbers[row][i];
				}
			}
			else if (operations[i] == '*') {
				unsigned long long result = 1;
				for (size_t row = 0; row < numbers.size(); row++) {
					result *= numbers[row][i];
				}
				total += result;
			}
			else {
				std::cout << "huh?" << std::endl;
			}
		}

		return total;
	}

	inline unsigned long long star2(const char* path) noexcept {
		InputReader parser(path, "");

		std::vector<std::string> numbers = parser.readNLines(NUMBER_OF_LINES);
		std::vector<char> operations;
		parser.parseLine(operations);

		unsigned long long total = 0;
		std::vector<unsigned long long> parsedNumbers;
		size_t currentOperation = 0;
		for (size_t column = 0; column < numbers[0].size(); column++) {
			std::string number;
			number.reserve(numbers.size());

			for (size_t row = 0; row < numbers.size(); row++) {
				number.push_back(numbers[row][column]);
			}

			if (number != std::string(numbers.size(), ' ')) {
				parsedNumbers.push_back(std::stoull(number));

				if (column != numbers[0].size() - 1) {
					continue;
				}
			}

			if (operations[currentOperation] == '+') {
				for (unsigned long long& parsedNumber : parsedNumbers) {
					total += parsedNumber;
				}
			}
			else if (operations[currentOperation] == '*') {
				unsigned long long result = 1;
				for (unsigned long long& parsedNumber : parsedNumbers) {
					result *= parsedNumber;
				}
				total += result;
			}
			currentOperation++;
			parsedNumbers.clear();
		}

		return total;  
	}
}