/**
 * @file IGameSession.hpp
 * @brief Declares the IGameSession interface.
 *
 * An IGameSession represents a playable session of the game.
 * It can be started by calling Play().
 */

 #pragma once

 /**
  * @brief An interface for a playable Rock-Paper-Scissors session.
  */
 class IGameSession {
 public:
     /**
      * @brief Virtual destructor for IGameSession.
      */
     virtual ~IGameSession() = default;
 
     /**
      * @brief Starts and runs the game session.
      */
     virtual void Play() = 0;
 };
 