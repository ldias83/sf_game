/**
 * @file UserPlayer.cpp
 * @brief Implements the UserPlayer class.
 */

 #include "UserPlayer.hpp"

 UserPlayer::UserPlayer(const std::string& userName)
     : m_name{"[User] " + userName}, m_score{}
 {
 }
 
 std::string UserPlayer::GetName() const {
     return m_name;
 }
 
 int UserPlayer::GetScore() const {
     return m_score;
 }
 
 void UserPlayer::AddWin() {
     ++m_score;
 }
 