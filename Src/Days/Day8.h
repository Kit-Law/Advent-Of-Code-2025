#pragma once

#include "./InputReader.h"

namespace Day8 {

	constexpr size_t NUMBER_OF_CLOSEST_REGISTERS = 1000;

	inline std::vector<std::tuple<int, int, int>> populateRegisters(InputReader& parser) {
		std::vector<std::tuple<int, int, int>> registers;

		int x, y, z;
		while (parser.getNextMatch(x, y, z)) {
			registers.push_back(std::make_tuple(x, y, z));
		}

		return registers;
	}

	inline std::vector<std::vector<double>> fillAdjacencyMatrix(const std::vector<std::tuple<int, int, int>>& registers) {
		std::vector<std::vector<double>> adjacencyMatrix;

		for (size_t from = 0; from < registers.size() - 1; from++) {
			adjacencyMatrix.push_back(std::vector<double>());
			adjacencyMatrix.back().resize(registers.size());
			for (size_t to = from + 1; to < registers.size(); to++) {
				double magnitude = 0;
				magnitude += std::pow((double)std::abs(std::get<0>(registers[from]) - std::get<0>(registers[to])), 2);
				magnitude += std::pow((double)std::abs(std::get<1>(registers[from]) - std::get<1>(registers[to])), 2);
				magnitude += std::pow((double)std::abs(std::get<2>(registers[from]) - std::get<2>(registers[to])), 2);
				adjacencyMatrix[from][to] = std::sqrt(magnitude);
			}
		}

		return adjacencyMatrix;
	}

	inline unsigned long long star1(const char* path) noexcept {
		InputReader parser(path, R"((\d+),(\d+),(\d+))");

		std::vector<std::tuple<int, int, int>> registers =
			populateRegisters(parser);

		std::vector<std::vector<double>> adjacencyMatrix = fillAdjacencyMatrix(registers);

		std::vector<std::tuple<size_t, size_t>> closestRegisters;
		for (size_t from = 0; from < registers.size() - 1; from++) {
			for (size_t to = from + 1; to < registers.size(); to++) {
				std::tuple<size_t, size_t> connection(from, to);
				closestRegisters.emplace_back(connection);
			}
		}

		std::sort(closestRegisters.begin(), closestRegisters.end(), [&](std::tuple<size_t, size_t>& lhs, std::tuple<size_t, size_t>& rhs) {
			return adjacencyMatrix[std::get<0>(lhs)][std::get<1>(lhs)] < adjacencyMatrix[std::get<0>(rhs)][std::get<1>(rhs)];
		});

		std::vector<std::vector<size_t>> grapths;

		for (size_t connection = 0; connection < NUMBER_OF_CLOSEST_REGISTERS; connection++) {
			const auto& [from, to] = closestRegisters[connection];

			std::optional<size_t> fromGrapth = {};
			std::optional<size_t> toGrapth = {};
			for (size_t grapth = 0; grapth < grapths.size(); grapth++) {
				auto& connections = grapths[grapth];
				if (std::find(connections.begin(), connections.end(), from) != connections.end())
					fromGrapth = grapth;
				if (std::find(connections.begin(), connections.end(), to) != connections.end())
					toGrapth = grapth;
			}

			if (fromGrapth && toGrapth) {
				if (*fromGrapth == *toGrapth) {
					continue;
				}
				grapths[*fromGrapth].insert(grapths[*fromGrapth].end(), grapths[*toGrapth].begin(), grapths[*toGrapth].end());
				grapths[*toGrapth].clear();
			}
			else if (fromGrapth) {
				grapths[*fromGrapth].push_back(to);
			}
			else if (toGrapth) {
				grapths[*toGrapth].push_back(from);
			}
			else {
				grapths.push_back({from, to});
			}
		}

		std::sort(grapths.begin(), grapths.end(), [&](std::vector<size_t>& lhs, std::vector<size_t>& rhs) {
			return lhs.size() > rhs.size();
		});

		return (unsigned long long)grapths[0].size() * (unsigned long long)grapths[1].size() * (unsigned long long)grapths[2].size();
	}

	inline long star2(const char* path) noexcept {
		InputReader parser(path, R"((\d+),(\d+),(\d+))");

		std::vector<std::tuple<int, int, int>> registers =
			populateRegisters(parser);

		std::vector<std::vector<double>> adjacencyMatrix = fillAdjacencyMatrix(registers);

		std::vector<std::tuple<size_t, size_t>> closestRegisters;
		for (size_t from = 0; from < registers.size() - 1; from++) {
			for (size_t to = from + 1; to < registers.size(); to++) {
				std::tuple<size_t, size_t> connection(from, to);
				closestRegisters.emplace_back(connection);
			}
		}

		std::sort(closestRegisters.begin(), closestRegisters.end(), [&](std::tuple<size_t, size_t>& lhs, std::tuple<size_t, size_t>& rhs) {
			return adjacencyMatrix[std::get<0>(lhs)][std::get<1>(lhs)] < adjacencyMatrix[std::get<0>(rhs)][std::get<1>(rhs)];
			});

		std::vector<std::vector<size_t>> grapths;

		for (size_t connection = 0; connection < closestRegisters.size(); connection++) {
			const auto& [from, to] = closestRegisters[connection];

			std::optional<size_t> fromGrapth = {};
			std::optional<size_t> toGrapth = {};
			for (size_t grapth = 0; grapth < grapths.size(); grapth++) {
				auto& connections = grapths[grapth];
				if (std::find(connections.begin(), connections.end(), from) != connections.end())
					fromGrapth = grapth;
				if (std::find(connections.begin(), connections.end(), to) != connections.end())
					toGrapth = grapth;
			}

			if (fromGrapth && toGrapth) {
				if (*fromGrapth == *toGrapth) {
					continue;
				}
				grapths[*fromGrapth].insert(grapths[*fromGrapth].end(), grapths[*toGrapth].begin(), grapths[*toGrapth].end());
				grapths[*toGrapth].clear();

				if (grapths[*fromGrapth].size() == adjacencyMatrix.size() + 1) {
					return (unsigned long long)std::get<0>(registers[from]) * (unsigned long long)std::get<0>(registers[to]);
				}
			}
			else if (fromGrapth) {
				grapths[*fromGrapth].push_back(to);

				if (grapths[*fromGrapth].size() == adjacencyMatrix.size() + 1) {
					return (unsigned long long)std::get<0>(registers[from]) * (unsigned long long)std::get<0>(registers[to]);
				}
			}
			else if (toGrapth) {
				grapths[*toGrapth].push_back(from);

				if (grapths[*toGrapth].size() == adjacencyMatrix.size() + 1) {
					return (unsigned long long)std::get<0>(registers[from]) * (unsigned long long)std::get<0>(registers[to]);
				}
			}
			else {
				grapths.push_back({ from, to });
			}
		}

		return 0;
	}
}