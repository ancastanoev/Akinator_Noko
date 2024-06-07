#include "Game.h"
#include "Utils.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>
#include <sstream>

Game::Game(const std::string& filename) : database(filename) {
    questions = {
        "Is your character real?", "Is your character male?", "Is your character an actor?", "Is your character a singer?",
        "Is your character from a TV show?", "Is your character animated?", "Is your character from a video game?",
        "Does your character have superpowers?", "Is your character from a book?", "Is your character a politician?",
        "Is your character dead?", "Is your character from a comic book?", "Is your character over 50 years old?",
        "Does your character have children?", "Is your character married?",  "Is your character a historical figure?", "is your character a scientist?", "Is your character a sports figure?"
    };
    current_responses.resize(questions.size(), "I don't know");
}

void Game::addNewCharacter(const std::string& character_name) {
    auto new_character = std::make_shared<Character>(character_name, current_responses);
    database.addCharacter(new_character);
    SetColor(10); // Green
    std::cout << "Character added successfully." << std::endl;
    SetColor(7); // Reset to default color
}

std::vector<int> Game::getDifferentiatingQuestions(const std::vector<std::shared_ptr<Character>>& characters) {
    std::vector<int> differentiating_questions;
    if (characters.size() < 2) return differentiating_questions;

    for (size_t i = 0; i < questions.size(); ++i) {
        bool different = false;
        std::string first_response = characters[0]->responses[i];
        for (size_t j = 1; j < characters.size(); ++j) {
            if (characters[j]->responses[i] != first_response) {
                different = true;
                break;
            }
        }
        if (different) {
            differentiating_questions.push_back(i);
        }
    }
    return differentiating_questions;
}

