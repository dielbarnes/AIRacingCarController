//
// Utils.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cctype>

// Safely releases a pointer
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }

class Utils
{
public:
	// Shows a dialog box
	static void ShowMessage(std::string strCustomMessage, const char* pSystemMessage = nullptr);

	// For textfield input validation
	static bool StringIsNumber(const std::string &rString);
};

#endif
