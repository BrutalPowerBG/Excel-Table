#pragma once
#include <iostream>
#include "TextRecognition.h"
#include "Formula.h"
#include "FormulaElement.h"

class FormulaRecognition: public TextRecognition
{
	Formula formula;
	int amountOfPhases;
	bool correct;
	Table* table;
public:
	bool isCorrect()
	{
		return correct;
	}
	void defineFormula()
	{
		int currentPhase = 0;
		int cellLinkPhase = 0;
		std::string tmpCellRow = "";
		unsigned int tmpCellRowInt;
		std::string tmpCellColumn = "";
		unsigned int tmpCellColumnInt;
		std::string tmpNumberToBeConverted = "";
		for(int i = 1; i < text.length(); i++)
		{
			if(text[i] == 'R' || text[i] == 'C' || text[i] == ' ' ||
			   text[i] == '.' || (text[i] >= '0' && text[i] <= '9') ||
			   text[i] == '+' || text[i] == '-' ||
			   text[i] == '*' || text[i] == '/')
			{
				if(text[i] == ' ')
					continue;
				if(currentPhase == 0)
				{
					if((text[i] == 'R' || (text[i] >= '0' && text[i] <= '9')))
					{
						currentPhase = 1;
						if(text[i] == 'R')
							cellLinkPhase = 1;
						else if(text[i] >= '0' && text[i] <= '9')
							tmpNumberToBeConverted.push_back(text[i]);
					}
					else
						correct = false;
				}
				if(currentPhase == 1 && cellLinkPhase == 0)
				{
					if((text[i] >= '0' && text[i] <= '9') || text[i] == '.')
					{
						tmpNumberToBeConverted.push_back(text[i]);
					}
					else
					{
						if(tmpNumberToBeConverted != "")
						{
							formula.addElement(new Number(atof(tmpNumberToBeConverted.c_str())));
							tmpNumberToBeConverted = "";
						}
						if(text[i] == '+' || text[i] == '-' ||
						   text[i] == '*' || text[i] == '/')
						{
							formula.addElement(new ArithmeticSign(text[i]));
							currentPhase = 0;
						}
					}
				}
				if(cellLinkPhase == 1)
				{
					if(text[i] >= '0' && text[i] <= '9')
					{
						tmpCellRow.push_back(text[i]);
					}
					if(text[i] == 'C')
					{
						tmpCellRowInt = atoi(tmpCellRow.c_str());
						tmpCellRow = "";
						cellLinkPhase = 2;
					}
				}
				else if(cellLinkPhase == 2)
				{
					if(text[i] >= '0' && text[i] <= '9')
					{
						tmpCellColumn.push_back(text[i]);
					}
					else
					{
						tmpCellColumnInt = atoi(tmpCellColumn.c_str());
						tmpCellColumn = "";
						formula.addElement(new CellLink(tmpCellRowInt, tmpCellColumnInt));
						if(text[i] == '+' || text[i] == '-' ||
						   text[i] == '*' || text[i] == '/')
						{
							formula.addElement(new ArithmeticSign(text[i]));
							currentPhase = 0;
						}
						cellLinkPhase = 0;
					}
				}
			}
			else
			{
				correct = false;
			}
		}
	}
	bool evaluateCorrectness() //of Formula sequence
	{
		bool numberOrLink = false;
		for(int i = 0; i < formula.size(); i++)
		{
			if(formula.getElement(i)->getType() == 'N' || formula.getElement(i)->getType() == 'L')
			{
				if(numberOrLink)
					return false;
				numberOrLink = true;
			}
			if(formula.getElement(i)->getType() == 'S')
			{
				if(!numberOrLink)
					return false;
				numberOrLink = false;
			}
		}
		if(!numberOrLink)
			return false;
		return true;
	}
	double getValue() //evaluates Formula
	{
		if(!correct)
			return 0;
		//TODO
	}
	FormulaRecognition(std::string _text, Table* _table): TextRecognition(_text), table(_table)
	{
		amountOfPhases = 2;
		correct = true;
		defineFormula();
		if(!evaluateCorrectness())
			correct = false;
	}
};