#include "SymbolTable.h"

#include <iostream> // for debugging

SymbolTable::SymbolTable() {
	this->symbolMap;

	// Predefined symbols
	symbolMap.insert("SP", 0);
	symbolMap.insert("LCL", 1);
	symbolMap.insert("ARG", 2);
	symbolMap.insert("THIS", 3);
	symbolMap.insert("THAT", 4);
	symbolMap.insert("SCREEN", 16384);
	symbolMap.insert("KBD", 24576);

	// Virtual registers
	for (int i = 0; i < 16; i++) {
		symbolMap.insert("R" + std::to_string(i), i);
	}
}

void SymbolTable::addEntry(std::string label, int address) {
	symbolMap.insert(label, address);
}

bool SymbolTable::contains(std::string label) {
	return symbolMap.contains(label);
}

int SymbolTable::getAddress(std::string label) {
	return symbolMap.getValue(label);
}

void SymbolTable::allocateVariables() {
	int x = 16;

	for (int y = 0; y < symbolMap.size(); y++) {
		std::string key = symbolMap.getKey(y);
		if (symbolMap.getValue(key) == -1) {
			symbolMap.setValue(key, x++);
		}
	}
}
