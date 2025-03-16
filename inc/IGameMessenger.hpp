/**
 * @file IGameMessenger.hpp
 * @brief Declares the IGameMessenger interface.
 *
 * IGameMessenger handles all user interaction, such as
 * displaying prompts and reading input from a particular medium
 * (e.g., console, GUI, network).
 */

 #pragma once

 #include <memory>
 #include <string>
 #include "IPlayer.hpp"
 #include "GameMove.hpp"
 
 /**
  * @brief An interface responsible for game-related input/output.
  */
 class IGameMessenger {
 public:
     /**
      * @brief Virtual destructor for IGameMessenger.
      */
     virtual ~IGameMessenger() = default;
 
     /**
      * @brief Displays a welcome or introduction message.
      */
     virtual void ShowWelcomeScreen() = 0;
 
     /**
      * @brief Requests the user player's name.
      * @return The name entered by the user.
      */
     virtual std::string RequestUserPlayerName() = 0;
 
     /**
      * @brief Requests the computer player's name.
      * @return The name entered (or chosen) for the computer.
      */
     virtual std::string RequestComputerPlayerName() = 0;
 
     /**
      * @brief Requests the number of rounds to play.
      * @return The integer representing how many rounds to play (or -1 if invalid).
      */
     virtual int RequestNumberOfRounds() = 0;
 
     /**
      * @brief Indicates that setup is complete and the game is ready to start.
      */
     virtual void ShowSetupComplete() = 0;
 
     /**
      * @brief Requests a move choice from the human participant.
      * @return The chosen move as an integer (1=Rock, 2=Paper, 3=Scissors), or -1 if invalid.
      */
     virtual int RequestMoveChoice() = 0;
 
     /**
      * @brief Displays the chosen move for a participant.
      * @param player The player who made the move.
      * @param move The move made by the player.
      */
     virtual void DisplayChosenMove(const std::shared_ptr<IPlayer>& player, GameMove move) = 0;
 
     /**
      * @brief Announces the winner of a round.
      * @param winner The player who won the round.
      */
     virtual void AnnounceRoundWinner(const std::shared_ptr<IPlayer>& winner) = 0;
 
     /**
      * @brief Announces a draw in the current round.
      */
     virtual void AnnounceDraw() = 0;
 
     /**
      * @brief Shows the final score of the user vs. computer match.
      * @param userPlayer The user (human) player.
      * @param computerPlayer The computer (AI) player.
      */
     virtual void ShowFinalScore(const std::shared_ptr<IPlayer>& userPlayer,
                                 const std::shared_ptr<IPlayer>& computerPlayer) = 0;
 
     /**
      * @brief Notifies that the user's input was invalid or unrecognized.
      */
     virtual void ShowInvalidInputMessage() = 0;
 };
 