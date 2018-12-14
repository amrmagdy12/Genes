#pragma once
#include <iostream>
#include <exception>
using namespace std;
class InvalidInput:public exception
{
public:
	virtual const char* what() const throw ()
	{
		return "Error: Invalid Input sequence ";
	}
};
class WrongSize:public exception
{
public:
	virtual const char* what() const throw ()
	{
		return "Error: size of Sequences must be multiple of 3";
	}
};
