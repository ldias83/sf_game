/**
 * @file ConsoleMessenger.hpp
 * @brief Declares the ConsoleMessenger class.
 *
 * ConsoleMessenger is a concrete implementation of IGameMessenger
 * that uses standard console I/O (std::cin/std::cout).
 */

 #pragma once

 #include "IGameMessenger.hpp"
 #include <memory>
 #include <string>
 
 /**
  * @brief A console-based implementation of IGameMessenger using std::cin/std::cout.
  */
 class ConsoleMessenger : public IGameMessenger {
 public:
     ConsoleMessenger() = default;
     virtual ~ConsoleMessenger() = default;
 
     void ShowWelcomeScreen() override;
     std::string RequestUserPlayerName() override;
     std::string RequestComputerPlayerName() override;
     int RequestNumberOfRounds() override;
     void ShowSetupComplete() override;
     int RequestMoveChoice() override;
     void DisplayChosenMove(const std::shared_ptr<IPlayer>& player, GameMove move) override;
     void AnnounceRoundWinner(const std::shared_ptr<IPlayer>& winner) override;
     void AnnounceDraw() override;
     void ShowFinalScore(const std::shared_ptr<IPlayer>& userPlayer,
                         const std::shared_ptr<IPlayer>& computerPlayer) override;
     void ShowInvalidInputMessage() override;
 
 private:
     /**
      * @brief Converts a GameMove enum to a human-readable string.
      * @param move The GameMove value.
      * @return A string representing the GameMove.
      */
     static std::string ConvertMoveToString(GameMove move);
 };
 