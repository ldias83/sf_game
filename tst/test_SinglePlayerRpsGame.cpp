#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SinglePlayerRpsGame.hpp"
#include "IPlayer.hpp"
#include "IGameMessenger.hpp"
#include "GameMove.hpp"
#include <memory>

using ::testing::Return;
using ::testing::_;

/**
 * @brief Mock class for IPlayer.
 */
class MockPlayer : public IPlayer {
public:
    MOCK_METHOD(void, AddWin, (), (override));
    MOCK_METHOD(int, GetScore, (), (const, override));
    MOCK_METHOD(std::string, GetName, (), (const, override));
};

/**
 * @brief Mock class for IGameMessenger.
 */
class MockMessenger : public IGameMessenger {
public:
    MOCK_METHOD(void, ShowWelcomeScreen, (), (override));
    MOCK_METHOD(std::string, RequestUserPlayerName, (), (override));
    MOCK_METHOD(std::string, RequestComputerPlayerName, (), (override));
    MOCK_METHOD(int, RequestNumberOfRounds, (), (override));
    MOCK_METHOD(void, ShowSetupComplete, (), (override));
    MOCK_METHOD(int, RequestMoveChoice, (), (override));
    MOCK_METHOD(void, DisplayChosenMove, (const std::shared_ptr<IPlayer>&, GameMove), (override));
    MOCK_METHOD(void, AnnounceRoundWinner, (const std::shared_ptr<IPlayer>&), (override));
    MOCK_METHOD(void, AnnounceDraw, (), (override));
    MOCK_METHOD(void, ShowFinalScore, (const std::shared_ptr<IPlayer>&, const std::shared_ptr<IPlayer>&), (override));
    MOCK_METHOD(void, ShowInvalidInputMessage, (), (override));
};

/**
 * @brief Helper to check if a player's name matches the expected value.
 */
static auto HasPlayerName(const std::string& expectedName) {
    return testing::Truly([expectedName](const std::shared_ptr<IPlayer>& p) {
        return p && p->GetName() == expectedName;
    });
}

/**
 * @brief Test fixture for SinglePlayerRpsGame.
 */
class SinglePlayerRpsGameTest : public ::testing::Test {
protected:
    // Store mock objects as base pointers:
    std::shared_ptr<IPlayer> m_user;
    std::shared_ptr<IPlayer> m_computer;

    std::unique_ptr<MockMessenger> m_messenger;
    MockMessenger* m_rawMessengerPtr;

    std::unique_ptr<SinglePlayerRpsGame> m_game;

    int m_mockRandomValue{};
    std::function<int()> m_mockRandomGenerator;

    void SetUp() override {
        // Create mock objects:
        auto userMockPtr = std::make_shared<MockPlayer>();
        auto computerMockPtr = std::make_shared<MockPlayer>();

        // By storing them as IPlayer, we ensure calls match IGameMessenger's signature.
        m_user = userMockPtr;
        m_computer = computerMockPtr;

        // Default stubs:
        ON_CALL(*std::static_pointer_cast<MockPlayer>(m_user), GetName())
            .WillByDefault(Return("[User] Alice"));
        ON_CALL(*std::static_pointer_cast<MockPlayer>(m_computer), GetName())
            .WillByDefault(Return("[Computer] Hal"));

        // Create and store MockMessenger:
        m_messenger = std::make_unique<MockMessenger>();
        m_rawMessengerPtr = m_messenger.get();

        // Our mock random generator
        m_mockRandomGenerator = [this]() { return m_mockRandomValue; };

        // Create the game with just 1 round for simplicity
        m_game = std::make_unique<SinglePlayerRpsGame>(
            m_user,           // user as IPlayer
            m_computer,       // computer as IPlayer
            std::move(m_messenger),
            1,
            m_mockRandomGenerator
        );
    }
};

/**
 * @test Verify that invalid input triggers an error message.
 */
