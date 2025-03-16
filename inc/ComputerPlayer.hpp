/**
 * @file ComputerPlayer.hpp
 * @brief Declares the ComputerPlayer class.
 *
 * ComputerPlayer represents a computer-controlled (AI) participant
 * in the Rock-Paper-Scissors game.
 */

 #pragma once

 #include "IPlayer.hpp"
 #include <string>
 
 /**
  * @brief Represents an AI-controlled participant in the game.
  */
 class ComputerPlayer : public IPlayer {
 public:
     /**
      * @brief Constructs a ComputerPlayer with the provided name.
      * @param computerName The custom name for this computer participant.
      */
     explicit ComputerPlayer(const std::string& computerName);
 
     /**
      * @brief Virtual destructor.
      */
     virtual ~ComputerPlayer() = default;
 
     std::string GetName() const override;
     int GetScore() const override;
     void AddWin() override;
 
 private:
     std::string m_name {};
     int m_score {};
 };
 