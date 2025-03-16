/**
 * @file IPlayer.hpp
 * @brief Declares the IPlayer interface.
 *
 * An IPlayer represents an entity (human or AI) that can
 * participate in the Rock-Paper-Scissors game, track its own score,
 * and report its name.
 */

 #pragma once
 #include <string>
 
 /**
  * @brief Represents a participant in the game (human or computer).
  */
 class IPlayer {
 public:
     /**
      * @brief Virtual destructor for safe polymorphic cleanup.
      */
     virtual ~IPlayer() = default;
 
     /**
      * @brief Retrieves the player's name.
      * @return The player's name as a string.
      */
     virtual std::string GetName() const = 0;
 
     /**
      * @brief Retrieves the player's current score.
      * @return The score as an integer.
      */
     virtual int GetScore() const = 0;
 
     /**
      * @brief Increments the player's score by 1, indicating a win.
      */
     virtual void AddWin() = 0;
 };
 