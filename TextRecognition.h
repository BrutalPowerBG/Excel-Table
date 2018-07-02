#pragma once
#include<string>
#include <vector>
#include <string>
#include "TableCells.h"
#include "FormulaElement.h"

class TextRecognition
{
protected:
	std::string text;
public:
	virtual bool isCorrect()=0;
	virtual double getValue() = 0;
	TextRecognition(std::string _text):text(_text){ }
};


