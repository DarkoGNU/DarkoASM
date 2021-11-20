#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[]) {
	std::string asmFile(argv[1]);
	std::cout << "Compiling " + asmFile + "...\n";

	Parser parser(asmFile);
	parser.firstPass();

	// Get the path for .hack file
	size_t index = asmFile.find_last_of('.');
	std::string outFile = asmFile.substr(0, index) + ".hack";
	std::filesystem::path outPath = std::filesystem::path{ outFile };

	// Open the .hack file for writing
	std::ofstream textFile(outPath);

	if (!textFile.is_open()) {
		std::cout << "Can't write to the output file\n";
		return -1;
	}

	while (parser.hasMoreCommands()) {
		parser.advance();

		std::string command = "";

		if (parser.commandType() == Parser::type::A_COMMAND) {
			command.append("0"); // op-code for A-commands
			std::string argument = parser.binaryNumber(); // A-command's argument
			command.append(argument);
		}
		else {
			command.append("111"); // op-code for C-commands

			std::string comp = parser.comp();
			std::string dest = parser.dest();
			std::string jump = parser.jump();

			command.append(Code::comp(comp));
			command.append(Code::dest(dest));
			command.append(Code::jump(jump));
		}

		// Write the assembled binary code
		textFile << command << "\n";
	}

	std::cout << "Compilation completed";
}
