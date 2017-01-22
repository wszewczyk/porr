#include "stdafx.h"
#include "stdafx.h"
#include "AES.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
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

	std::vector<std::vector<unsigned char>> enchancedKey(4, std::vector<unsigned char>(4));

	string key = "abcdefgh";
	//Generating array for key.
	AES aes = AES();
	enchancedKey = aes.GenerateKey(key);
	for (int j = 0; j < 40; j++)
	{
		vector<unsigned char> v(4);
		v = aes.MixColumns(enchancedKey, j);  // extanding vector
		for (int i = 0; i < 4; i++)
		{
			enchancedKey[i].push_back(v[i]);	//Generating keys in one big vector (instead of separated)
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
		AllStates[i] = aes.Encrypt(AllStates[i], enchancedKey);
	}
	double end = omp_get_wtime();
	double time_s = 1000 * (end - checkpoint);
	cout << "Czas szyfrowania - wersja sekwencyjna: " << time_s << endl;



	omp_set_num_threads(2);
	checkpoint = omp_get_wtime();
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = aes.GenerateState(Strings[i]);
		AllStates[i] = aes.Encrypt(AllStates[i], enchancedKey);
	}
	end = omp_get_wtime();
	double time_p = 1000 * (end - checkpoint);
	cout << "Czas szyfrowania - omp: " << time_p << endl;

	ofstream myfile;
	myfile.open("results.txt", std::ios::app);
	myfile << numOfBlocks << " " << time_s << " " << time_p <<"\n";
	myfile.close();

	int finish;
	cin >> finish;

}
