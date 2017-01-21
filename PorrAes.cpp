
#pragma once
#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>
# include <string>
#include <sstream>
#include <vector>
#include <mpi.h>
#include<ctime>

using namespace std;

unsigned char Rcon[40] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};


unsigned char s[256] =
{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};


struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
	return HexCharStruct(_c);
}



struct AES
{
	unsigned char sbox[256];

	std::vector<vector<unsigned char> > keys;

	unsigned char** GetSubBytes(unsigned char**  tablica)
	{
		unsigned char **newchar = new unsigned char *[4];
		for (int i = 0; i < 4; i++)
		{
			newchar[i] = new unsigned char[4];
			for (int j = 0; j < 4; j++)
			{
				newchar[i][j] = getsboxvalue(tablica[i][j]);

				//cout << hex(newchar[i][j]) << "  ";
			}
			//cout << endl;
		}
		return newchar;
	}

	unsigned char getsboxvalue(unsigned char x)
	{
		unsigned char d;
		for (int i = 0; i < 256; i++)
		{
			if ((int)x == i)
			{
				d = sbox[i];

				break;
			}
		}
		return d;
	}

	unsigned char ** GetShiftRowTable(unsigned char ** firsttable)
	{
		unsigned char** mat = new unsigned char*[4];
		int j = 0;
		for (int i = 0; i < 4; i++)
		{
			mat[i] = new unsigned char[4];
			unsigned char* dd = new unsigned char[4];
			for (int d = 0; d < j; d++)
			{
				dd = RotateLeft(firsttable[i]);
			}
			j++;
		}
		return firsttable;
	}

	unsigned char* RotateLeft(unsigned char * row)
	{
		unsigned char* buffer = new unsigned char;
		*buffer = row[0];
		for (int i = 0; i < 3; i++)
		{
			row[i] = row[i + 1];
		}
		row[3] = *buffer;
		return row;
	}

