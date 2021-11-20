#pragma once

#include <string>

#include "SpecialMap.h"

class SymbolTable {
	SpecialMap symbolMap;

public:
	SymbolTable();
	void addEntry(std::string label, int address);
	bool contains(std::string label);
	int getAddress(std::string label);
	void allocateVariables();
};