TEST_F(SinglePlayerRpsGameTest, InvalidInputShowsError) {
    // If the user picks "5" => invalid
    EXPECT_CALL(*m_rawMessengerPtr, RequestMoveChoice())
        .WillOnce(Return(5));

    EXPECT_CALL(*m_rawMessengerPtr, ShowInvalidInputMessage()).Times(1);
    EXPECT_CALL(*m_rawMessengerPtr, ShowFinalScore(m_user, m_computer)).Times(1);

    m_game->Play();
}

/**
 * @test Verify user wins properly (Rock vs Scissors).
 */
TEST_F(SinglePlayerRpsGameTest, UserWinIsProcessedCorrectly) {
    // user picks Rock (1)
    EXPECT_CALL(*m_rawMessengerPtr, RequestMoveChoice())
        .WillOnce(Return(1));

    // computer picks Scissors (3)
    m_mockRandomValue = 3;

    // Cast back to MockPlayer to set the expectations:
    auto userMock = std::static_pointer_cast<MockPlayer>(m_user);
    auto computerMock = std::static_pointer_cast<MockPlayer>(m_computer);

    EXPECT_CALL(*m_rawMessengerPtr, DisplayChosenMove(HasPlayerName("[User] Alice"), GameMove::Rock));
    EXPECT_CALL(*m_rawMessengerPtr, DisplayChosenMove(HasPlayerName("[Computer] Hal"), GameMove::Scissors));
    EXPECT_CALL(*userMock, AddWin()).Times(1);
    EXPECT_CALL(*m_rawMessengerPtr, AnnounceRoundWinner(HasPlayerName("[User] Alice")));
    EXPECT_CALL(*m_rawMessengerPtr, ShowFinalScore(m_user, m_computer)).Times(1);

    m_game->Play();
}

/**
 * @test Verify computer wins properly (Rock vs Scissors reversed).
 */
TEST_F(SinglePlayerRpsGameTest, ComputerWinIsProcessedCorrectly) {
    // user picks Scissors (3)
    EXPECT_CALL(*m_rawMessengerPtr, RequestMoveChoice())
        .WillOnce(Return(3));

    // computer picks Rock (1)
    m_mockRandomValue = 1;

    auto userMock = std::static_pointer_cast<MockPlayer>(m_user);
    auto computerMock = std::static_pointer_cast<MockPlayer>(m_computer);

    EXPECT_CALL(*m_rawMessengerPtr, DisplayChosenMove(HasPlayerName("[User] Alice"), GameMove::Scissors));
    EXPECT_CALL(*m_rawMessengerPtr, DisplayChosenMove(HasPlayerName("[Computer] Hal"), GameMove::Rock));
    EXPECT_CALL(*computerMock, AddWin()).Times(1);
    EXPECT_CALL(*m_rawMessengerPtr, AnnounceRoundWinner(HasPlayerName("[Computer] Hal")));
    EXPECT_CALL(*m_rawMessengerPtr, ShowFinalScore(m_user, m_computer)).Times(1);

    m_game->Play();
}

/**
 * @test Verify a draw scenario (Paper vs Paper).
 */
TEST_F(SinglePlayerRpsGameTest, DrawIsHandledCorrectly) {
    // user picks Paper (2)
    EXPECT_CALL(*m_rawMessengerPtr, RequestMoveChoice())
        .WillOnce(Return(2));

    // computer picks Paper (2)
    m_mockRandomValue = 2;

    EXPECT_CALL(*m_rawMessengerPtr, DisplayChosenMove(HasPlayerName("[User] Alice"), GameMove::Paper));
    EXPECT_CALL(*m_rawMessengerPtr, DisplayChosenMove(HasPlayerName("[Computer] Hal"), GameMove::Paper));
    EXPECT_CALL(*m_rawMessengerPtr, AnnounceDraw());
    EXPECT_CALL(*m_rawMessengerPtr, ShowFinalScore(m_user, m_computer)).Times(1);

    m_game->Play();
}
