#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
using namespace std;

class Sequence
{
protected:
	char * seq;
	int len;
public:
	// constructors and destructor
	Sequence();
	Sequence(int length);
	Sequence(Sequence& rhs);
	virtual ~Sequence();
	// pure virtual function that should be overridden because every
	// type of sequence has its own details to be printed
	
	/** Setters **/
	void setLen(int length);
	void setSeq(char * sequence);
	void setSeq(int index, char value);

	/** Getters **/
	int getLen();
	char getSeq(int index);
	char* getSeq(int F, int E);
	char* getSeq();
	int getLength();

	// Pure Virtual functions 
	virtual void Print() = 0;
	// friend function that will find the LCS (longest common
	// subsequence) between 2 sequences of any type, according to
	// polymorphism
	/** Function to load sequence from file **/
	virtual void LoadSequenceFromFile(char* filename) = 0  ;

	/** Function to save sequence to file **/
	virtual void SaveSequenceToFile(char* filename) = 0 ;

	friend char* Align(Sequence * s1, Sequence * s2);

};

#endif // SEQUENCE_H

