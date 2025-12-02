#pragma once

#include <fstream>
#include <sstream>

namespace Day1 {

	inline constexpr int STARTING_POSITION = 50;
	inline constexpr int MAX_POSITION = 100;

	inline long star1(const char* path)
	{
		int dialPosition = STARTING_POSITION;
		long zeroCounts = 0;

		std::fstream input(path);
		std::string rotation;
		while (std::getline(input, rotation))
		{
			char direction;
			int degree;
			if (sscanf(rotation.c_str(), "%c%d", &direction, &degree) <= 0)
			{
				std::string errMessage = std::string("Unable to read roation: ") + rotation;
				throw std::exception(errMessage.c_str());
			}

			dialPosition = (direction == 'L' ? dialPosition - degree : dialPosition + degree) % 100;

			if (!dialPosition) {
				zeroCounts++;
			}
		}

		return zeroCounts;
	}

	inline long star2(const char* path) noexcept
	{
		int dialPosition = STARTING_POSITION;
		long zeroCounts = 0;
		long altZeroCounts = zeroCounts;

		std::fstream input(path);
		std::string rotation;
		while (std::getline(input, rotation))
		{
			char direction;
			int degree;
			if (sscanf(rotation.c_str(), "%c%d", &direction, &degree) <= 0)
			{
				std::string errMessage = std::string("Unable to read roation: ") + rotation;
				throw std::exception(errMessage.c_str());
			}

			if (direction == 'L')
			{
				while (degree)
				{
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
			else 
			{
				while (degree)
				{
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