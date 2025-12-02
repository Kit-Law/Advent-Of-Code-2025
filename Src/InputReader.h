#pragma once

#include <fstream>
#include <regex>
#include <optional>

class InputReader {
private:
	std::fstream _input;
	std::string _currentLine;

	std::regex _regexPattern;
	std::optional<const char> _delimiter;

public:
	inline InputReader(const char* path, const char* regexPattern, std::optional<const char> delimiter = {})
		: _input{ path }, _regexPattern{ regexPattern }, _delimiter{ delimiter } {
	}

	inline bool empty() const { return _input.eof() && _currentLine.empty(); }
	inline operator bool() const { return !empty(); }

	template <typename... Args>
	inline bool getNextMatch(Args&... args) {
		if (empty()) {
			return false;
		}

		std::string token = getToken();
		std::smatch match;

		if (!std::regex_match(token, match, _regexPattern)) {
			throw std::runtime_error("Unable to read rotation: " + token);
		}

		constexpr std::size_t N = sizeof...(Args);
		if (match.size() < 1 + N) {
			throw std::runtime_error("Regex has fewer capture groups than required arguments");
		}

		int i = 1;
		((args = [&] {
			using T = std::remove_reference_t<Args>;
			std::string s = match[i++].str();

			if constexpr (std::is_same_v<T, std::string>) {
				return s;
			}
			else if constexpr (std::is_same_v<T, char>) {
				return static_cast<T>(s[0]);
			}
			else if constexpr (std::is_integral_v<T>) {
				if constexpr (std::is_signed_v<T>) {
					return static_cast<T>(std::stoll(s));
				}
				else {
					return static_cast<T>(std::stoull(s));
				}
			}
			else {
				static_assert(!sizeof(T), "Unsupported type in getNextMatch");
			}
			}()), ...);

		return true;
	}

	template <typename... Args>
	inline bool getNextMatch(std::regex pattern, Args&... args) {
		std::regex pattenBuffer = _regexPattern;
		_regexPattern = pattern;
		getNextMatch(args);
		_regexPattern = pattenBuffer;
	}

	inline std::vector<std::string> readLinesUntil(std::string exitStr = "") {
		std::string line;
		std::vector<std::string> lines;

		while (std::getline(_input, line)) {
			if (line == exitStr) {
				return lines;
			}

			lines.push_back(line);
		}

		return lines;
	}

	inline std::vector<std::string> readNLines(const size_t numberOfLines) {
		std::string line;
		std::vector<std::string> lines;

		for (size_t count = 0; count < numberOfLines; count++) {
			if (!std::getline(_input, line)) {
				return lines;
			}

			lines.push_back(line);
		}

		return lines;
	}

private:
	inline std::string getToken() {
		std::string token;
		if (!_delimiter) {
			std::getline(_input, token);
			return token;
		}

		if (_currentLine.empty())
			std::getline(_input, _currentLine);

		size_t pos = _currentLine.find(*_delimiter);
		if (pos == std::string::npos) {
			token = _currentLine;
			_currentLine.clear();
		}
		else {
			token = _currentLine.substr(0, pos);
			_currentLine.erase(0, pos + 1);
		}

		return token;
	}
};