	unsigned char ** MixColumn(unsigned char ** matrix)
	{
		unsigned char **mat = new unsigned char*[4];
		unsigned char column[4];
		for (int i = 0; i < 4; i++)
		{
			mat[i] = new unsigned char[4];

		}
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				column[i] = matrix[i][j];
			}
			gmix_column(column);
			for (int i = 0; i < 4; i++)
			{
				mat[i][j] = column[i];
			}
		}
		return mat;
	}

	unsigned char** AddRoundKey(unsigned char** matrix, unsigned char** key, int size = 4)
	{
		unsigned char**result = new unsigned char*[size];
		for (int i = 0; i < size; i++)
		{
			result[i] = new unsigned char[size];
			for (int j = 0; j < size; j++)
			{
				result[i][j] = matrix[i][j] ^ key[i][j];
			}
		}
		return result;
	}

	void gmix_column(unsigned char r[]) {		// ta funkcja jest skopiowana z neta, srednio ja ogarniam
		unsigned char a[4];	// operacja mixcolumns
		unsigned char b[4];
		unsigned char c;
		unsigned char h;
		/* The array 'a' is simply a copy of the input array 'r'
		* The array 'b' is each element of the array 'a' multiplied by 2
		* in Rijndael's Galois field
		* a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */
		for (c = 0; c < 4; c++) {
			a[c] = r[c];
			/* h is 0xff if the high bit of r[c] is set, 0 otherwise */
			h = (unsigned char)((signed char)r[c] >> 7);
			/* arithmetic right shift, thus shifting in either zeros or ones */
			b[c] = r[c] << 1;
			/* implicitly removes high bit because b[c] is an 8-bit char,
			so we xor by 0x1b and not 0x11b in the next line */
			b[c] ^= 0x1B & h; /* Rijndael's Galois field */
		}
		r[0] = (b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]); /* 2 * a0 + a3 + a2 + 3 * a1 */
		r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
		r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
		r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
	}


	void InitializeArray(unsigned char** Array, int x = 4, int y = 4)
	{
		Array = new unsigned char*[x];
		for (int i = 0; i < x; i++)
		{
			Array[i] = new unsigned char[y];

		}
	}


	vector<vector<unsigned char> > RotateAndSubByteKeyColumn(vector<vector<unsigned char> > vect, int Columnindex)
	{
		unsigned char buffer[4];
		for (int i = 0; i < vect.size(); i++)
		{
			buffer[i] = vect[i][Columnindex];

		}

		unsigned char a = buffer[0];
		for (int i = 0; i < 3; i++)
		{
			buffer[i] = buffer[i + 1];
		}
		buffer[3] = a;
		for (int i = 0; i < vect.size(); i++)
		{
			vect[i][Columnindex] = buffer[i];
			vect[i][Columnindex] = getsboxvalue(vect[i][Columnindex]);

		}

		return vect;
	}


	vector<unsigned char> MixColumns(vector<vector<unsigned char> > vect1, int IterationNumber)
	{
		unsigned char first[4];
		unsigned char second[4];
		vector<unsigned char> result(4);
		if (IterationNumber % 4 == 0)
		{	//PrintVector(vect1);
			vect1 = RotateAndSubByteKeyColumn(vect1, IterationNumber + 3);
			//PrintVector(vect1);
			for (int i = 0; i < 4; i++)
			{
				first[i] = vect1[i][IterationNumber];
				second[i] = vect1[i][IterationNumber + 3];
				result[i] = first[i] ^ second[i] ^ Rcon[10 * i + IterationNumber / 4];
				//cout<<endl<< hex(first[i]) <<"  "<<hex(second[i])<<"  "<<hex(Rcon[10*i + IterationNumber])<<"  "<<hex(result[i])<<endl;
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				first[i] = vect1[i][IterationNumber];
				second[i] = vect1[i][IterationNumber + 3];
				result[i] = first[i] ^ second[i];
			}
		}

		return result;
	}

	unsigned char** GetMainLoopOutput(unsigned char** input, vector<vector<unsigned char> > keys)
	{

		unsigned char*** KeyMatrix;
		KeyMatrix = new unsigned char**[11];
		for (int i = 0; i < 11; i++)
		{
			KeyMatrix[i] = new unsigned char*[4];
			for (int j = 0; j < 4; j++)
			{
				KeyMatrix[i][j] = new unsigned char[4];
			}
		}
		int KeyMatrixIndex = 0;
		int d = 0;
		//cout<<keys.size()<<" "<<keys[0].size();
		for (int i = 0; i < keys[0].size(); i++)
		{
			if ((i) % 4 == 0 && i != 0)
			{
				d = 0;
				KeyMatrixIndex++;
				//PrintTable(KeyMatrix[KeyMatrixIndex],4);
			}
			for (int j = 0; j < keys.size(); j++)
			{	//cout<<hex(keys[i][j])<<endl;
				KeyMatrix[KeyMatrixIndex][j][d] = keys[j][i];	// w sumie niepotrzebnie tworze to KeyMatrix
			}	//ale juz mi sie nie chce przerabiac
			d++;	// to sa macierze kluczy tworzonych w key schedule
		}


		input = AddRoundKey(input, KeyMatrix[0]);	// tutaj zaczyna sie program wlasciwy, dzialanie zgodne z symulacja

		for (int i = 1; i < 10; i++)
		{
			input = GetSubBytes(input);
			input = GetShiftRowTable(input);
			input = MixColumn(input);
			input = AddRoundKey(input, KeyMatrix[i]);
		}

		input = GetSubBytes(input);
		input = GetShiftRowTable(input);
		input = AddRoundKey(input, KeyMatrix[10]);



		return input;
	}


	void PrintVector(vector<vector<unsigned char> > table)
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
	void PrintTable(unsigned char** table, int size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << hex(table[i][j]) << " ";
				//std::stringstream ss;
				//ss<<table[i][j];
				//cout<<ss.str()<<" ";
			}
			cout << endl;
		}
	}

};





