#include "stdafx.h"
#include "RNA.h"
#include <fstream>
#include <string>
#include <iostream>
#include "MyException.h"
using namespace std;

RNA::RNA() {}
RNA::RNA(char * seq1, RNA_Type atype, int Length):Sequence(Length)
{
	type = atype;
	try {
		if (len % 3 != 0) {
			WrongSize wrong;
			throw wrong;
		}
		else
		{
			for (int i = 0; i < len; i++) {
				if (seq1[i] != 'A' && seq1[i] != 'T' && seq1[i] != 'C' && seq1[i] != 'G' && seq1[i] != 'U')
				{
					InvalidInput in;
					throw in;
				}
				else {
					this->seq[i] = seq1[i];
				}
			}
		}
	}
	catch (InvalidInput in)
	{
		cout << in.what() << endl;
		exit(1);
	}
	catch (WrongSize wr)
	{
		cout << wr.what() << endl;
		exit(1);
	}
}

void RNA::setRNA_Type(RNA_Type Type)
{
	type = Type;
}


void RNA::setRNA_Type()
{
	cout << "\nChoose the type of RNA: \n"
		<< "1) mRNA \n"
		<< "2) pre_mRNA \n"
		<< "3) mRNA_exon \n"
		<< "4) mRNA_intron \n"
		<< "Your choice is: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		type = mRNA;
		break;
	case 2:
		type = pre_mRNA;
		break;
	case 3:
		type = mRNA_exon;
		break;
	case 4:
		type = mRNA_intron;
		break;
	}
}


RNA_Type RNA::getRNA_Type()
{
	return type;
}

RNA& RNA::operator=(const RNA& obj)
{
	type = obj.type;
	len = obj.len;
	setSeq(obj.seq);
	return *this;
}


bool RNA::operator== (RNA &obj)
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


bool RNA::operator!= (RNA &obj)
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


RNA RNA::operator+ (RNA &obj)
{
	RNA Res;
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
	else
	{
		cout << "Error: Can't add sequence of Conflict type !!" << endl;
		return Res;
	}
	
}
RNA::RNA(RNA &rhs)
{
	this->len = rhs.len; 
	this->seq = new char[len];
	for (int i = 0; i < len; i++) {
		this->seq[i] = rhs.seq[i];
	}
}
istream& operator>>(istream& in, RNA& obj)
{
	cout << "Enter sequence Length:";
	in >> obj.len;

	cout << " which RNA type do you want: 1- mRNA\n 2- mRNA_exon\n 3-pre_mRNA\n 4- mRNA_intron\n Your Choice is: ";
	int choice;
	a:
	in >> choice;

	switch (choice)
	{
	case 1:
		obj.type = mRNA;
		break;
	case 2:
		obj.type = mRNA_exon;
		break;
	case 3:
		obj.type = pre_mRNA;
		break;
	case 4:
		obj.type = mRNA_intron;
		break;
	default:
		cout << "Invalid type please Re-inter again ";
		goto a;

	}
	cout << "Enter your RNA sequence:";
	obj.seq = new char[obj.len];
	for (int i = 0; i < obj.len; i++)
		in >> obj.seq[i];
	
return in;

}
ostream& operator<<(ostream& out, RNA obj)
{
	for (int i = 0; i < obj.len; i++)
	{
		out << obj.seq[i] << " ";
	}
	return out; 
}

DNA RNA::ConvertToDNA()
{
	DNA dna;
	dna.setLen(len);
	dna.setDNA_Type();
	dna.setSeq(seq) ;
		for (int i = 0; i<len; i++)
		{
			switch (seq[i])
			{
			case 'U':
				dna.setSeq(i, 'A');
				break;
			case 'A':
				dna.setSeq(i, 'T');
				break;
			case 'G':
				dna.setSeq(i, 'C');
				break;
			case 'C':
				dna.setSeq(i, 'G');
				break;
			}
		}

	for (int i = 0; i<len / 2; i++)
	{
		char temp;
		temp = dna.getSeq(i);
		dna.setSeq(i, dna.getSeq(len - i - 1));
		dna.setSeq(len - i - 1, temp);
	}
	dna.BuildComplementaryStrand();
	return dna;
}

Protein& RNA::ConvertToProtein(CodonsTable table) {
	table.LoadCodonsFromFile("RNAcodontable.txt");
	Protein *p = new Protein();
	char s[4];
	for (int i = 0; i < len; i += 3) {
		s[0] = seq[i]; 
		s[1] = seq[i + 1];
		s[2] = seq[i + 2];
		s[3] = '\0';
		p->addSeq(table.getAminoAcid(s).AminoAcid);
	}
	return *p;
}
void RNA::LoadSequenceFromFile(char* filename) {
	fstream fromFile;
	fromFile.open(filename);
	char Data[100];
	int count = 0;
	while (!fromFile.eof()) {
		fromFile >> Data[count];
		count++;
	}
	cout << "RNA Sequence: ";
	for (int i = 0; i < count-1; i++) {
		cout << Data[i] << " ";
	}
	cout << endl;
}
void RNA::SaveSequenceToFile(char* filename) { 
	ofstream toFile(filename);
	for (int i = 0; i<len; i++) {
		toFile << seq[i];
	}
	toFile << endl;
	toFile << "Type :";
	switch (type) {
	case 0:
		toFile << mRNA;
		break;
	case 1:
		toFile << pre_mRNA;
		break;
	case 2:
		toFile << mRNA_exon;
		break;
	case 3:
		toFile << mRNA_intron;
		break;
	default:
		toFile << mRNA;

	}
	toFile.close(); 
}

void RNA::Print()
{
	string RNA_types[4] = { "mRNA","pre_mRNA","mRNA_exon","mRNA_intron" };
	cout << "RNA type: " << RNA_types[type - 1] << endl;
	cout << "RNA sequence: ";
	for (int i = 0; i<len; i++)
		cout << seq[i] << " ";
	cout << endl;
}
RNA::~RNA()
{
	delete [] seq;
}
