/**
 * @file test_ConsoleMessenger.cpp
 * @brief Unit tests for the ConsoleMessenger class using Google Test.
 *
 * ## Test Strategy
 * Because ConsoleMessenger uses std::cin and std::cout directly, we redirect
 * the I/O streams in our tests to stringstreams. This lets us:
 * - Feed predefined input to the messenger.
 * - Capture and verify output (to confirm messages).
 *
 * ## Gherkin Tests
 * ### Scenario: ShowWelcomeScreen prints the welcome banner
 *   Given a ConsoleMessenger
 *   When ShowWelcomeScreen is called
 *   Then the output stream should contain "Welcome to the Rock-Paper-Scissors"
 *
 * ### Scenario: RequestUserPlayerName reads a name from input
 *   Given a user typed "Alice" in the input stream
 *   When RequestUserPlayerName is called
 *   Then it should return "Alice"
 *
 * ### Scenario: RequestNumberOfRounds returns -1 on invalid input
 *   Given a user typed a non-integer in the input
 *   When RequestNumberOfRounds is called
 *   Then it should return -1
 *
 * (And similarly for other prompts/methods.)
 */

 #include <gtest/gtest.h>
 #include <sstream>
 #include <string>
 #include <iostream>
 #include "ConsoleMessenger.hpp"
 
 /**
  * @brief Test fixture for ConsoleMessenger to redirect I/O streams.
  */
 class ConsoleMessengerTest : public ::testing::Test {
 protected:
     std::stringstream m_inputBuffer;
     std::stringstream m_outputBuffer;
     std::streambuf* m_oldCinBuf {nullptr};
     std::streambuf* m_oldCoutBuf {nullptr};
 
     ConsoleMessenger m_messenger; // The object under test
 
     void SetUp() override {
         // Redirect std::cin to read from m_inputBuffer
         m_oldCinBuf = std::cin.rdbuf(m_inputBuffer.rdbuf());
         // Redirect std::cout to write to m_outputBuffer
         m_oldCoutBuf = std::cout.rdbuf(m_outputBuffer.rdbuf());
     }
 
     void TearDown() override {
         // Restore original buffers
         std::cin.rdbuf(m_oldCinBuf);
         std::cout.rdbuf(m_oldCoutBuf);
     }
 };
 
 /**
  * @test Verifies the welcome screen output.
  */
 TEST_F(ConsoleMessengerTest, ShowWelcomeScreen_DisplaysBanner)
 {
     /**
      * Gherkin:
      *   Given a ConsoleMessenger
      *   When ShowWelcomeScreen is called
      *   Then the output should contain "Welcome to the Rock-Paper-Scissors"
      */
     m_messenger.ShowWelcomeScreen();
     std::string output = m_outputBuffer.str();
     EXPECT_NE(output.find("Welcome to the Rock-Paper-Scissors"), std::string::npos);
 }
 
 /**
  * @test Verifies the user name prompt reads a string from input.
  */
 TEST_F(ConsoleMessengerTest, RequestUserPlayerName_ReadsInputProperly)
 {
     /**
      * Gherkin:
      *   Given the user typed "Alice" in the input stream
      *   When RequestUserPlayerName is called
      *   Then it returns "Alice"
      */
     m_inputBuffer << "Alice\n";
     std::string name = m_messenger.RequestUserPlayerName();
     EXPECT_EQ(name, "Alice");
 }
 
 /**
  * @test Verifies RequestNumberOfRounds returns valid integer.
  */
 TEST_F(ConsoleMessengerTest, RequestNumberOfRounds_ValidInteger)
 {
     /**
      * Gherkin:
      *   Given the user typed "7" in the input stream
      *   When RequestNumberOfRounds is called
      *   Then it returns 7
      */
     m_inputBuffer << "7\n";
     int rounds = m_messenger.RequestNumberOfRounds();
     EXPECT_EQ(rounds, 7);
 }
 
 /**
  * @test Verifies RequestNumberOfRounds returns -1 on invalid input.
  */
 TEST_F(ConsoleMessengerTest, RequestNumberOfRounds_InvalidInput)
 {
     /**
      * Gherkin:
      *   Given a user typed invalid (non-integer) input
      *   When RequestNumberOfRounds is called
      *   Then it returns -1
      */
     m_inputBuffer << "abc\n";
     int rounds = m_messenger.RequestNumberOfRounds();
     EXPECT_EQ(rounds, -1);
 }
 
 /**
  * @test Verifies ShowInvalidInputMessage writes a message to output.
  */
 TEST_F(ConsoleMessengerTest, ShowInvalidInputMessage_WritesToOutput)
 {
     /**
      * Gherkin:
      *   Given a ConsoleMessenger
      *   When ShowInvalidInputMessage is called
      *   Then the output should contain "Invalid input!"
      */
     m_messenger.ShowInvalidInputMessage();
     std::string output = m_outputBuffer.str();
     EXPECT_NE(output.find("Invalid input!"), std::string::npos);
 }
 