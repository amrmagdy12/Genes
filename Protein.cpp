#include "stdafx.h"
#include "Protein.h"
#include "MyException.h"
#include <string>
#include <fstream>
#include "CodonsTable.h"
#include <iostream>
#include "MyException.h"

using namespace std;
Protein::Protein(){
	len = 0;
	seq = "";
}
Protein::Protein(char * p,Protein_Type atype, int Length) :Sequence(Length)
{
	type = atype;
	for (int i = 0; i < Length; i++)
	{
		seq[i] = p[i];
	}
}
DNA* Protein::GetDNAStrandsEncodingMe(DNA &bigDNA)
{
	CodonsTable c;
	int z = 0, x = 0, c1 = 0, ch = 0;

	char* seq1 = new char[bigDNA.getLen()];
	char* seq2 = new char[bigDNA.getLen()];
	char found[4];
	found[3] = '\0';
	seq1 = bigDNA.getSeq();
	c.LoadCodonsFromFile("RNAcodontable.txt");

	for (int i = 0; i < bigDNA.getLen(); i++)
	{
		if (seq1[i] == 'T')
		{
			seq1[i] = 'U';
		}
	}


	for (int i = 0; i < bigDNA.getLen(); i++)
	{
		found[0] = seq1[i];
		found[1] = seq1[i + 1];
		found[2] = seq1[i + 2];

		//DNA* newd = new DNA(seq2, bigDNA.getType(), bigDNA.getSize());
		if (seq[c1] == (c.getAminoAcid(found).AminoAcid))
		{
			for (int j = 0; j < 3; j++)
			{
				seq2[z] = found[j];
				z++;
				ch++;

			}
			c1++;
			i += 2;   // 34an ykml mn awl el talata eli b3dhom

			if (c1 == len) {
				c1 = 0;
				ch = 0;
			}
		}
		else
		{
			c1 = 0;

			z -= ch;

			ch = 0;

		}
	}
	seq2[z] = '\0';
	int y = 0;
	//int b = 0;
	for (int i = 0; i < z; i++)
	{
		if (seq2[i] == 'U')
		{
			seq2[i] = 'T';
		}
	}
	while (y < z) {
		for (int i = 0; i < len * 3; i++) {
			cout << seq2[y] << seq2[y + 1] << seq2[y + 2];
			i += 2;
			y += 3;

		}
		//b++;
		cout << endl;

	}
}
bool Protein::operator==(Protein prott)
{
	bool isEqual = true;
	if (len == prott.getLength())
	{
		for (int i = 0; i < len; i++)
		{
			if (seq[i] != prott.seq[i])
			{
				isEqual = false;
				break;
			}
					
		}
		return isEqual;
	}
	else {
		return isEqual;
	} 
	
}
void Protein::addSeq(char c)
{	
	this->len++;
	char* seq2 = new char[len];
	for (int i = 0; i < len - 1; i++) {
		seq2[i] = seq[i];
	}
	seq2[len-1] = c;
	this->seq = seq2;
}
Protein::Protein(Protein & prot)
{
	type = prot.type;
	len = prot.len;
	seq = new char[len];
	for (int i = 0; i < len; i++)
	{
		seq[i] = prot.seq[i];
	}
}
Protein& Protein::operator=(const Protein& obj)
{
	type = obj.type;
	len = obj.len;
	setSeq(obj.seq);
	return *this;
}

bool Protein::operator== (Protein &obj)
{
	int counter = 0;
	if ((type != obj.type) || (len != obj.len))
		return false;
	else
	{
		for (int i = 0; i<len; i++)
			if (seq[i] == obj.seq[i])
				counter++;
		if (counter == len)
			return true;
		else
			return false;

	}
}


bool Protein::operator!= (Protein &obj)
{
	int counter = 0;
	if ((type != obj.type) || (len != obj.len))
		return true;
	else
	{
		for (int i = 0; i<len; i++)
			if (seq[i] == obj.seq[i])
				counter++;
		if (counter == len)
			return false;
		else
			return true;

	}
}


Protein Protein::operator+ (Protein &obj)
{
	Protein Res;
	if (type == obj.type)
	{
		Res.type = type;
		Res.len = len + obj.len;
		Res.seq = new char[Res.len];
		int index = 0;
		for (int i = 0; i<len; i++)
		{
			Res.seq[index] = seq[i];
			index++;
		}
		for (int i = 0; i<obj.len; i++)
		{
			Res.seq[index] = obj.seq[i];
			index++;
		}
		return Res;
	}
	else {
		cout << "Error: Can't add Sequence of ConflictType!!" << endl;
		return Res;
	}
}
istream& operator>>(istream& in, Protein &obj)
{
	cout << "Enter the length of the Protein sequence: ";
	in >> obj.len;
	obj.seq = new char[obj.len];
	for (int i = 0; i<obj.len; i++)
		in >> obj.seq[i];
	return in;
}


ostream& operator<<(ostream& out, Protein obj)
{
	out << "Protein sequence: ";
	for (int i = 0; i<obj.len; i++)
		out << obj.seq[i] << " ";
	out << endl;
	return out;
}


void Protein::Print() {
	string Protein_types[4] = { "Hormon","Enzyme","TF","Cellular_Function" };
	cout << "Protein type: " << Protein_types[type - 1] << endl;
	cout << "Protein sequence: ";
	for (int i = 0; i<len; i++)
		cout << seq[i] << " ";
	cout << endl;
}
void Protein::LoadSequenceFromFile(char* filename) {
	fstream fromFile;
	fromFile.open(filename);
	char Data[100];
	int count = 0;
	while (!fromFile.eof()) {
		fromFile >> Data[count];
		count++;
	}
	cout << "Protein Sequence: ";
	for (int i = 0; i < count; i++) {
		cout << Data[i] << " ";
	}
	cout << endl;
}
void Protein::SaveSequenceToFile(char* filename) {
	ofstream toFile(filename);
	for (int i = 0; i<len; i++) {
		toFile << seq[i];
	}
	toFile << endl;
	toFile << "Type : ";
	switch (type) {
	case 0:
		toFile << Hormon;
		break;
	case 1:
		toFile << Enzyme;
		break;
	case 2:
		toFile << TF;
		break;
	case 3:
		toFile << Cellular_Function ;
		break;
	default:
		toFile << Hormon;

	}
	toFile.close();
}



Protein::~Protein()
{
}
