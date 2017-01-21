#include "stdafx.h"
#include "stdafx.h"
#include "AES.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>
# include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include "Helper.h"

using namespace std;

int main()
{
	int numOfBlocks;
	cin >> numOfBlocks;

	double start = omp_get_wtime();

	std::vector<std::vector<unsigned char>> vect1(4, std::vector<unsigned char>(4));

	string key = "abcdefgh";
	//Generating array for key.
	AES aes = AES();
	vect1 = aes.GenerateKey(key);
	for (int j = 0; j < 40; j++)
	{
		vector<unsigned char> v(4);
		v = aes.MixColumns(vect1, j);  // extanding vector
		for (int i = 0; i < 4; i++)
		{
			vect1[i].push_back(v[i]);	//Generating keys in one big vector (instead of separated)
		}
	}

	string input = "abcdfghijklmnopr";
	string block = input;
	for (int i = 1; i < numOfBlocks; i++)
	{
		input += block;
	}

	double d = input.size() / 16.0;
	int n = input.size() / 16;
	if (n < d)
	{
		n++;	//n - number of matrix states
	}

	unsigned char*** AllStates = new unsigned char**[n];	//creating states
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = new unsigned char*[4];
		for (int j = 0; j < 4; j++)
		{
			AllStates[i][j] = new unsigned char[4];

		}
	}

	vector<string> Strings(n);
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
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = aes.GenerateState(Strings[i]);
		AllStates[i] = aes.Encrypt(AllStates[i], vect1);
	}
	double end = omp_get_wtime();
	cout << "Czas szyfrowania - wersja sekwencyjna: " << 1000 * (end - checkpoint) << endl;



	omp_set_num_threads(2);
	checkpoint = omp_get_wtime();
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = aes.GenerateState(Strings[i]);
		AllStates[i] = aes.Encrypt(AllStates[i], vect1);
	}
	end = omp_get_wtime();
	cout << "Czas szyfrowania - omp: " << 1000 * (end - checkpoint) << endl;

	int finish;
	cin >> finish;

}
