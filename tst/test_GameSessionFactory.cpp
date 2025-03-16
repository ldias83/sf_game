/**
 * @file test_GameSessionFactory.cpp
 * @brief Unit tests for the GameSessionFactory class using Google Test and Google Mock.
 *
 * ## Test Strategy
 * This file verifies that GameSessionFactory correctly registers
 * and creates IGameSession objects for a given GameMode. We use a
 * mock IGameSession to confirm that creation works as intended.
 *
 * ## Gherkin Tests
 * ### Scenario: Registered mode creates valid game session
 *   Given a GameSessionFactory
 *   And a GameMode "ConsoleSinglePlayer"
 *   And a mock creation function returning a mock IGameSession
 *   When we call Create with that mode
 *   Then we get a non-null unique_ptr to the newly created session
 *
 * ### Scenario: Unregistered mode returns nullptr
 *   Given a GameSessionFactory
 *   When we call Create with a mode that wasn't registered
 *   Then it returns nullptr
 */

 #include <gtest/gtest.h>
 #include <gmock/gmock.h>
 #include <memory>
 #include "GameSessionFactory.hpp"
 #include "IGameSession.hpp"
 #include "GameMode.hpp"
 
 using ::testing::_;
 
 /**
  * @brief A mock IGameSession to test creation logic.
  */
 class MockGameSession : public IGameSession {
 public:
     MOCK_METHOD(void, Play, (), (override));
 };
 
 /**
  * @brief Test fixture for GameSessionFactory.
  */
 class GameSessionFactoryTest : public ::testing::Test {
 protected:
     void SetUp() override {
         // Optional setup
     }
 
     void TearDown() override {
         // Optional teardown
     }
 
     GameSessionFactory m_factory;
 };
 
 /**
  * @test Verifies that a registered mode returns a valid game session.
  */
 TEST_F(GameSessionFactoryTest, RegisteredModeReturnsValidSession)
 {
     /**
      * Gherkin:
      *   Given a GameSessionFactory
      *   And we register a mode with a function returning a new MockGameSession
      *   When we call Create with that mode
      *   Then we get a non-null pointer to the session
      */
     m_factory.RegisterGame(GameMode::ConsoleSinglePlayer, []() {
         return std::make_unique<MockGameSession>();
     });
 
     auto session = m_factory.Create(GameMode::ConsoleSinglePlayer);
     EXPECT_NE(session, nullptr);
 }
 
 /**
  * @test Verifies that an unregistered mode returns nullptr.
  */
 TEST_F(GameSessionFactoryTest, UnregisteredModeReturnsNullptr)
 {
     /**
      * Gherkin:
      *   Given a GameSessionFactory
      *   When we call Create with a mode that wasn't registered
      *   Then it returns nullptr
      */
     auto session = m_factory.Create(GameMode::ConsoleSinglePlayer);
     EXPECT_EQ(session, nullptr);
 }
 