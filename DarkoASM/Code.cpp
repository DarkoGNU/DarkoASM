#include "Code.h"

std::string Code::dest(std::string mnemonic) {
	return destMap[mnemonic];
}

std::string Code::comp(std::string mnemonic) {
	char M = '0';
	size_t index = mnemonic.find("M");

	// if there's an M, replace it with A and set the M bit
	if (index != std::string::npos) {
		M = '1';
		mnemonic[index] = 'A';
	}

	return M + compMap[mnemonic];
}

std::string Code::jump(std::string mnemonic) {
	return jumpMap[mnemonic];
}

std::unordered_map<std::string, std::string> Code::destMap = {
	{ "null", "000" },
	{ "M", "001" },
	{ "D", "010" },
	{ "MD", "011" },
	{ "A", "100" },
	{ "AM", "101" },
	{ "AD", "110" },
	{ "AMD", "111" }
};

std::unordered_map<std::string, std::string> Code::compMap = {
	{"0", "101010"},
	{"1", "111111"},
	{"-1", "111010"},
	{"D", "001100"},
	{"A", "110000"},
	{"!D", "001101"},
	{"!A", "110001"},
	{"-D", "001111"},
	{"-A", "110011"},
	{"D+1", "011111"},
	{"A+1", "110111"},
	{"D-1", "001110"},
	{"A-1", "110010"},
	{"D+A", "000010"},
	{"D-A", "010011"},
	{"A-D", "000111"},
	{"D&A", "000000"},
	{"D|A", "010101"}
};

std::unordered_map<std::string, std::string> Code::jumpMap = {
	{"null", "000"},
	{"JGT", "001"},
	{"JEQ", "010"},
	{"JGE", "011"},
	{"JLT", "100"},
	{"JNE", "101"},
	{"JLE", "110"},
	{"JMP", "111"},
};
