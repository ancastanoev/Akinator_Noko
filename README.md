# Akinator_Noko

This project is a console-based implementation of an Akinator-like game where the system tries to guess a character you're thinking of by asking a series of questions. The game learns and expands its character database based on user interactions.

Project Structure
Headers
- Character.h: Defines the Character class.
- CharacterDatabase.h: Defines the CharacterDatabase class.
- Game.h: Defines the Game class.
- Utils.h: Contains utility functions, such as SetColor and printGenie.

Source Files
- Character.cpp: Implements the Character class.
- CharacterDatabase.cpp: Implements the CharacterDatabase class.
- Game.cpp: Implements the Game class.
- Utils.cpp: Implements the utility functions.
- main.cpp: Contains the main function and starts the game.

Prerequisites
- A C++ compiler
- Windows OS (for the console color functions)

Setup Instructions
Download the Source Code
- Ensure you have all the .h and .cpp files in the same directory.

Compile the Project
- You can compile the project using either the command line or an Integrated Development Environment (IDE).
  Using the Command Line
  - Compile the source files using a command like:
    g++ -o akinator main.cpp Character.cpp CharacterDatabase.cpp Game.cpp Utils.cpp
    This command compiles all the source files and links them into an executable named 'akinator'.

Run the Game
- Execute the compiled program:
  ./akinator

Playing the Game
Start the Game
- Run the executable. You will be greeted by Noko, the guessing master.

Menu Options
- 1. Play Game: Starts a new game session.
- 2. Exit: Exits the game.
  Any other input is invalid and the user is prompted to choose between "1" and "2".

Answering Questions
- The game will ask a series of yes/no/dk (don't know) questions. Respond with yes, no, or dk.
- If you input an invalid response, you will be prompted to enter a valid answer.

Character Guesses
- Based on your responses, the game will filter characters and try to guess who you're thinking of.
- If the game guesses correctly, you will be notified.
- If the game cannot guess correctly, you will be prompted to provide the name of the character you were thinking of. The game will then add this character to its database.

Adding New Characters
- If the game fails to find a matching character, it will ask if you want to add the character to the database.
- The information of the new character is acquired from the questions that led to the failure. Other information is set to "default as not known."

Character Database
- The character database is stored in a CSV file named characters.csv. The initial file contains a list of 30 characters. Each time nokonator fails and you add a new character, it will be saved in the csv together with its information. You can manually edit this file to add or modify characters directly.

Future Enhancements
- Implementing more complex filtering and guessing algorithms.
- Adding a graphical user interface (GUI).
- Allowing more nuanced responses beyond yes/no/dk.
