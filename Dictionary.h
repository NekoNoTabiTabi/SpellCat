#pragma once
#include <unordered_set>
#include <fstream>
#include <string>
class Dictionary
{
public:
	std::unordered_set<std::string> dictionary;

	void LoadDictionary(const std::string& path);
	bool IsValidWord(const std::string& word);
};

