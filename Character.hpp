#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include <string>

class Character {
public:
    std::string name;
    std::vector<std::string> responses;

    Character(const std::string& name, const std::vector<std::string>& responses);

    friend std::ostream& operator<<(std::ostream& os, const Character& character);
    bool operator==(const Character& other) const;
};

#endif 
