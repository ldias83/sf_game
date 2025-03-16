/**
 * @file GameSessionFactory.hpp
 * @brief Declares the GameSessionFactory class.
 *
 * GameSessionFactory creates IGameSession objects for the specified
 * GameMode by storing and invoking registered creation functions.
 */

 #pragma once

 #include "GameMode.hpp"
 #include "IGameSession.hpp"
 #include <functional>
 #include <memory>
 #include <unordered_map>
 
 /**
  * @brief A factory class that can create different types of game sessions.
  */
 class GameSessionFactory {
 public:
     /**
      * @brief Type alias for the function that creates a new IGameSession.
      */
     using CreatorFunc = std::function<std::unique_ptr<IGameSession>()>;
 
     /**
      * @brief Default constructor.
      */
     GameSessionFactory() = default;
 
     /**
      * @brief Default destructor.
      */
     ~GameSessionFactory() = default;
 
     /**
      * @brief Registers a creation function for a specific GameMode.
      * @param mode The game mode to register.
      * @param func The function that creates the corresponding IGameSession.
      */
     void RegisterGame(GameMode mode, CreatorFunc func);
 
     /**
      * @brief Creates an IGameSession for the given GameMode.
      * @param mode The game mode for which to create the session.
      * @return A unique_ptr to the created session, or nullptr if mode not found.
      */
     std::unique_ptr<IGameSession> Create(GameMode mode);
 
 private:
     std::unordered_map<GameMode, CreatorFunc> m_registry {};
 };
 