#pragma once
#include <iostream>
#include <string>
#include "TextRecognition.h"

class StringRecognition: public TextRecognition
{
public:
	bool isCorrect()
	{
		int amountOfQuotes = 1;
		bool previousSymbolIsSlash = false;
		for(int i = 1; i < text.length(); i++)
		{
			if(text[i] == '/')
				previousSymbolIsSlash = true;
			if(text[i] == '"' && !previousSymbolIsSlash)
				amountOfQuotes++;
			if(text[i] != '/')
				previousSymbolIsSlash = false;
		}
		if(text[text.length() - 1] == '"' && text[text.length() - 2] != '/'
		   && amountOfQuotes == 2)
			return true;
		else
			return false;
	}
	double getValue()
	{
		return 0;
	}
	StringRecognition(std::string _text): TextRecognition(_text)
	{
	}
};
