#pragma once

#include "./InputReader.h"

namespace Day9 {

	inline unsigned long long star1(const char* path) noexcept {
		InputReader parser(path, R"((\d+),(\d+))");

		std::vector<std::tuple<long long, long long>> points;
		long long x, y;
		while (parser.getNextMatch(x, y)) {
			points.push_back(std::make_tuple(x, y));
		}

		unsigned long long largestArea = 0;
		for (size_t i = 0; i < points.size(); i++) {
			for (size_t j = 0; j < points.size(); j++) {
				if (i == j) {
					continue;
				}

				const auto& [xi, yi] = points[i];
				const auto& [xj, yj] = points[j];

				unsigned long long currentArea = std::abs(xi - xj + 1) * std::abs(yi - yj + 1);

				if (currentArea > largestArea) [[unlikely]] {
					largestArea = currentArea;
				}
			}
		}

		return largestArea;
	}

	inline long star2(const char* path) noexcept {
		InputReader parser(path, R"((\d+),(\d+))");

		std::vector<std::tuple<long long, long long>> points;
		long long x, y;
		while (parser.getNextMatch(x, y)) {
			points.push_back(std::make_tuple(x, y));
		}

		unsigned long long largestArea = 0;
		for (size_t i = 0; i < points.size(); i++) {
			for (size_t j = 0; j < points.size(); j++) {
				if (i == j) {
					continue;
				}

				const auto& [xi, yi] = points[i];
				const auto& [xj, yj] = points[j];

				unsigned long long currentArea = std::abs(xi - xj + 1) * std::abs(yi - yj + 1);

				if (currentArea > largestArea) [[unlikely]] {
					bool isInPerimiter = true;
					for (size_t k = 0; k < points.size(); k++) {
						const auto& [xk, yk] = points[k];
						if ((std::min(xi, xj) < xk && xk < std::max(xi, xj)) &&
							(std::min(yi, yj) < yk && yk < std::max(yi, yj))) {
							isInPerimiter = false;
							break;
						}
					}

					if (isInPerimiter) {
						largestArea = currentArea;
					}
				}
			}
		}

		return largestArea;
	}
}