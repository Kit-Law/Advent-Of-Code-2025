#pragma once

#include "./InputReader.h"

namespace Day1 {

	inline constexpr int STARTING_POSITION = 50;
	inline constexpr int MAX_POSITION = 100;

	inline long star1(const char* path) {
		int dialPosition = STARTING_POSITION;
		long zeroCounts = 0;

		InputReader parser(path, R"(([LR])(\d+))");
		char direction;
		int degree;

		while (parser.getNextMatch(direction, degree)) {
			dialPosition = (direction == 'L' ? dialPosition - degree : dialPosition + degree) % 100;

			if (!dialPosition) {
				zeroCounts++;
			}
		}

		return zeroCounts;
	}

	inline long star2(const char* path) noexcept {
		int dialPosition = STARTING_POSITION;
		long zeroCounts = 0;
		long altZeroCounts = zeroCounts;

		InputReader parser(path, R"(([LR])(\d+))");
		char direction;
		int degree;

		while (parser.getNextMatch(direction, degree)) {
			if (direction == 'L') {
				while (degree) {
					dialPosition--;
					if (dialPosition == 0) {
						zeroCounts++;
					}
					if (dialPosition == -1) {
						dialPosition = 99;
					}
					degree--;
				}
			}
			else {
				while (degree) {
					dialPosition++;
					if (dialPosition == 100) {
						dialPosition = 0;
						zeroCounts++;
					}
					degree--;
				}
			}
		}

		return zeroCounts;
	}
}