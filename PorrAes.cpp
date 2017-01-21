#pragma once
#include "stdafx.h"
#include "stdafx.h"
#include "AES.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>
# include <string>
#include <sstream>
#include <vector>
#include <mpi.h>
#include <ctime>
#include "Helper.h"

using namespace std;

int main()
{
	int numOfBlocks;
	cin >> numOfBlocks;

	double start = omp_get_wtime();

	std::vector<std::vector<unsigned char>> vect1(4, std::vector<unsigned char>(4));

	string key = "klucz";
	//przerobienie klucza na tablice CipherKey
	AES aes = AES();
	vect1 = aes.GenerateKey(key);
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
	//in class
	unsigned char*** AllStates = new unsigned char**[n];	//tworzenie wszystkich macierzy stanu
	for (int i = 0; i < n; i++)
	{
		AllStates[i] = new unsigned char*[4];
		for (int j = 0; j < 4; j++)
		{
			AllStates[i][j] = new unsigned char[4];

		}
	}

	//in class
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


#pragma omp parallel for
	cout << "ZASZYFROWANE";
	for (int i = 0; i < n; i++)		//
	{
		AllStates[i] = aes.GenerateState(Strings[i]);		// odpowiednie uzupelnianie macierzy stanu
		//cout<<endl<<Strings[i]<<endl;
		AllStates[i] = aes.GetMainLoopOutput(AllStates[i], vect1);	// cala operacja szyfrujaca
		Helper::PrintTable(AllStates[i], 4);
		//aes.PrintTable(AllStates[i],4);
	}

	double end = omp_get_wtime();
	cout << "CZAS LICZENIA: " << 1000 * (end - checkpoint) << endl;
	cout << 1000 * (end - checkpoint) << endl;

	int f;
	cin >> f;
	return 0;

	//int numOfBlocks = 10000;
	////cout<<"Podaj liczbê bloków do testowego szyfrowania:\n";
	////cin>>numOfBlocks;

	//clock_t begin = clock();


	//AES aes;
	//for (int i = 0; i < 256; i++)
	//{
	//	aes.sbox[i] = s[i];
	//}



	//std::vector<std::vector<unsigned char> > vect1(4, std::vector<unsigned char>(4));


	//string key = "klucz";
	////przerobienie klucza na tablice CipherKey
	//vect1 = GenerateKey(key);
	//for (int j = 0; j<40; j++)
	//{
	//	vector<unsigned char> v(4);
	//	v = aes.MixColumns(vect1, j);  // cala operacja rozszerzania wektora
	//	for (int i = 0; i<4; i++)
	//	{
	//		vect1[i].push_back(v[i]);	//tworzenie kolejnych kluczy, nie robilem oddzielnych tylko wrzucilem do jednego dlugiego wektora
	//	}


	//}


	//string input = "1234abcd1234abcd";
	//string block = input;
	//for (int i = 1; i<numOfBlocks; i++)
	//{
	//	input += block;
	//}

	//double d = input.size() / 16.0;
	//int n = input.size() / 16;
	//if (n<d)
	//{
	//	n++;	//n - liczba macierzy stanu
	//}

	////cout<<"LICZBA BLOKOW TEKSTU: "<<n<<endl;


	//vector<string> Strings(n);		//podzial tekstu do zaszyfrowania na teksty 16 literowe
	//int index = 0;
	//for (int i = 0; i<input.size(); i++)
	//{
	//	if (i % 16 == 0 && i != 0)
	//	{
	//		index++;
	//	}
	//	Strings[index] += input[i];
	//}

	//unsigned char*** AllStates = new unsigned char**[n];	//tworzenie wszystkich macierzy stanu
	//for (int i = 0; i<n; i++)
	//{
	//	AllStates[i] = new unsigned char*[4];
	//	for (int j = 0; j<4; j++)
	//	{
	//		AllStates[i][j] = new unsigned char[4];

	//	}
	//}





	//// Initialize the MPI environment
	//MPI_Init(NULL, NULL);

	//// Get the number of processes
	//int world_size;
	//MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	//// Get the rank of the process
	//int world_rank;
	//MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);






	//clock_t checkpoint = clock();

	//for (int i = 1; i<world_size; i++)
	//{
	//	if (world_rank == i) {
	//		for (int j = i - 1; j<n; j += world_size - 1)
	//		{
	//			AllStates[j] = GenerateState(Strings[j]);
	//			AllStates[j] = aes.GetMainLoopOutput(AllStates[j], vect1);
	//			MPI_Send(AllStates[j], 4, MPI_BYTE, 0, j, MPI_COMM_WORLD);
	//		}
	//	}
	//}
	//if (!world_rank)
	//{
	//	for (int i = 0; i<n; i++)
	//	{
	//		MPI_Recv(AllStates[i], 4, MPI_BYTE, (i % (world_size - 1)) + 1, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//		//cout<<"WATEK "<<world_rank<<" !!!!!!\n";
	//	}
	//	for (int i = 0; i<n; i++)
	//	{
	//		//cout<<AllStates[i][1][1];
	//	}
	//}




	//MPI_Finalize();

	//clock_t end = clock();
	//if (!world_rank) {
	//	cout << world_rank << ": Czas przygotowania: " << double(checkpoint - begin) / CLOCKS_PER_SEC << endl;
	//	cout << world_rank << ": Czas równoleg³ego szyfrowania: " << double(end - checkpoint) / CLOCKS_PER_SEC << endl;
	//	//cout<<CLOCKS_PER_SEC;
	//	cout << "koniec";
	//}
	//return 0;


}

