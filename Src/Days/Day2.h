#pragma once

#include <fstream>
#include <sstream>

namespace Day2 {

	inline constexpr char delimiter = ',';
	inline constexpr char delimiterSize = 1;

	inline unsigned long long star1(const char* path) noexcept
	{
		unsigned long long symetricNumbers = 0;

		std::fstream input(path);
		std::string line;
		while (std::getline(input, line))
		{
			size_t pos = 0;
			std::string token;
			while (!line.empty() && pos != std::string::npos) {
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiterSize);

				unsigned long long startingValue;
				unsigned long long finalValue;
				if (sscanf(token.c_str(), "%llu-%llu", &startingValue, &finalValue) <= 0)
				{
					std::string errMessage = std::string("Unable to read roation: ") + token;
					throw std::exception(errMessage.c_str());
				}

				for (unsigned long long testValue = startingValue; testValue <= finalValue; testValue++)
				{
					unsigned short numberOfDigits = (int)log10((double)testValue) + 1;

					if (numberOfDigits % 2 == 1) {
						continue;
					}

					unsigned long long lhs = testValue / pow(10, numberOfDigits / 2);
					unsigned long long rhs = testValue % (int)pow(10, numberOfDigits / 2);

					if (lhs == rhs)
					{
						symetricNumbers += testValue;
					}
				}
			}
		}

		return symetricNumbers;
	}

	inline unsigned long long star2(const char* path) noexcept
	{
		unsigned long long symetricNumbers = 0;

		std::fstream input(path);
		std::string line;
		while (std::getline(input, line))
		{
			size_t pos = 0;
			std::string token;
			while (!line.empty() && pos != std::string::npos) {
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiterSize);

				unsigned long long startingValue;
				unsigned long long finalValue;
				if (sscanf(token.c_str(), "%llu-%llu", &startingValue, &finalValue) <= 0)
				{
					std::string errMessage = std::string("Unable to read roation: ") + token;
					throw std::exception(errMessage.c_str());
				}

				for (unsigned long long testValue = startingValue; testValue <= finalValue; testValue++)
				{
					unsigned short numberOfDigits = (int)log10((double)testValue) + 1;

					for (size_t patternLength = 1; patternLength <= numberOfDigits / 2; patternLength++) {
						if (numberOfDigits % patternLength != 0) {
							continue;
						}

						const unsigned int patternLengthShift = pow(10, patternLength);
						unsigned long long remainder = testValue / patternLengthShift;
						unsigned long long pattern = testValue % patternLengthShift;

						bool foundInvalidId = true;

						while (remainder > 0) {
							unsigned long long prefix = remainder % patternLengthShift;

							if (prefix != pattern) {
								foundInvalidId = false;
								break;
							}

							remainder /= patternLengthShift;
						}

						if (foundInvalidId) {
							symetricNumbers += testValue;
							break;
						}
					}
				}
			}
		}

		return symetricNumbers;
	}
}