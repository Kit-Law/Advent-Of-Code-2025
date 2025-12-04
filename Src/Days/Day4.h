#pragma once

#include "./InputReader.h"
#include "../Deps/gif-h/gif.h"

namespace Day4 {

	uint8_t* image;
	size_t width;
	size_t height;

	inline void SetPixel(int xx, int yy, uint8_t red, uint8_t grn, uint8_t blu) {
		uint8_t* pixel = &(image[(yy * width + xx) * 4]);
		pixel[0] = red;
		pixel[1] = grn;
		pixel[2] = blu;
		pixel[3] = 255;  // no alpha for this demo
	}

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

	inline unsigned long long star2(const char* path) noexcept {
		InputReader parser(path, "");
		std::vector<std::string> rows = parser.readLinesUntil();

		width = rows.size();
		height = rows[0].size();
		image = new uint8_t[width * height * 4];

		GifWriter writer = {};
		const char* filename = "./Visualization/Day4.gif";
		GifBegin(&writer, filename, width, height, 2, 8, true);

		unsigned long long movableRolls = 0;
		std::vector<std::tuple<size_t, size_t>> rollsToMove;

		for (size_t frame = 0; true; frame++) {
			for (size_t i = 0; i < rows.size(); i++) {
				for (size_t j = 0; j < rows[0].size(); j++) {
					if (rows[i][j] != '@') {
						SetPixel(i, j, 84, 73, 75);
						continue;
					}

					std::vector<unsigned char> adjacents = getAdjacents(rows, i, j);

					size_t rollCount =
						std::count_if(adjacents.begin(),
							adjacents.end(),
							[](unsigned char adjacent) { return adjacent == '@'; });

					if (rollCount < 4) {
						SetPixel(i, j, 244, 91, 105);
						rollsToMove.push_back(std::make_tuple(i, j));
					}
					else {
						SetPixel(i, j, 12, 186, 186);
					}
				}
			}
			if (rollsToMove.empty()) break;

			movableRolls += rollsToMove.size();
			for (const auto& [removeI, removeJ] : rollsToMove) {
				rows[removeI][removeJ] = '.';
			}
			rollsToMove.clear();

			if (frame == 1) GifWriteFrame(&writer, image, width, height, 40, 8, true);
			//if (frame > 0) GifWriteFrame(&writer, image, width, height, std::min(10 - (int)(frame / 2), 0), 8, true);
			if (frame > 1) GifWriteFrame(&writer, image, width, height, 8, 8, true);
		}

		for (size_t i = 0; i < rows.size(); i++) {
			for (size_t j = 0; j < rows[0].size(); j++) {
				if (rows[i][j] == '@') {
					SetPixel(i, j, 12, 186, 186);
				}
				else {
					SetPixel(i, j, 84, 73, 75);
				}
			}
		}
		GifWriteFrame(&writer, image, width, height, 40, 8, true);

		GifEnd(&writer);
		delete image;

		return movableRolls;
	}
}