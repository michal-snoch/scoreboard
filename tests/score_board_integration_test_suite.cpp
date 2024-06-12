#include <gtest/gtest.h>
#include <score_board.hpp>
#include <memory_store.hpp>

struct ScoreBoardIntegrationTestSuite : ::testing::Test
{
    MemoryStore store;
    ScoreBoard board{store};
};

TEST_F(ScoreBoardIntegrationTestSuite, IntegrationTest)
{
    // Storage is empty on the start
    EXPECT_EQ(0u, store.getAll().size());
    EXPECT_EQ(0u, board.getGamesSummary().size());

    // Once we start first game, it is returned successfuly
    board.startNewGame("Team A", "Team B");
    EXPECT_EQ(1u, store.getAll().size());

    auto summary = board.getGamesSummary();
    EXPECT_EQ(1u, summary.size());
    EXPECT_EQ("Team A 0 - Team B 0", summary.front());

    // Updating results
    board.updateScore("Team A", "Team B", 1u, 0u);
    summary = board.getGamesSummary();
    EXPECT_EQ(1u, summary.size());
    EXPECT_EQ("Team A 1 - Team B 0", summary.front());

    // Finishing the game
    board.finishGame("Team A", "Team B");
    EXPECT_EQ(0u, store.getAll().size());
    EXPECT_EQ(0u, board.getGamesSummary().size());
}
