#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "CharacterDatabase.h"

class Game {
private:
    CharacterDatabase database;
    std::vector<std::string> questions;
    std::vector<std::string> current_responses;

public:
    Game(const std::string& filename);

    void addNewCharacter(const std::string& character_name);
    std::vector<int> getDifferentiatingQuestions(const std::vector<std::shared_ptr<Character>>& characters);
    void askQuestions();
    void play();
};

#endif // GAME_H
