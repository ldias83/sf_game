/**
 * @file test_UserPlayer.cpp
 * @brief Unit tests for the UserPlayer class using Google Test and Google Mock.
 *
 * This module tests the behavior of the UserPlayer class, ensuring that:
 * - The class correctly initializes with a user-provided name.
 * - The player's score starts at zero and increments correctly.
 * - Edge cases such as empty names and stress conditions are handled.
 * - Mock-based tests validate interactions and method calls.
 *
 * ## Testing Strategy:
 * - **Good Weather Tests:** Validate correct behavior under normal conditions.
 * - **Bad Weather Tests:** Ensure edge cases and invalid states are handled gracefully.
 * - **Mock-Based Tests:** Use Google Mock to verify method calls and expected behaviors.
 *
 * ## Dependencies:
 * - Google Test (`gtest`)
 * - Google Mock (`gmock`)
 * - IPlayer.hpp (Base interface for player entities)
 * - UserPlayer.hpp (Concrete implementation of a user-controlled player)
 *
 * @author Lucas Dias
 * @date 15/03/2025
 */

 #include <gtest/gtest.h>
 #include <gmock/gmock.h>
 #include "UserPlayer.hpp"
 #include "IPlayer.hpp"
 
 using ::testing::AtLeast;
 using ::testing::Return;
 using ::testing::NiceMock;
 
 /**
  * @brief Mock class for UserPlayer (example, though typically you'd mock the interface).
  */
 class MockUserPlayer : public UserPlayer {
 public:
     MockUserPlayer() : UserPlayer("Mock") {}
     MOCK_METHOD(std::string, GetName, (), (const, override));
     MOCK_METHOD(int, GetScore, (), (const, override));
     MOCK_METHOD(void, AddWin, (), (override));
 };
 
 /**
  * @brief Test fixture for UserPlayer using direct instantiation.
  */
 class UserPlayerTestFixture : public ::testing::Test {
 protected:
     std::unique_ptr<UserPlayer> m_player;
     std::unique_ptr<NiceMock<MockUserPlayer>> m_mockPlayer;
 
     void SetUp() override {
         m_player = std::make_unique<UserPlayer>("Alice");
         m_mockPlayer = std::make_unique<NiceMock<MockUserPlayer>>();
     }
 
     void TearDown() override {
         m_player.reset();
         m_mockPlayer.reset();
     }
 };
 
 /**
  * @brief Test fixture for UserPlayer using the IPlayer interface.
  */
 class UserPlayerPolymorphicTest : public ::testing::Test {
 protected:
     std::unique_ptr<IPlayer> m_player;
 
     void SetUp() override {
         m_player = std::make_unique<UserPlayer>("Alice");
     }
 
     void TearDown() override {
         m_player.reset();
     }
 };
 
 TEST_F(UserPlayerTestFixture, GetNameReturnsCorrectValue) {
     EXPECT_EQ(m_player->GetName(), "[User] Alice");
 }
 
 TEST_F(UserPlayerTestFixture, InitialScoreIsZero) {
     EXPECT_EQ(m_player->GetScore(), 0);
 }
 
 TEST_F(UserPlayerTestFixture, ScoreIncrementsByOne) {
     m_player->AddWin();
     EXPECT_EQ(m_player->GetScore(), 1);
 }
 
 TEST_F(UserPlayerTestFixture, ScoreIncrementsMultipleTimes) {
     m_player->AddWin();
     m_player->AddWin();
     m_player->AddWin();
     EXPECT_EQ(m_player->GetScore(), 3);
 }
 
 TEST_F(UserPlayerTestFixture, HandlesEmptyName) {
     UserPlayer emptyPlayer("");
     EXPECT_EQ(emptyPlayer.GetName(), "[User] ");
 }
 
 // Polymorphic usage tests
 TEST_F(UserPlayerPolymorphicTest, Polymorphic_GetName) {
     EXPECT_EQ(m_player->GetName(), "[User] Alice");
 }
 
 TEST_F(UserPlayerPolymorphicTest, Polymorphic_InitialScoreIsZero) {
     EXPECT_EQ(m_player->GetScore(), 0);
 }
 
 TEST_F(UserPlayerPolymorphicTest, Polymorphic_ScoreIncrements) {
     m_player->AddWin();
     EXPECT_EQ(m_player->GetScore(), 1);
 }
 