// Genes.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include "Sequence.h"
#include "DNA.h"
#include "RNA.h"
#include "Protein.h"
#include "CodonsTable.h"

using namespace std;
int main()
{
	DNA d1; 
	cin >> d1;
	Protein p1("KNT",Hormon ,3);
	p1.GetDNAStrandsEncodingMe(d1);
	return 0;
}

