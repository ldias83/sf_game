/**
 * @file test_ComputerPlayer.cpp
 * @brief Unit tests for the ComputerPlayer class using Google Test.
 *
 * ## Test Strategy
 * This file verifies correct behavior of the ComputerPlayer:
 * - Ensures that the name is formatted as expected.
 * - Confirms the initial score is zero.
 * - Validates that AddWin increments the score properly.
 *
 * ## Gherkin Tests
 * ### Scenario: ComputerPlayer name is returned correctly
 *   Given a ComputerPlayer initialized with a name
 *   When GetName is called
 *   Then it returns "[Computer] " + name
 *
 * ### Scenario: ComputerPlayer starts with 0 score
 *   Given a newly constructed ComputerPlayer
 *   When GetScore is called
 *   Then it returns 0
 *
 * ### Scenario: ComputerPlayer increments score
 *   Given a ComputerPlayer
 *   When AddWin is called N times
 *   Then GetScore should return N
 */

 #include <gtest/gtest.h>
 #include "ComputerPlayer.hpp"
 
 /**
  * @brief Test fixture for ComputerPlayer.
  */
 class ComputerPlayerTest : public ::testing::Test {
 protected:
     void SetUp() override {
         // Optional setup
     }
 
     void TearDown() override {
         // Optional teardown
     }
 };
 
 /**
  * @test Verifies that the ComputerPlayer name is formatted properly.
  */
 TEST_F(ComputerPlayerTest, ComputerPlayerNameIsFormattedCorrectly)
 {
     ComputerPlayer comp{"HAL9000"};
     EXPECT_EQ(comp.GetName(), "[Computer] HAL9000");
 }
 
 /**
  * @test Verifies that the initial score is 0.
  */
 TEST_F(ComputerPlayerTest, InitialScoreIsZero)
 {
     ComputerPlayer comp{"R2D2"};
     EXPECT_EQ(comp.GetScore(), 0);
 }
 
 /**
  * @test Verifies that AddWin increments the score.
  */
 TEST_F(ComputerPlayerTest, ScoreIncrementsByOne)
 {
     ComputerPlayer comp{"C3PO"};
     comp.AddWin();
     EXPECT_EQ(comp.GetScore(), 1);
 
     comp.AddWin();
     comp.AddWin();
     EXPECT_EQ(comp.GetScore(), 3);
 }
 