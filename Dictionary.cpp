#include "Dictionary.h"
#include <iostream>
void Dictionary::LoadDictionary(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open dictionary file at '" << path << "'." << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        // Normalize to uppercase
        for (auto& c : word) c = toupper(c);
        dictionary.insert(word);
    }

    std::cout << "Dictionary loaded successfully from '" << path << "'. Total words: " << dictionary.size() << std::endl;
}

bool Dictionary::IsValidWord(const std::string& word)
{
    return dictionary.find(word) != dictionary.end();
}
