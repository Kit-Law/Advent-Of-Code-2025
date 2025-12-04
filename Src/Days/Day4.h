#pragma once

#include "./InputReader.h"

namespace Day4 {

	inline std::vector<unsigned char> getAdjacents(std::vector<std::string>& rows, int i, int j) {
		std::vector<unsigned char> adjacents;

		const bool hasSpaceNorth = i - 1 >= 0;
		const bool hasSpaceEast = j + 1 < rows[i].size();
		const bool hasSpaceSouth = i + 1 < rows.size();
		const bool hasSpaceWest = j - 1 >= 0;

		if (hasSpaceNorth)                 adjacents.push_back(rows[i - 1][j]);
		if (hasSpaceNorth && hasSpaceEast) adjacents.push_back(rows[i - 1][j + 1]);
		if (hasSpaceEast)                  adjacents.push_back(rows[i][j + 1]);
		if (hasSpaceEast && hasSpaceSouth) adjacents.push_back(rows[i + 1][j + 1]);
		if (hasSpaceSouth)                 adjacents.push_back(rows[i + 1][j]);
		if (hasSpaceSouth && hasSpaceWest) adjacents.push_back(rows[i + 1][j - 1]);
		if (hasSpaceWest)                  adjacents.push_back(rows[i][j - 1]);
		if (hasSpaceWest && hasSpaceNorth) adjacents.push_back(rows[i - 1][j - 1]);

		return adjacents;
	}

	inline unsigned long long star1(const char* path) noexcept {
		return 0;
		InputReader parser(path, "");
		std::vector<std::string> rows = parser.readLinesUntil();

		unsigned long long movableRolls = 0;

		for (size_t i = 0; i < rows.size(); i++) {
			for (size_t j = 0; j < rows[0].size(); j++) {
				if (rows[i][j] != '@') continue;

				std::vector<unsigned char> adjacents = getAdjacents(rows, i, j);

				size_t rollCount = 
					std::count_if(adjacents.begin(),
								  adjacents.end(),
						          [](unsigned char adjacent) { return adjacent == '@'; });

				if (rollCount < 4) movableRolls++;
			}
		}

		return movableRolls;
	}

	inline long star2(const char* path) noexcept {
		InputReader parser(path, "");
		std::vector<std::string> rows = parser.readLinesUntil();

		unsigned long long movableRolls = 0;
		std::vector<std::tuple<size_t, size_t>> rollsToMove;

		while (true) {
			for (size_t i = 0; i < rows.size(); i++) {
				for (size_t j = 0; j < rows[0].size(); j++) {
					if (rows[i][j] != '@') continue;

					std::vector<unsigned char> adjacents = getAdjacents(rows, i, j);

					size_t rollCount =
						std::count_if(adjacents.begin(),
							adjacents.end(),
							[](unsigned char adjacent) { return adjacent == '@'; });

					if (rollCount < 4) rollsToMove.push_back(std::make_tuple(i, j));
				}
			}

			if (rollsToMove.empty()) break;

			movableRolls += rollsToMove.size();
			for (const auto& [removeI, removeJ] : rollsToMove) {
				rows[removeI][removeJ] = '.';
			}
			rollsToMove.clear();
		}

		return movableRolls;
	}
}