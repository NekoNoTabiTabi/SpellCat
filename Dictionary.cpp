#include "Dictionary.h"

void Dictionary::LoadDictionary(const std::string& path)
{
    std::ifstream file(path);
    std::string word;
    while (file >> word) {
        // Normalize to uppercase
        for (auto& c : word) c = toupper(c);
        dictionary.insert(word);
    }

}

bool Dictionary::IsValidWord(const std::string& word)
{
    return dictionary.find(word) != dictionary.end();
}
