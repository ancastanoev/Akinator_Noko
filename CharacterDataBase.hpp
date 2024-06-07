#ifndef CHARACTERDATABASE_H
#define CHARACTERDATABASE_H

#include <vector>
#include <string>
#include <memory>
#include "Character.h"

class CharacterDatabase {
private:
    std::vector<std::shared_ptr<Character>> characters;
    std::string filename;

public:
    CharacterDatabase(const std::string& filename);

    void loadCharacters();
    void saveCharacters();
    void addCharacter(const std::shared_ptr<Character>& character);
    std::vector<std::shared_ptr<Character>> getCharacters() const;
    bool hasSameResponsePattern(const std::shared_ptr<Character>& target) const;
};

#endif // CHARACTERDATABASE_H
