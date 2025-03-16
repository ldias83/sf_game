/**
 * @file SinglePlayerRpsGame.cpp
 * @brief Implements the SinglePlayerRpsGame class.
 */

 #include "SinglePlayerRpsGame.hpp"

 SinglePlayerRpsGame::SinglePlayerRpsGame(std::shared_ptr<IPlayer> userPlayer,
                                          std::shared_ptr<IPlayer> computerPlayer,
                                          std::unique_ptr<IGameMessenger> messenger,
                                          int numberOfRounds,
                                          std::function<int()> randomGenerator)
     : m_userPlayer{userPlayer},
       m_computerPlayer{computerPlayer},
       m_messenger{std::move(messenger)},
       m_numberOfRounds{numberOfRounds},
       m_randomGenerator{std::move(randomGenerator)}
 {
     m_playersByType[ParticipantType::User]      = m_userPlayer;
     m_playersByType[ParticipantType::Computer]  = m_computerPlayer;
 }
 
 void SinglePlayerRpsGame::Play() {
     for (int i{}; i < m_numberOfRounds; ++i) {
         auto [isValidMove, userMove, computerMove] = ObtainMoves();
 
         if (!isValidMove) {
             m_messenger->ShowInvalidInputMessage();
         } else {
             DisplayRoundMoves(userMove, computerMove);
             ParticipantType winnerType = DetermineRoundOutcome(userMove, computerMove);
             ProcessRoundResult(winnerType);
         }
     }
 
     // After all rounds, show final score
     m_messenger->ShowFinalScore(m_userPlayer, m_computerPlayer);
 }
 
 std::tuple<bool, GameMove, GameMove> SinglePlayerRpsGame::ObtainMoves() {
     // User picks a move (or gets -1 if invalid).
     int userChoice { m_messenger->RequestMoveChoice() };
     bool isValidMove { (userChoice >= 1 && userChoice <= 3) };
 
     GameMove userMove = static_cast<GameMove>(userChoice);
     GameMove computerMove = static_cast<GameMove>(1 + (m_randomGenerator() % 3));
 
     return { isValidMove, userMove, computerMove };
 }
 
 void SinglePlayerRpsGame::DisplayRoundMoves(GameMove userMove, GameMove computerMove) {
     m_messenger->DisplayChosenMove(m_userPlayer, userMove);
     m_messenger->DisplayChosenMove(m_computerPlayer, computerMove);
 }
 
 ParticipantType SinglePlayerRpsGame::DetermineRoundOutcome(GameMove userMove, GameMove computerMove) const {
     if (IsRoundDraw(userMove, computerMove)) {
         return ParticipantType::NoOne;
     }
     if (DoesUserWinRound(userMove, computerMove)) {
         return ParticipantType::User;
     }
     return ParticipantType::Computer;
 }
 
 void SinglePlayerRpsGame::ProcessRoundResult(ParticipantType winnerType) {
     if (winnerType == ParticipantType::NoOne) {
         m_messenger->AnnounceDraw();
     } else {
         m_playersByType[winnerType]->AddWin();
         m_messenger->AnnounceRoundWinner(m_playersByType[winnerType]);
     }
 }
 