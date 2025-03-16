/**
 * @file SinglePlayerRpsGame.hpp
 * @brief Declares the SinglePlayerRpsGame class.
 *
 * SinglePlayerRpsGame implements a simple user-vs-computer version of
 * Rock-Paper-Scissors using the IGameSession interface.
 */

 #pragma once

 #include "IGameSession.hpp"
 #include "IPlayer.hpp"
 #include "IGameMessenger.hpp"
 #include "GameMove.hpp"
 #include <memory>
 #include <unordered_map>
 #include <functional>
 #include <tuple>
 
 /**
  * @brief Identifies which participant won a round (if any).
  */
 enum class ParticipantType
 {
     NoOne,
     User,
     Computer
 };
 
 /**
  * @brief Implements a single-player Rock-Paper-Scissors session with
  *        one user (human) player and one computer (AI) player.
  */
 class SinglePlayerRpsGame : public IGameSession {
 public:
     /**
      * @brief Constructs a SinglePlayerRpsGame.
      * @param userPlayer         The human user player.
      * @param computerPlayer     The computer (AI) player.
      * @param messenger          Messenger for input/output.
      * @param numberOfRounds     How many rounds to play.
      * @param randomGenerator    A function that returns random integers (used for AI moves).
      */
     SinglePlayerRpsGame(std::shared_ptr<IPlayer> userPlayer,
                         std::shared_ptr<IPlayer> computerPlayer,
                         std::unique_ptr<IGameMessenger> messenger,
                         int numberOfRounds,
                         std::function<int()> randomGenerator);
 
     /**
      * @brief Destructor.
      */
     virtual ~SinglePlayerRpsGame() = default;
 
     /**
      * @brief Starts the game loop for the configured number of rounds.
      */
     void Play() override;
 
 private:
     /**
      * @brief Gets the moves for both the user and the computer for a round.
      * @return A tuple: (isValidMove, userMove, computerMove).
      */
     std::tuple<bool, GameMove, GameMove> ObtainMoves();
 
     /**
      * @brief Displays both players' moves for the current round.
      * @param userMove The user's move.
      * @param computerMove The computer's move.
      */
     void DisplayRoundMoves(GameMove userMove, GameMove computerMove);
 
     /**
      * @brief Determines which participant won the round.
      * @param userMove The user's move.
      * @param computerMove The computer's move.
      * @return ParticipantType (NoOne, User, or Computer).
      */
     ParticipantType DetermineRoundOutcome(GameMove userMove, GameMove computerMove) const;
 
     /**
      * @brief Processes the round result, announces the outcome, and increments score if needed.
      * @param winnerType The type of participant who won (or NoOne).
      */
     void ProcessRoundResult(ParticipantType winnerType);
 
 private:
     /**
      * @brief Checks if both moves are the same.
      */
     static constexpr bool IsRoundDraw(GameMove userMove, GameMove computerMove) {
         return userMove == computerMove;
     }
 
     /**
      * @brief Checks if the user (human) player wins against the computer's move.
      */
     static constexpr bool DoesUserWinRound(GameMove userMove, GameMove computerMove) {
         return ((userMove == GameMove::Rock     && computerMove == GameMove::Scissors) ||
                 (userMove == GameMove::Paper    && computerMove == GameMove::Rock)     ||
                 (userMove == GameMove::Scissors && computerMove == GameMove::Paper));
     }
 
 private:
     std::shared_ptr<IPlayer> m_userPlayer {};
     std::shared_ptr<IPlayer> m_computerPlayer {};
     std::unique_ptr<IGameMessenger> m_messenger {};
     int m_numberOfRounds {};
     std::function<int()> m_randomGenerator {};
 
     /**
      * @brief Maps participant types to the actual player instances.
      */
     std::unordered_map<ParticipantType, std::shared_ptr<IPlayer>> m_playersByType {};
 };
 