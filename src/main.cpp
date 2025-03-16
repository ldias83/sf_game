/**
 * @file main.cpp
 * @brief The entry point for the Rock-Paper-Scissors application.
 *
 * This file creates and configures a GameSessionFactory, registers
 * a SinglePlayerRpsGame (user vs. computer), and runs the game session.
 *
 * Note: std::rand() is used here for simplicity. For production,
 *       consider <random> utilities for better randomness.
 */

 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 #include "GameSessionFactory.hpp"
 #include "SinglePlayerRpsGame.hpp"
 #include "UserPlayer.hpp"
 #include "ComputerPlayer.hpp"
 #include "ConsoleMessenger.hpp"
 
 int main()
 {
     // Seed the pseudo-random number generator
     std::srand(static_cast<unsigned>(std::time(nullptr)));
 
     // Create a console-based messenger for I/O
     std::unique_ptr<IGameMessenger> messenger = std::make_unique<ConsoleMessenger>();
     messenger->ShowWelcomeScreen();
 
     // Request user inputs
     std::string userName { messenger->RequestUserPlayerName() };
     std::string computerName { messenger->RequestComputerPlayerName() };
     int rounds { messenger->RequestNumberOfRounds() };
     if (rounds < 1) {
         std::cout << "Invalid number of rounds. Exiting...\n";
         return 1;
     }
 
     messenger->ShowSetupComplete();
 
     // Create the factory and register our single-player console-based game
     GameSessionFactory factory;
     factory.RegisterGame(GameMode::ConsoleSinglePlayer, [=]() {
         return std::make_unique<SinglePlayerRpsGame>(
             std::make_shared<UserPlayer>(userName),
             std::make_shared<ComputerPlayer>(computerName),
             std::make_unique<ConsoleMessenger>(),
             rounds,
             []() { return std::rand(); }
         );
     });
 
     // Create the game session from the factory
     std::unique_ptr<IGameSession> gameSession = factory.Create(GameMode::ConsoleSinglePlayer);
     if (!gameSession) {
         std::cout << "Failed to create game session.\n";
         return 1;
     }
 
     // Start the game
     gameSession->Play();
     return 0;
 }
 