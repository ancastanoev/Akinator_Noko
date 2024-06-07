#include "Character.h"
#include "Utils.h"

Character::Character(const std::string& name, const std::vector<std::string>& responses)
    : name(name), responses(responses) {}

std::ostream& operator<<(std::ostream& os, const Character& character) {
    SetColor(13); // Magenta
    os << "Character Name: " << character.name << "\nResponses: ";
    for (const auto& response : character.responses) {
        os << response << " ";
    }
    SetColor(7); // Reset to default color
    return os;
}

bool Character::operator==(const Character& other) const {
    return responses == other.responses;
}
