#ifndef PROTEIN_H
#define PROTEIN_H
#include "DNA.h"
#include "RNA.h"
#include "Sequence.h"
#include <iostream>
using namespace std;
class DNA;
class CodonsTable;
enum Protein_Type { Hormon, Enzyme, TF, Cellular_Function };

class Protein : public Sequence
{
private:
	Protein_Type type;
public:
	// constructors and destructor
	Protein();
	Protein(char * p, Protein_Type, int Length);
	Protein(Protein & prot);
	~Protein();
	/** Overloading the assignment operator **/
	Protein& operator=(const Protein& obj);

	/** Overloading the operator == to check if 2 Protein objects are equal **/
	bool operator== (Protein &obj);

	/** Overloading the operator != to check if 2 Protein objects are not equal **/
	bool operator!= (Protein &obj);
	bool operator==(Protein prott);
	/** Overloading the operator + to concatenate any two sequences of the same type **/
	Protein operator+ (Protein &obj);
	void addSeq(char c);
	void Print();
	
	/** Function to load sequence from file **/
	void LoadSequenceFromFile(char* filename);

	/** Function to save sequence to file **/
	void SaveSequenceToFile(char* filename);


	friend istream& operator>>(istream& in, Protein &obj);
	friend ostream& operator<<(ostream& out, Protein obj);
	// return an array of DNA sequences that can possibly
	// generate that protein sequence
	 DNA* GetDNAStrandsEncodingMe(DNA &bigDNA );
};


#endif // PROTEIN_H
