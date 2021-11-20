#pragma once

#include <string>
#include <unordered_map>

class Code {
	static std::unordered_map<std::string, std::string> destMap;
	static std::unordered_map<std::string, std::string> compMap;
	static std::unordered_map<std::string, std::string> jumpMap;

public:
	Code();
	static std::string dest(std::string mnemonic);
	static std::string comp(std::string mnemonic);
	static std::string jump(std::string mnemonic);
};
