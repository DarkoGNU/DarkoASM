#include "SpecialMap.h"

void SpecialMap::insert(std::string key, int value) {
	if (dataMap.contains(key)) {
		dataMap[key] = value;
	}
	else {
		orderMap[counter++] = key;
		dataMap[key] = value;
	}
}

std::string SpecialMap::getKey(int order) {
	return orderMap[order];
}

int SpecialMap::getValue(std::string key) {
	return dataMap[key];
}

bool SpecialMap::contains(std::string key) {
	return dataMap.contains(key);
}

int SpecialMap::size() {
	return orderMap.size();
}

void SpecialMap::setValue(std::string key, int value) {
	dataMap[key] = value;
}
