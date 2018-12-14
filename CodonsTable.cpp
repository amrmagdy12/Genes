#include "stdafx.h"
#include "CodonsTable.h"
#include <fstream>
#include <iostream>

using namespace std; 

CodonsTable::CodonsTable()
{

}
void CodonsTable::LoadCodonsFromFile(char * codonsFileName)
{
	char valuEs[4];
	char amino;

	ifstream inFile;
	inFile.open(codonsFileName);
	if (!inFile) {
		cout << "Unable to open file datafile.txt";
	}
	for (int i = 0; i < 64; i++) {
		inFile >> valuEs;
		if (i == 48 || i == 50 || i == 56) {
			for (int j = 0; j < 3; j++)
			{
				codons[i].value[j] = valuEs[j];
			}
			codons[i].value[3] = '\0';
			codons[i].AminoAcid = '\0';
		}
		else {
			for (int j = 0; j < 3; j++)
			{
				codons[i].value[j] = valuEs[j];
			}
			codons[i].value[3] = '\0';
			inFile >> amino;
			codons[i].AminoAcid = amino;
		}
	//	cout << codons[i].value << ' ' << codons[i].AminoAcid << " " << i << endl;
	}
}
Codon CodonsTable::getAminoAcid(string value)
{
	bool check = 0;
	Codon reqCodon;
	reqCodon.AminoAcid = 'A';
	for (int i = 0; i<3; i++)
	{
		reqCodon.value[i] = value[i];
	}
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (codons[i].value[j] == reqCodon.value[j])
			{
				check = 1;
			}
			else
			{
				check = 0;
				break;
			}
		}
		if (check == 1)
		{
			//cout << "ade el amino acid :";
			//cout << codons[i].AminoAcid;
			reqCodon.AminoAcid = codons[i].AminoAcid;
			break;
		}
		else
		{
			continue;
		}
	}

	return reqCodon;

}

void CodonsTable::setCodon(char * value, char AminoAcid, int index)
{
	Codon reqCodon;
	for (int i = 0; i<4; i++)
	{
		reqCodon.value[i] = value[i];
	}
	reqCodon.AminoAcid = AminoAcid;

	codons[index] = reqCodon;


}






CodonsTable::~CodonsTable()
{
}

