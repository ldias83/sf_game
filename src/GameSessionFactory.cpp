/**
 * @file GameSessionFactory.cpp
 * @brief Implements the GameSessionFactory class.
 */

 #include "GameSessionFactory.hpp"

 void GameSessionFactory::RegisterGame(GameMode mode, CreatorFunc func) {
     m_registry[mode] = std::move(func);
 }
 
 std::unique_ptr<IGameSession> GameSessionFactory::Create(GameMode mode) {
     auto it = m_registry.find(mode);
     if (it != m_registry.end()) {
         return it->second();
     }
     return nullptr;
 }
 