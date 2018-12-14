#include "stdafx.h"
#include "Sequence.h"
#include <iostream>

Sequence::Sequence()
{
	//ctor
} 
char* Align(Sequence * s1, Sequence * s2) {
	int **arr = new int *[s2->len + 1];
	for (int i = 0; i < s1->len + 1; i++)
	{
		arr[i] = new int[s2->len+1];
	}
	for (int i = 0; i < s2->len + 1; i++)
	{
		for (int j = 0; j < s1->len + 1; j++)
		{
			arr[i][j] = 0;
		}
	}
	for (int i = 1; i < s2->len + 1; i++)
	{
		for (int j = 1;j < s1->len + 1; j++)
		{
			if (s2->seq[i - 1] == s1->seq[j - 1])
			{
				arr[i][j] = arr[i - 1][j - 1] + 1;
			}
			else {
				if (arr[i - 1][j] > arr[i][j - 1])
				{
					arr[i][j] = arr[i - 1][j];
				}
				else {
					arr[i][j] = arr[i][j - 1];
				}
			}
		}
	}
		int lenofseq = arr[s2->len][s1->len];
		int k = s2->len;
		int z = s1->len;
		char *validseq = new char[lenofseq];
		validseq[lenofseq] = '\0';
			while (lenofseq >= 0 && k != 0 && z != 0)
		{
			if (arr[k][z] == arr[k - 1][z] && arr[k][z] == arr[k][z-1])
			{
				z--; 
			}
			else if (arr[k][z - 1] == arr[k - 1][z] && arr[k][z] > arr[k][z - 1])
			{
				validseq[lenofseq - 1] = s2->seq[k - 1];
				k--;
				z--; 
				lenofseq--; 
			}
			else {
				if (arr[k][z - 1] > arr[k - 1][z])
				{
					z--; 
				}
				else {
					k--;
				}
			}
		}
		return validseq;
	}
	

Sequence::Sequence(int length)
{
	this-> seq = new char[length];
	len = length;
}

void Sequence::setLen(int length)
{
	len = length;
}


void Sequence::setSeq(char * sequence)
{
	seq = new char[len];
	for (int i = 0; i<len; i++)
		seq[i] = sequence[i];
}

char* Sequence::getSeq(int F, int E)
{
	char *sec = new char[E];
	for (int i = F; i < E; i++)
	{
		sec[i] = seq[i];
	}
	return sec;
}
void Sequence::setSeq(int index, char value)
{
	seq[index] = value;
}


int Sequence::getLen()
{
	return len;
}

char Sequence::getSeq(int index)
{
	return seq[index];
}
char* Sequence::getSeq()
{
	return seq;
}
int Sequence::getLength()
{
	return len;
}


Sequence::Sequence(Sequence& rhs) {

	// copy constructor
}
Sequence::~Sequence()
{

}