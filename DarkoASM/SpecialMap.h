#pragma once

#include <unordered_map>
#include <string>

class SpecialMap {
	int counter = 0;
	std::unordered_map<int, std::string> orderMap;
	std::unordered_map<std::string, int> dataMap;

public:
	void insert(std::string key, int value);
	std::string getKey(int order);
	int getValue(std::string key);
	bool contains(std::string key);
	int size();
	void setValue(std::string key, int value);
};
