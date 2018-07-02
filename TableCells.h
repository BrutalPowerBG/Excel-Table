#pragma once
#include <vector>
#include <string>
#include "TextRecognition.h"
#include "NumberRecognition.h"
#include "StringRecognition.h"
#include "FormulaRecognition.h"
class Table;

class Cell
{
	TextRecognition* textRecognition;
	std::string cellString;
	char cellType;
	Table* belongsTo;
	void identifyCellType()
	{
		char type;
		//Remove all spaces before and after cell string
		for(int i = 0 ; i<cellString.length(); i--)
		{
			if(cellString[i] == ' ')
				cellString.erase(i, 1);
			else
				break;
		}
		for(int i = cellString.length() - 1; i > 0; i--)
		{
			if(cellString[i] == ' ')
				cellString.erase(i, 1);
			else
				break;
		}
		char startingCharacter = cellString[0];
		if(startingCharacter >= '0' && startingCharacter <= '9')
		{
			startingCharacter = '0';
		}
		switch(startingCharacter)
		{
			case '0': case '+': case '-':
				cellType = 'N'; //for Number
				break;
			case '=':
				cellType = 'F'; //for Formula
				break;
			case '"':
				cellType = 'S'; //for String
				break;
			default:
				cellType = 'E'; //for Error
		}

		switch(cellType)
		{
			case 'N':
				textRecognition = new NumberRecognition(cellString);
				break;
			case 'F':
				textRecognition = new FormulaRecognition(cellString, belongsTo);
				break;
			case 'S':
				textRecognition = new StringRecognition(cellString);
				break;
		}
		if(!textRecognition->isCorrect())
				cellType = 'E';

	}
public:
	void setCell(std::string _string)
	{
		cellString = _string;
		delete textRecognition;
		identifyCellType();
	}
	Cell(std::string _string, Table* _belongsTo): belongsTo(_belongsTo)
	{
		setCell(_string);
	}
	~Cell()
	{
		delete textRecognition;
		delete belongsTo;
	}
};

class Table
{
	std::vector<std::vector<Cell>> cells;
public:
	//TODO
};