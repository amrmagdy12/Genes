#ifndef RNA_H
#define RNA_H

#include<cstring>
#include "Sequence.h"
#include "DNA.h"
#include "Protein.h"
#include "CodonsTable.h"

class DNA;
class CodonsTable;
enum RNA_Type { mRNA, pre_mRNA, mRNA_exon, mRNA_intron };

class RNA :public Sequence
{
private:
	RNA_Type type;
public:
	// constructors and destructor
	RNA();
	RNA(char * seq, RNA_Type ,int Length);
	RNA(RNA& rhs);
	~RNA();
	/** Setters **/
	void setRNA_Type(RNA_Type Type);
	void setRNA_Type();

	/** Getters **/
	RNA_Type getRNA_Type();

	// function to be overridden to print all the RNA information
	void Print();
	// function to convert the RNA sequence into protein sequence
	// using the codonsTable object
	friend istream& operator>>(istream& in, RNA &obj);
	friend ostream& operator<<(ostream& out, RNA obj);
	RNA& operator=(const RNA& obj);

	/** Overloading the operator == to check if 2 RNA objects are equal **/
	bool operator== (RNA &obj);

	/** Overloading the operator != to check if 2 RNA objects are not equal **/
	bool operator!= (RNA &obj);

	/** Overloading the operator + to concatenate any two sequences of the same type **/
	RNA operator+ (RNA &obj);

	/** Function to load sequence from file **/
	void LoadSequenceFromFile(char* filename);

	/** Function to save sequence to file **/
	void SaveSequenceToFile(char* filename);

	Protein& ConvertToProtein(CodonsTable table);
	// function to convert the RNA sequence back to DNA
	DNA ConvertToDNA();
};


#endif // RNA_H
