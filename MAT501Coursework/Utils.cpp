//
// Utils.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include <windows.h>
#include "Utils.h"

void Utils::ShowMessage(std::string strCustomMessage, const char* pSystemMessage)
{
	std::string text;
	text = (pSystemMessage == nullptr) ? strCustomMessage : strCustomMessage + "\n\n" + std::string(pSystemMessage);

	MessageBox(0, text.c_str(), "", 0);
}

bool Utils::StringIsNumber(const std::string &rString)
{
	std::string::const_iterator iterator = rString.begin();
	bool bDecimalPointFound = false;
	while (iterator != rString.end() && (std::isdigit(*iterator) || ('-' == *iterator && iterator == rString.begin()) || '.' == *iterator))
	{
		if ('.' == *iterator)
		{
			if (bDecimalPointFound) // String has more than one decimal point
			{
				return false;
			}
			else
			{
				bDecimalPointFound = true;
			}
		}
		++iterator;
	}
	return !rString.empty() && "." != rString && iterator == rString.end();
}
