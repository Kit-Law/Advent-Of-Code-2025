#pragma once

#include "./InputReader.h"

namespace Day7 {

	inline unsigned long long star1(const char* path) noexcept {
		InputReader parser(path, "");
		std::vector<std::string> rows = parser.readLinesUntil();

		unsigned long long totalSplits = 0;

		for (size_t y = 0; y < rows.size() - 1; y++) {
			for (size_t x = 0; x < rows[y].size(); x++) {
				if (rows[y][x] != '|' && rows[y][x] != 'S') continue;
				if (rows[y + 1][x] == '.') {
					rows[y + 1][x] = '|';
					continue;
				}
				if (rows[y + 1][x] != '^') continue;

				if (x - 1 >= 0) rows[y + 1][x - 1] = '|';
				if (x + 1 < rows[y + 1].size()) rows[y + 1][x + 1] = '|';
				totalSplits++;
			}
		}

		return totalSplits;
	}

	inline unsigned long long star2(const char* path) noexcept {
		InputReader parser(path, "");
		std::vector<std::string> rowsBuffer = parser.readLinesUntil();
		std::vector<std::vector<long long>> rows;

		for (const auto& row : rowsBuffer) {
			rows.push_back(std::vector<long long>());
			for (const auto& value : row) {
				if (value == '.') {
					rows.back().push_back(0);
				}
				if (value == 'S') {
					rows.back().push_back(1);
				}
				if (value == '^') {
					rows.back().push_back(-1);
				}
			}
		}

		for (size_t y = 0; y < rows.size() - 1; y++) {
			for (size_t x = 0; x < rows[y].size(); x++) {
				if (rows[y][x] == 0 || rows[y][x] == -1) continue;
				if (rows[y + 1][x] != -1) {
					rows[y + 1][x] += rows[y][x];
					continue;
				}

				if (x - 1 >= 0) rows[y + 1][x - 1] += rows[y][x];
				if (x + 1 < rows[y + 1].size()) rows[y + 1][x + 1] = rows[y][x];
			}
		}

		//std::cout << std::endl;
		//for (size_t y = 0; y < rows.size(); y++) {
		//	for (size_t x = 0; x < rows[y].size(); x++) {
		//		if (rows[y][x] == -1) std::cout << '^' << " ";
		//		else std::cout << (int)rows[y][x] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		//std::cout << std::endl;

		unsigned long long totalSplits = 0;
		for (const long long folds : rows.back()) {
			if (folds == -1) continue;
			totalSplits += folds;
		}

		return totalSplits;
	}
}