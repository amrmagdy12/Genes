#include "stdafx.h"
#include "DNA.h"
#define EOF (-1)
#include <fstream>
#include <iostream>
#include "MyException.h"
using namespace std;

DNA::DNA() {}

DNA::DNA(DNA& rhs) {
	len = rhs.len;
	seq = new char[len]; 
	for (int i = 0; i < len; i++) { this->seq[i] = rhs.seq[i]; }
}
DNA::DNA(char * seq, DNA_Type atype, int Length) :Sequence(Length)
{
	type = atype;
	try {
		if (len % 3 != 0){
			WrongSize wrong;
			throw wrong;
		}
		else
		{
				for (int i = 0; i < len; i++) {
					if (seq[i] != 'A' && seq[i] != 'T' && seq[i] != 'C' && seq[i] != 'G')
					{
						InvalidInput in;
						throw in;
					}
					else {
						this->seq[i] = seq[i];
					}
				}
				BuildComplementaryStrand();
			}
}
catch (InvalidInput in)
{
	cout << in.what() << endl;
	exit(1);
}
catch (WrongSize wr)
{
	cout << wr.what() << endl ;
	exit(1);
}
	
}
// Setters
void DNA::setDNA_Type()
{
	cout << "\nChoose the type of DNA: \n"
		<< "1) promoter \n"
		<< "2) motif \n"
		<< "3) tail \n"
		<< "4) noncoding \n"
		<< "Your choice is: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		type = promoter;
		break;
	case 2:
		type = motif;
		break;
	case 3:
		type = tail;
		break;
	case 4:
		type = noncoding;
		break;
	}
}
void DNA::setLen(int ident)
{
	len = ident;
}

void DNA::setDNA_Type(DNA_Type Type)
{
	type = Type;
}

// Getters
DNA_Type DNA::getDNA_Type()
{
	return type;
}

DNA& DNA::operator=(const DNA& obj)
{
	type = obj.type;
	len = obj.len;
	setSeq(obj.seq);
	BuildComplementaryStrand();
	return *this;
}

bool DNA::operator== (DNA &obj)
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


bool DNA::operator!= (DNA &obj)
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


DNA DNA::operator+ (DNA &obj)
{
	DNA Res;
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
		Res.BuildComplementaryStrand();
		return Res;
	}
	else
	{
		cout << "Error: Can't add sequence of Conflict type !!" << endl;

	}
			
}

istream& operator>>(istream& in, DNA & obj)
{
	cout << "Enter sequence Length:";
	in >> obj.len;
	cout << " which DNA type do you want: 1- promoter\n 2- motif\n 3- tail\n 4- non-coding\n Your Choice is: ";
	int choice; 
	a:
	in >> choice;
	
	switch(choice)
	{
	case 1:
		obj.type = promoter;
		break;
	case 2:
		obj.type = motif;
		break; 
	case 3:
		obj.type = tail;
		break;
	case 4:
		obj.type = noncoding;
		break;
	default:
		cout << "Invalid type please Re-inter again ";
		goto a;

	}
	cout << "Enter your DNA sequence:";
	obj.seq = new char[obj.len];
	bool ntaTmm = false;
	try{
		for (int i = 0; i < obj.len; i++)
		{
			in >> obj.seq[i];
			if (obj.seq[i] == 'A' || obj.seq[i] == 'T' || obj.seq[i] == 'C' || obj.seq[i] == 'G')
				ntaTmm = true; 
			else
				throw "Invalid Input character ";
		}
	}
	catch (char * mes)
	{
		cout << mes;
	}	
	obj.BuildComplementaryStrand();
	
	return in;


}
ostream& operator<<(ostream& out, DNA obj)
{
	for (int i = 0; i < obj.len; i++)
	{
		out << obj.seq[i] << " ";
	}
	cout << endl;

	return out;
}

void DNA::BuildComplementaryStrand() {
	complementary_strand = new DNA;
	complementary_strand->seq = new char[len];
	for (int i = 0; i < len; i++) {
		switch (seq[i]) {
		case 'T':
			complementary_strand->seq[i] = 'A';
			break;
		case 'A':
			complementary_strand->seq[i] = 'T';
			break;
		case 'G':
			complementary_strand->seq[i] = 'C';
			break;
		case 'C':
			complementary_strand->seq[i] = 'G';
			break;
		}
	}
	for (int i = 0; i < len / 2; i++) {
		swap(complementary_strand->seq[i], complementary_strand->seq[len - 1 - i]);
	}

}

RNA DNA::ConvertToRNA(int Start , int End)
{
	char *seq2;
	int length = End - Start + 1;
	if (Start == -1 && End == -1)
	{
		Start = 0;
		End = len;
		length = len;
	}
	seq2 = new char[length];
	for (int i = 0; i<length; i++)
	{
		if (seq[Start] == 'T')
			seq2[i] = 'U';
		else
			seq2[i] = seq[Start];
		Start++;
	}
	RNA rna(seq2, mRNA, length);
	return rna;
}
void DNA::Print() {
	cout << "ComplementaryStrand:";
	for (int i = 0; i < len; i++) {
		cout << complementary_strand->seq[i] << " ";
	}
	cout << endl;

}
void DNA::LoadSequenceFromFile(char* filename) {
	fstream fromFile;
	fromFile.open(filename); 
	char Data[100];
	int count = 0; 
	while (!fromFile.eof()) {
		fromFile >> Data[count];
		count++;
	}
	cout << "DNA Sequence: ";
	for (int i = 0; i < count-1 ; i++) {
		cout << Data[i] << " ";
	}
	cout << endl;
}
void DNA::SaveSequenceToFile(char* filename) {
	ofstream toFile;
	toFile.open(filename);
	if (!toFile) {
		cout << "Unable to open file datafile.txt";
	}
	for (int i = 0; i < len; i++) {
		toFile << seq[i];
	}
	toFile << endl;
	toFile << "Complementary strand : ";
	for (int i = 0; i < len; i++) {
		toFile<< complementary_strand->seq[i];
	}
	toFile << endl;
	toFile << "Type : ";
	switch(type){
	case 0:
		toFile << promoter ;
		break;
	case 1:
		toFile << motif;
		break;
	case 2:
		toFile << tail;
		break;
	case 3:
		toFile << noncoding;
		break;
	default:
		toFile << promoter;
		
	}
  
	toFile.close();
}

DNA::~DNA()
{

}
