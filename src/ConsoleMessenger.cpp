/**
 * @file ConsoleMessenger.cpp
 * @brief Implements the ConsoleMessenger class.
 */

 #include "ConsoleMessenger.hpp"
 #include <iostream>
 #include <limits>
 
 void ConsoleMessenger::ShowWelcomeScreen() {
     std::cout << " *********************************************\n";
     std::cout << " **** Welcome to the Rock-Paper-Scissors! ****\n";
     std::cout << " *********************************************\n\n";
 }
 
 std::string ConsoleMessenger::RequestUserPlayerName() {
     std::cout << "Please enter the user player's name: ";
     std::string name {};
     std::cin >> name;
     return name;
 }
 
 std::string ConsoleMessenger::RequestComputerPlayerName() {
     std::cout << "Please enter the computer player's name: ";
     std::string name {};
     std::cin >> name;
     return name;
 }
 
 int ConsoleMessenger::RequestNumberOfRounds() {
     std::cout << "How many rounds do you want to play? ";
     int rounds {};
     std::cin >> rounds;
     if (!std::cin) {
         // Clear error state
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         return -1;
     }
     return rounds;
 }
 
 void ConsoleMessenger::ShowSetupComplete() {
     std::cout << "\nGreat, all set!\nLet's get started!\n\n";
 }
 
 int ConsoleMessenger::RequestMoveChoice() {
     std::cout << "Enter your move (1 = Rock, 2 = Paper, 3 = Scissors): ";
     int choice {};
     std::cin >> choice;
     if (!std::cin) {
         // Clear error state
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         return -1;
     }
     return choice;
 }
 
 void ConsoleMessenger::DisplayChosenMove(const std::shared_ptr<IPlayer>& player, GameMove move) {
     std::cout << player->GetName() << " chose: " << ConvertMoveToString(move) << "\n";
 }
 
 void ConsoleMessenger::AnnounceRoundWinner(const std::shared_ptr<IPlayer>& winner) {
     std::cout << winner->GetName() << " wins this round!\n\n";
 }
 
 void ConsoleMessenger::AnnounceDraw() {
     std::cout << "It's a draw!\n\n";
 }
 
 void ConsoleMessenger::ShowFinalScore(const std::shared_ptr<IPlayer>& userPlayer,
                                       const std::shared_ptr<IPlayer>& computerPlayer) {
     std::cout << "Final Score => "
               << userPlayer->GetName() << ": " << userPlayer->GetScore() << " | "
               << computerPlayer->GetName() << ": " << computerPlayer->GetScore() << "\n";
 }
 
 void ConsoleMessenger::ShowInvalidInputMessage() {
     std::cout << "Invalid input!\n\n";
 }
 
 std::string ConsoleMessenger::ConvertMoveToString(GameMove move) {
     switch(move) {
         case GameMove::Rock:     return "Rock";
         case GameMove::Paper:    return "Paper";
         case GameMove::Scissors: return "Scissors";
         default:                 return "Invalid";
     }
 }
 