void Game::askQuestions() {
    auto possible_characters = database.getCharacters();
    std::string answer;

    // Initialize question indices
    std::vector<int> question_indices(questions.size());
    std::iota(question_indices.begin(), question_indices.end(), 0);

    // Static variable to keep track of the last used first question
    static int last_first_question_idx = -1;

    // Select a different first question index
    int first_question_idx;
    do {
        first_question_idx = std::rand() % questions.size();
    } while (first_question_idx == last_first_question_idx);

    last_first_question_idx = first_question_idx;

    // Create a vector of the remaining questions
    std::vector<int> remaining_indices;
    for (size_t i = 0; i < question_indices.size(); ++i) {
        if (i != first_question_idx) {
            remaining_indices.push_back(question_indices[i]);
        }
    }

    // Shuffle the remaining questions
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(remaining_indices.begin(), remaining_indices.end(), g);

    // Combine the first question with the shuffled remaining questions
    std::vector<int> shuffled_indices = {first_question_idx};
    shuffled_indices.insert(shuffled_indices.end(), remaining_indices.begin(), remaining_indices.end());

    std::vector<bool> asked_questions(questions.size(), false);

    for (size_t idx : shuffled_indices) {
        // Skip questions that have been answered with "dn"
        if (asked_questions[idx]) continue;

        do {
            SetColor(14); // Yellow
            std::cout << questions[idx] << " (yes/no/dk): ";
            std::cin >> answer;
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower); // Convert to lowercase for consistency

            if (answer != "yes" && answer != "no" && answer != "dk") {
                SetColor(12); // Red
                std::cout << "Invalid input. Please enter 'yes', 'no', or 'dk'." << std::endl;
            }
        } while (answer != "yes" && answer != "no" && answer != "dk");

        // Mark the question as asked if not "dn"
        if (answer == "dk") {
            asked_questions[idx] = true;
            continue;
        } else {
            asked_questions[idx] = true;
        }

        // Save the response
        current_responses[idx] = (answer == "yes" ? "Yes" : "No");

        // Filter characters based on user response
        std::vector<std::shared_ptr<Character>> filtered_characters;
        for (const auto& character : possible_characters) {
            if ((answer == "yes" && character->responses[idx] == "Yes") ||
                (answer == "no" && character->responses[idx] == "No") ||
                (character->responses[idx] == "I don't know")) {
                filtered_characters.push_back(character);
            }
        }
        possible_characters = filtered_characters;



        // Stop searching if only one character matches
        if (possible_characters.size() == 1) {
            SetColor(14); // Yellow
            std::cout << "Is it " << possible_characters[0]->name << "? (yes/no): ";
            std::cin >> answer;
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            if (answer == "yes") {
                SetColor(10); // Green
                std::cout << "GREAT! I GUESSED IT RIGHT!" << std::endl;
            } else {
                // Ask for the correct character and add a new question if necessary
                std::string character_name;
                SetColor(11); // Cyan
                std::cout << "Who is the character you were thinking of? ";
                std::cin.ignore();
                getline(std::cin, character_name);
                addNewCharacter(character_name);
            }
            SetColor(7); // Reset to default color
            return; // Stop searching
        }

        // Stop searching if no characters match
        if (possible_characters.empty()) {
            SetColor(12); // Red
            std::cout << "No matching character found." << std::endl;

            // Ask if the user wants to add a new character
            SetColor(11); // Cyan
            std::cout << "Would you like to add this character to the database? (yes/no): ";
            std::string add_new;
            std::cin >> add_new;
            std::transform(add_new.begin(), add_new.end(), add_new.begin(), ::tolower);
            if (add_new == "yes") {
                std::string character_name;
                SetColor(11); // Cyan
                std::cout << "Enter the name of the character: ";
                std::cin.ignore(); // Clear the input buffer
                getline(std::cin, character_name);
                addNewCharacter(character_name);
            }
            SetColor(7); // Reset to default color
            return; // Stop searching
        }

        // If two or more characters remain, ask differentiating questions
        if (possible_characters.size() > 1 && possible_characters.size() <= 5) {
            std::vector<int> differentiating_questions = getDifferentiatingQuestions(possible_characters);
            for (size_t idx : differentiating_questions) {
                // Skip questions that have been answered with "dn"
                if (asked_questions[idx]) continue;

                do {
                    SetColor(14); // Yellow
                    std::cout << questions[idx] << " (yes/no/dk): ";
                    std::cin >> answer;
                    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower); // Convert to lowercase for consistency

                    if (answer != "yes" && answer != "no" && answer != "dk") {
                        SetColor(12); // Red
                        std::cout << "Invalid input. Please enter 'yes', 'no', or 'dk'." << std::endl;
                    }
                } while (answer != "yes" && answer != "no" && answer != "dk");

                // Mark the question as asked if not "dn"
                if (answer == "dk") {
                    asked_questions[idx] = true;
                    continue;
                } else {
                    asked_questions[idx] = true;
                }

                // Save the response
                current_responses[idx] = (answer == "yes" ? "Yes" : "No");

                // Filter characters based on user response
                std::vector<std::shared_ptr<Character>> filtered_characters;
                for (const auto& character : possible_characters) {
                    if ((answer == "yes" && character->responses[idx] == "Yes") ||
                        (answer == "no" && character->responses[idx] == "No") ||
                        (character->responses[idx] == "I don't know")) {
                        filtered_characters.push_back(character);
                    }
                }
                possible_characters = filtered_characters;

                // Debugging output
                //SetColor(11); // Cyan

                // Stop searching if only one character matches
                if (possible_characters.size() == 1) {
                    SetColor(14); // Yellow
                    std::cout << "Is it " << possible_characters[0]->name << "? (yes/no): ";
                    std::cin >> answer;
                    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
                    if (answer == "yes") {
                        SetColor(10); // Green
                        std::cout << "Great! I guessed it right!" << std::endl;
                    } else {
                        // Ask for the correct character and add a new question if necessary
                        std::string character_name;
                        SetColor(11); // Cyan
                        std::cout << "Who is the character you were thinking of? ";
                        std::cin.ignore();
                        getline(std::cin, character_name);
                        addNewCharacter(character_name);
                    }
                    SetColor(7); // Reset to default color
                    return; // Stop searching
                }

                // Stop searching if no characters match
                if (possible_characters.empty()) {
                    SetColor(12); // Red
                    std::cout << "No matching character found." << std::endl;

                    // Ask if the user wants to add a new character
                    SetColor(11); // Cyan
                    std::cout << "Would you like to add this character to the database? (yes/no): ";
                    std::string add_new;
                    std::cin >> add_new;
                    std::transform(add_new.begin(), add_new.end(), add_new.begin(), ::tolower);
                    if (add_new == "yes") {
                        std::string character_name;
                        SetColor(11); // Cyan
                        std::cout << "Enter the name of the character: ";
                        std::cin.ignore(); // Clear the input buffer
                        getline(std::cin, character_name);
                        addNewCharacter(character_name);
                    }
                    SetColor(7); // Reset to default color
                    return; // Stop searching
                }
            }
        }
    }

    // If multiple characters match, ask about each character one by one
    if (!possible_characters.empty()) {
        SetColor(14); // Yellow
        std::cout << " THOUGH ONE. LET'S NARROW IT DOWN FURTHER." << std::endl;
        for (const auto& character : possible_characters) {
            SetColor(14); // Yellow
            std::cout << "Is it " << character->name << "? (yes/no): ";
            std::cin >> answer;
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            if (answer == "yes") {
                SetColor(10); // Green
                std::cout << "GREAT! I GUESSED IT RIGHT!" << std::endl;
                SetColor(7); // Reset to default color
                return; // Stop searching
            }
        }

        // If none of the characters matched, ask for the correct character
        SetColor(12); // Red
        std::cout << "None of the guessed characters matched. Who is the character you were thinking of? ";
        std::string character_name;
        std::cin.ignore();
        getline(std::cin, character_name);
        addNewCharacter(character_name);
        SetColor(7); // Reset to default color
    }
}

void Game::play() {
    while (true) {
        SetColor(10); // Green
        std::cout << std::endl;
        SetColor(9); // Blue
        std::cout << "1. Play Game" << std::endl;
        std::cout << "2. Exit" << std::endl;
        SetColor(10); // Green
        std::cout << "Enter your choice: ";

       int choice;
        std::cin >> choice;

        // Check if the input is not an integer
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
            SetColor(12); // Red
            std::cout << "Invalid choice. Please enter a number." << std::endl;
        } else {
            if (choice == 1) {
                printGenie();
                askQuestions();
            } else if (choice == 2) {
                SetColor(10); // Green
                std::cout << "GOODBYE! IT WAS A PLEASURE!" << std::endl;
                break;
            } else {
                SetColor(12); // Red
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        SetColor(7); // Reset to default color
    }
}
