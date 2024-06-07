#include "Game.h"
#include "Utils.h"
int main() {
    printGenie();
    std::string filename = "C:\\Users\\user26.10.2020\\Desktop\\c++\\akifinal\\characters3.csv";
    Game game(filename);
    game.play();
    return 0;
}
