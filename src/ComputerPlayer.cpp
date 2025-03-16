/**
 * @file ComputerPlayer.cpp
 * @brief Implements the ComputerPlayer class.
 */

 #include "ComputerPlayer.hpp"

 ComputerPlayer::ComputerPlayer(const std::string& computerName)
     : m_name{"[Computer] " + computerName}, m_score{}
 {
 }
 
 std::string ComputerPlayer::GetName() const {
     return m_name;
 }
 
 int ComputerPlayer::GetScore() const {
     return m_score;
 }
 
 void ComputerPlayer::AddWin() {
     ++m_score;
 }
 