vector<vector<unsigned char> > ConvertArrayToVector(unsigned char Array[][4], vector<vector<unsigned char> > vect)
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

vector<vector<unsigned char> > GenerateKey(string input)	// tworzenie klucza na podstawie tekstu wejsiowego
{
	vector<vector<unsigned char> > out(4, std::vector<unsigned char>(4));
	int x = 0;
	int y = 0;
	for (int i = 0; i < input.size(); i++)
	{

		if ((i) % 1 == 0 && i != 0)
		{
			y++;
		}

		if (i % 4 == 0 && i != 0)
		{
			x++;
			y = 0;
		}
		out[y][x] += input[i];
		if (x > 3)
			break;
	}
	return out;
}

unsigned char** GenerateState(string input)	// funkcja uzupelnia macierz stanu przy pomocy wejsiowego tekstu
{
	unsigned char** State = new unsigned char*[4];
	for (int i = 0; i < 4; i++)
	{
		State[i] = new unsigned char[4];
		for (int j = 0; j < 4; j++)
		{
			State[i][j] = 0x00;
		}
	}

	int x = 0;
	int y = 0;
	for (int i = 0; i < input.size(); i++)
	{

		if (i % 1 == 0 && i != 0)
		{
			y++;
		}
		if (i % 4 == 0 && i != 0)
		{
			x++;
			y = 0;
		}
		State[y][x] += input[i];
		if (x > 3)
			break;
	}
	return State;
}



int main()
{
	int numOfBlocks;
	cin >> numOfBlocks;

	double start = omp_get_wtime();

	AES aes;
	for (int i = 0; i < 256; i++)
	{
		aes.sbox[i] = s[i];
	}



	std::vector<std::vector<unsigned char> > vect1(4, std::vector<unsigned char>(4));


	string key = "klucz";
	//przerobienie klucza na tablice CipherKey
	vect1 = GenerateKey(key);
	for (int j = 0; j < 40; j++)
	{
		vector<unsigned char> v(4);
		v = aes.MixColumns(vect1, j);  // cala operacja rozszerzania wektora
		for (int i = 0; i < 4; i++)
		{
			vect1[i].push_back(v[i]);	//tworzenie kolejnych kluczy, nie robilem oddzielnych tylko wrzucilem do jednego dlugiego wektora
		}


	}


	string input = "1234abcd1234abcd";
	string block = input;
	for (int i = 1; i < numOfBlocks; i++)
	{
		input += block;
	}

	double d = input.size() / 16.0;
	int n = input.size() / 16;
	if (n < d)
	{
		n++;	//n - liczba macierzy stanu
	}

	//cout<<"LICZBA BLOKOW TEKSTU: "<<n<<endl;

	unsigned char*** AllStates = new unsigned char**[n];	//tworzenie wszystkich macierzy stanu
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = new unsigned char*[4];
		for (int j = 0; j < 4; j++)
		{
			AllStates[i][j] = new unsigned char[4];

		}
	}

	vector<string> Strings(n);		//podzial tekstu do zaszyfrowania na teksty 16 literowe
	int index = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (i % 16 == 0 && i != 0)
		{
			index++;
		}
		Strings[index] += input[i];
	}


	double checkpoint = omp_get_wtime();
	//cout<<"CZAS PRZYGOTOWANIA: "<<1000*(checkpoint-start)<<endl;
	cout << n << " " << 1000 * (checkpoint - start) << " ";

	omp_set_num_threads(2);
	cout << "Threads: " << omp_get_num_threads() << endl;
#pragma omp parallel for private(i)
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = GenerateState(Strings[i]);
		AllStates[i] = aes.GetMainLoopOutput(AllStates[i], vect1);
	}

	double end = omp_get_wtime();
	cout << "CZAS LICZENIA: " << 1000 * (end - checkpoint) << endl;

	int f;
	cin >> f;
	return 0;
}


