#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "SymbolTable.h"

class Parser {
	std::filesystem::path filePath;
	std::vector<std::string> commands;
	SymbolTable symbolMap;
	int currentCommand;

public:
	// Instruction types
	enum class type { A_COMMAND, C_COMMAND, L_COMMAND };

	// Constructor
	Parser(std::string fileName);

	// Handling commands
	bool hasMoreCommands();
	Parser::type commandType();
	std::string advance();

	// Get A or L-instruction's argument
	std::string symbol();
	// get the address in binary form
	std::string binaryNumber();

	// Get different parts of a C-instruction
	std::string dest();
	std::string comp();
	std::string jump();

	// Preprocess the assembly code
	void firstPass();

private:
	void readFile();
	void reset();

	void createSymbolMap();
	void processCommands();
};
