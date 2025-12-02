#include <iostream>

#include "Days/Day1.h"
#include "Days/Day2.h"
#include "Days/Day3.h"
#include "Days/Day4.h"
#include "Days/Day5.h"
#include "Days/Day6.h"
#include "Days/Day7.h"
#include "Days/Day8.h"
#include "Days/Day9.h"
#include "Days/Day10.h"
#include "Days/Day11.h"
#include "Days/Day12.h"

#define SOLUTION(day) { std::cout << #day << ": Star 1 = " << day::star1("Input/" #day ".txt") << ", Star 2 = " << day::star2("Input/" #day ".txt") << std::endl; }

int main()
{
	try
	{
		SOLUTION(Day2);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}