#pragma once
#include <iostream>
#include <cassert>
#include "TextRecognition.h"

class FormulaElement
{
protected:
	char type;
public:
	char getType()
	{
		return type;
	}
};

class CellLink: public FormulaElement
{
	unsigned int R, C;
public:
	int getRow()
	{
		return R;
	}
	int getColumn()
	{
		return C;
	}
	CellLink(unsigned int _R, unsigned int _C): R(_R), C(_C)
	{
		type = 'L';
	}
};
class Number: public FormulaElement
{
	double number;
public:
	double getNumber()
	{
		return number;
	}
	Number(double _number): number(_number)
	{
		type = 'N';
	};
};
class ArithmeticSign: public FormulaElement
{
	char sign;
	int signPriority;
	std::vector<char> availableSigns;
public:
	char getSign()
	{
		return sign;
	}
	ArithmeticSign(char _sign)
	{
		type = 'S';
		//The code below checks if the sign is one of the expected and assigns priority:
		availableSigns.push_back('+');
		availableSigns.push_back('*');
		availableSigns.push_back('-');
		availableSigns.push_back('/');
		bool isLegit = false;
		for(int i = 0; i<availableSigns.size(); i++)
		{
			if(_sign == availableSigns[i])
			{
				isLegit = true;
				signPriority = i % 2;
			}
		}
		assert(isLegit); // before public release
		if(!isLegit) //should never be possible, but just in case
			std::cout << "Error: Invalid arithmetic sign"; //after public release
		sign = _sign;
	}
};