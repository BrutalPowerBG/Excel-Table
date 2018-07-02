#pragma once
#include <iostream>
#include <string>
#include "TextRecognition.h"

class NumberRecognition: public TextRecognition
{
	double number;
public:
	bool isCorrect()
	{
		bool isDouble = false;
		for(int i = 1; i < text.length(); i++)
		{
			if(text[i] == '.' && !isDouble)
				isDouble = true;
			else
			{
				if(text[i] == '.' && isDouble)
					return false;
				else if(text[i] <'0' || text[i] > '9')
					return false;
			}
		}
		return true;
	}
	double getValue()
	{
		return number;
	}
	NumberRecognition(std::string _text): TextRecognition(_text)
	{
		bool correct = isCorrect();
		if(correct)
			number = atof(text.c_str());
		else
			std::cout << "ERROR: Incorrect number";
	}
};