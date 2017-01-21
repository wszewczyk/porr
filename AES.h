#ifndef AES_H
#define AES_H
#include <vector>
#include <string>
#include <iostream>
struct AES
{
	static std::vector<unsigned char> AES::MixCols(std::vector<std::vector<unsigned char>> vect1, int IterationNumber);
	static std::vector<std::vector<unsigned char>> RotateAndSubByteKeyColumn(std::vector<std::vector<unsigned char>> vect, int Columnindex);
	static unsigned char sbox[256];
	static unsigned char Rcon[40];
	static unsigned char GetSboxValue(unsigned char x);
	static std::vector<std::vector<unsigned char>> GenerateKey(std::string input);
	static std::vector<std::vector<unsigned char>> GenerateEnhancedKey(std::vector<std::vector<unsigned char>> vect1);
	static unsigned char** GenerateState(std::string input);
	static unsigned char** GetMainLoopOutput(unsigned char** input, std::vector<std::vector<unsigned char> > keys);
	static unsigned char** AddRoundKey(unsigned char** matrix, unsigned char** key, int size = 4);
	static unsigned char** GetSubBytes(unsigned char** tablica);
	static unsigned char** GetShiftRowTable(unsigned char** firsttable);
	static unsigned char* RotateLeft(unsigned char* row);
	static unsigned char** MixColumn(unsigned char** matrix);
	static void GmixColumn(unsigned char r[]);
	std::vector<unsigned char> MixColumns(std::vector<std::vector<unsigned char> > vect1, int IterationNumber);
};

#endif // !AES_H