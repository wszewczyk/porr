#ifndef HELPER_H
#define HELPER_H
#include <vector>
#include <string>
#include <iostream>

struct Helper
{
	static void PrintTable(unsigned char** table, int size);
	static void PrintVector(std::vector<std::vector<unsigned char>> table);
	static void PrintVectorMatrix(const std::vector<std::vector<unsigned char>>& v);
	static std::vector<std::vector<unsigned char>> ConvertArrayToVector(unsigned char Array[][4], std::vector<std::vector<unsigned char>> vect);
};

#endif // !HELPER_H