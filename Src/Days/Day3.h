#pragma once

#include <set>

#include "./InputReader.h"

namespace Day3 {

	constexpr size_t numberOfBatteriesNeeded = 12;

	inline unsigned long long star1(const char* path) noexcept {
		InputReader parser(path, "");
		std::vector<std::vector<unsigned char>> rows = parser.readNumbers();

		unsigned long long total = 0;
		for (std::vector<unsigned char>& row : rows) {
			auto maxElement = std::max_element(row.begin(), row.end());

			if (maxElement == row.end() - 1) {
				auto maxElementInSubset = std::max_element(row.begin(), maxElement);
				total += (*maxElementInSubset) * 10 + (*maxElement);
			}
			else {
				auto maxElementInSubset = std::max_element(maxElement + 1, row.end());
				total += (*maxElement) * 10 + (*maxElementInSubset);
			}
		}

		return total;
	}

	inline void populateMaxBatteries(std::vector<unsigned char>::iterator lhs, std::vector<unsigned char>::iterator rhs, std::set<std::vector<unsigned char>::iterator>& batteries) {
		if (batteries.size() == numberOfBatteriesNeeded) {
			return;
		}
		
		auto maxElement = std::max_element(lhs, rhs);
		batteries.insert(maxElement);

		if (maxElement + 1 < rhs) populateMaxBatteries(maxElement + 1, rhs, batteries);
		if (lhs < maxElement) populateMaxBatteries(lhs, maxElement, batteries);
	}

	inline unsigned long long star2(const char* path) noexcept {
		InputReader parser(path, "");
		std::vector<std::vector<unsigned char>> rows = parser.readNumbers();

		unsigned long long total = 0;
		for (std::vector<unsigned char>& row : rows) {
			std::set<std::vector<unsigned char>::iterator> batteries;
			populateMaxBatteries(row.begin(), row.end(), batteries);

			size_t remainingBatteries = numberOfBatteriesNeeded;
			for (size_t i = 0; i < row.size() && remainingBatteries > 0; i++) {
				if (!batteries.contains(row.begin() + i)) {
					continue;
				}

				remainingBatteries--;
				total += row[i] * pow(10, remainingBatteries);
			}
		}

		return total;
	}
}