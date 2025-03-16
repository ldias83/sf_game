/**
 * @file UserPlayer.hpp
 * @brief Declares the UserPlayer class.
 *
 * UserPlayer represents a human-controlled participant in
 * the Rock-Paper-Scissors game.
 */

 #pragma once

 #include "IPlayer.hpp"
 #include <string>
 
 /**
  * @brief Represents a human-controlled participant in the game.
  */
 class UserPlayer : public IPlayer {
 public:
     /**
      * @brief Constructs a user (human) player with the provided name.
      * @param userName The custom name for this human participant.
      */
     explicit UserPlayer(const std::string& userName);
 
     /**
      * @brief Virtual destructor.
      */
     virtual ~UserPlayer() = default;
 
     std::string GetName() const override;
     int GetScore() const override;
     void AddWin() override;
 
 private:
     std::string m_name {};
     int m_score {};
 };
 