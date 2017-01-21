#include "stdafx.h"
#include "Helper.h"

struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(unsigned char _c) : c(_c) { }
};


inline HexCharStruct hex(unsigned char _c)
{
	return HexCharStruct(_c);
}

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::hex << (int)hs.c);
}



void Helper::PrintTable(unsigned char** table, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << hex(table[i][j]) << " ";
			//std::stringstream ss;
			//ss<<table[i][j];
			//cout<<ss.str()<<" ";
		}
		std::cout << std::endl;
	}
}

void Helper::PrintVector(std::vector<std::vector<unsigned char>> table)
{
	//cout<<endl;
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			//cout<< hex(table[i][j])<<" ";
		}
		//cout<<endl;
	}
}

void Helper::PrintVectorMatrix(const std::vector<std::vector<unsigned char>>& v) {
	//vector<int> v;
	for (int i = 0; i<v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++)
		{
			std::cout << v[i][j];
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<unsigned char>> Helper::ConvertArrayToVector(unsigned char Array[][4], std::vector<std::vector<unsigned char> > vect)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vect[i][j] = Array[i][j];
		}
	}
	return vect;
}
