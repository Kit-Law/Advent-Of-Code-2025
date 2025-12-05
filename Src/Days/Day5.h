#pragma once

#include "./InputReader.h"

namespace Day5 {

	inline unsigned long long star1(const char* path) noexcept {
		InputReader parser(path, R"((\d+)-(\d+))", {}, "");
		
		std::vector<std::tuple<unsigned long long, unsigned long long>> ranges;
		unsigned long long fromValue;
		unsigned long long toValue;

		while (parser.getNextMatch(fromValue, toValue)) {
			ranges.push_back(std::make_tuple(fromValue, toValue));
		}

		parser.updatePattern(R"((\d+))");

		unsigned long long freshCount = 0;
		unsigned long long testValue;
		while (parser.getNextMatch(testValue)) {
			for (const auto& [from, to] : ranges) {
				if (testValue >= from && testValue <= to) {
					freshCount++;
					break;
				}
			}
		}
		
		return freshCount;
	}

	inline unsigned long long star2(const char* path) noexcept {
		InputReader parser(path, R"((\d+)-(\d+))", {}, "");

		std::vector<std::tuple<unsigned long long, unsigned long long>> ranges;
		unsigned long long fromValue;
		unsigned long long toValue;

		while (parser.getNextMatch(fromValue, toValue)) {
			ranges.push_back(std::make_tuple(fromValue, toValue));
		}

		std::sort(ranges.begin(), ranges.end(), [](auto& lhs, auto& rhs) {
			return std::get<0>(lhs) < std::get<0>(rhs);
		});

		unsigned long long freshCount = 0;

		fromValue = 0;
		size_t j;
		for (size_t i = 0; i < ranges.size(); i = j) {
			j = i + 1;
			toValue = std::get<1>(ranges[i]);
			for (; j < ranges.size() && std::get<0>(ranges[j]) <= toValue; j++) {
				toValue = std::max(std::get<1>(ranges[j]), toValue);
			}

			freshCount += toValue - std::get<0>(ranges[i]) + 1;
		}

		return freshCount;
	}
}