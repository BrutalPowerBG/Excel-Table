#pragma once
#include "TextRecognition.h"
#include "FormulaElement.h"

class Formula
{
	std::vector<FormulaElement*> elements;
public:
	void addElement(FormulaElement* newElement)
	{
		elements.push_back(newElement);
	}
	unsigned int size()
	{
		return elements.size();
	}
	FormulaElement* getElement(unsigned int index)
	{
		return elements[index];
	}
	~Formula()
	{
		while(!elements.empty())
		{
			delete elements.back();
			elements.pop_back();
		}
	}

};


