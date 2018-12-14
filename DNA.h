#ifndef DNA_H
#define DNA_H
#include "Sequence.h"
#include "RNA.h"
#include <iostream>

using namespace std;

class RNA;

enum DNA_Type { promoter, motif, tail, noncoding };

class DNA : public Sequence
{
private:
	DNA_Type type;
	DNA*  complementary_strand;
	int startIndex;
	int endIndex;
public:
	// constructors and destructor
	DNA();
	DNA(char * seq ,DNA_Type, int length);
	// Copy Constructor
	DNA(DNA& rhs);
	// Destructor
	~DNA();
	/** setters **/
	void setDNA_Type(DNA_Type Type);
	void setDNA_Type();
	void setLen(int ident);
	DNA_Type getDNA_Type();
	void Print();
	RNA ConvertToRNA(int Start, int End);
	void BuildComplementaryStrand();
	DNA& operator=(const DNA& obj);

	bool operator== (DNA &obj);

	/** Overloading the operator != to check if 2 DNA objects are not equal **/
	bool operator!= (DNA &obj);

	/** Overloading the operator + to concatenate any two sequences of the same type **/
	DNA operator+ (DNA &obj);

	/** Function to load sequence from file **/
	void LoadSequenceFromFile(char* filename);

	/** Function to save sequence to file **/
	void SaveSequenceToFile(char* filename);

	
	// Friend Functions //
	friend istream& operator>>(istream& in, DNA &obj);
	friend ostream& operator<<(ostream& out, DNA obj);
};


#endif // DNA_H
