#include "Parser.h"

#include <fstream>
#include <regex>
#include <iostream>
#include <bitset>

Parser::Parser(std::string fileName) {
	this->commands;
	this->symbolMap;

	this->filePath = std::filesystem::path{ fileName };
	this->currentCommand = -1; // -1, so when we advance for the first time, we get command 0
}

void Parser::readFile() {
	std::regex spaces(R"(\s+)");

	std::string line;
	std::ifstream textFile(filePath);

	// Clean the lines & add them to the vector
	if (textFile.is_open()) {
		while (std::getline(textFile, line)) {
			line = std::regex_replace(line, spaces, ""); // remove whitespace

			// find and erase comments
			size_t comment = line.find("//");
			if (comment != std::string::npos) {
				line.erase(comment);
			}

			// ignore empty lines
			if (!line.empty()) {
				commands.push_back(line);
			}
		}
	}
	else {
		std::cout << "Can't open the specified file\n";
	}
}

void Parser::firstPass() {
	this->readFile();
	this->createSymbolMap();
	this->processCommands();
}

void Parser::createSymbolMap() {
	// we start at i = -1 and we increment with every A/C-command
	int i = 0;

	while (this->hasMoreCommands()) {
		std::string instruction = this->advance();
		Parser::type currentType = this->commandType();

		if (currentType == Parser::type::A_COMMAND || currentType == Parser::type::L_COMMAND) {
			// Increment only for A-commands
			if (currentType == Parser::type::A_COMMAND) {
				i++;
			}

			std::string currentSymbol = this->symbol();

			// If the symbol starts with a digit, skip
			if (std::isdigit(currentSymbol[0])) {
				continue;
			}

			// Skip if symbol in the table && it's not an L-command
			if (symbolMap.contains(currentSymbol) && currentType != Parser::type::L_COMMAND) {
				continue;
			}

			if (currentType == Parser::type::L_COMMAND) {
				symbolMap.addEntry(currentSymbol, i); // the symbol points to the next command
			}
			else {
				symbolMap.addEntry(currentSymbol, -1); // potential variable
			}
		}
		else {
			i++; // increment for C-commands
		}
	}

	// assign memory locations to variables and reset the counter
	symbolMap.allocateVariables();
	this->reset();
}

void Parser::processCommands() {
	// Store preprocessed commands here
	std::vector<std::string> cleanCommands;

	while (this->hasMoreCommands()) {
		std::string instruction = this->advance();
		Parser::type currentType = this->commandType();

		// L-commands aren't real commands
		if (currentType == Parser::type::L_COMMAND) {
			continue;
		}

		if (currentType == Parser::type::C_COMMAND) {
			// just store C-commands
			cleanCommands.push_back(instruction);
			continue;
		}

		if (currentType == Parser::type::A_COMMAND) {
			// replace the symbol with a number and store A-command
			std::string currentSymbol = this->symbol();

			if (std::isdigit(currentSymbol[0])) {
				cleanCommands.push_back("@" + currentSymbol);
			}
			else {
				cleanCommands.push_back("@" + std::to_string(symbolMap.getAddress(currentSymbol)));
			}
		}
	}

	// Replace commands and reset the counter
	commands = cleanCommands;
	this->reset();
}

bool Parser::hasMoreCommands() {
	return (currentCommand + 1) < (int)commands.size();
}

std::string Parser::advance() {
	return commands.at(++currentCommand);
}

void Parser::reset() {
	currentCommand = -1;
}

Parser::type Parser::commandType() {
	// To determine what command we're dealing with,
	// we just need to check the first character
	switch (commands.at(currentCommand).at(0)) {
	case '(':
		return Parser::type::L_COMMAND;
	case '@':
		return Parser::type::A_COMMAND;
	default:
		return Parser::type::C_COMMAND;
	}
}

std::string Parser::symbol() {
	std::string command = commands.at(currentCommand);

	if (this->commandType() == Parser::type::A_COMMAND) {
		// A-command: @symbol
		return command.substr(1);
	}
	else {
		// L-command: (symbol)
		return command.substr(1, command.size() - 2);
	}
}

std::string Parser::binaryNumber() {
	// convert the number to binary
	int number = std::stoi(this->symbol());
	return std::bitset<15>(number).to_string();
}

std::string Parser::dest() {
	// dest = comp ; jump
	std::string current = commands.at(currentCommand);
	size_t index = current.find("=");

	if (index == std::string::npos) {
		return "null";
	}

	return current.substr(0, index);
}

std::string Parser::comp() {
	// dest = comp ; jump
	std::string current = commands.at(currentCommand);
	size_t index1 = current.find("=");
	size_t index2 = current.find(";");

	if (index1 == std::string::npos) {
		index1 = -1;
	}

	if (index2 == std::string::npos) {
		index2 = current.size();
	}

	return current.substr(index1 + 1, index2);
}

std::string Parser::jump() {
	// dest = comp ; jump
	std::string current = commands.at(currentCommand);
	size_t index = current.find(";");

	if (index == std::string::npos) {
		return "null";
	}

	return current.substr(index + 1, current.size());
}
