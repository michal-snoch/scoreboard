#include <gtest/gtest.h>
#include <score_board.hpp>
#include "mocks/store_mock.hpp"

struct ScoreUpdaterTestSuite : ::testing::Test
{
    StoreMock storeMock;
    std::unique_ptr<ScoreUpdater> updater = std::make_unique<ScoreBoard>(storeMock);

    std::list<Store::Entry> emptyStore;

    ScoreUpdaterTestSuite() {
        ON_CALL(storeMock, getAll()).WillByDefault(::testing::ReturnRef(emptyStore));
    }
};

TEST_F(ScoreUpdaterTestSuite, startingNewGameSuccesfully)
{
    std::string team1Name = "Team 1";
    std::string team2Name = "Team 2";

    EXPECT_CALL(storeMock, createOrUpdate(team1Name, team2Name, 0u, 0u));
    updater->startNewGame(team1Name, team2Name);
}

TEST_F(ScoreUpdaterTestSuite, startingAlreadyExisitingGameNotAllowedXYZ)
{
    using namespace ::testing;

    std::string duplicatedTeam1Name = "Team 1";
    std::string duplicatedTeam2Name = "Team 2";

    std::list<Store::Entry> storage = {
        { duplicatedTeam1Name, duplicatedTeam2Name, 1u, 1u}
    };

    EXPECT_CALL(storeMock, getAll).WillRepeatedly(::testing::ReturnRef(storage));
    EXPECT_CALL(storeMock, createOrUpdate(_, _, _, _)).Times(0u);

    updater->startNewGame(duplicatedTeam1Name, duplicatedTeam2Name);
}

TEST_F(ScoreUpdaterTestSuite, updatingScoreSuccesfully)
{
    std::string team1Name = "Team 1";
    std::string team2Name = "Team 2";
    uint16_t team1NewScore = 3u;
    uint16_t team2NewScore = 4u;

    std::list<Store::Entry> storage = { { team1Name, team2Name, 1u, 1u} };
    EXPECT_CALL(storeMock, getAll).WillRepeatedly(::testing::ReturnRef(storage));
    EXPECT_CALL(storeMock, createOrUpdate(team1Name, team2Name, team1NewScore, team2NewScore));

    updater->updateScore(team1Name, team2Name, team1NewScore, team2NewScore);
}

TEST_F(ScoreUpdaterTestSuite, updatingScoreOnNonExistingEntryHasNoEffect)
{
    using namespace ::testing;

    EXPECT_CALL(storeMock, getAll).WillRepeatedly(ReturnRef(emptyStore));
    EXPECT_CALL(storeMock, createOrUpdate(_, _, _, _)).Times(0u);

    updater->updateScore("team1Name", "team2Name", 0u, 0u);
}

TEST_F(ScoreUpdaterTestSuite, finishingGameSuccesfully)
{
    std::string team1Name = "Team 1";
    std::string team2Name = "Team 2";

    std::list<Store::Entry> storage = { { team1Name, team2Name, 1u, 1u} };
    EXPECT_CALL(storeMock, getAll).WillRepeatedly(::testing::ReturnRef(storage));
    EXPECT_CALL(storeMock, remove(team1Name, team2Name));

    updater->finishGame(team1Name, team2Name);
}

TEST_F(ScoreUpdaterTestSuite, finishingGameOnNonExistingEntryHasNoEffect)
{
    using namespace ::testing;

    EXPECT_CALL(storeMock, getAll).WillRepeatedly(ReturnRef(emptyStore));
    EXPECT_CALL(storeMock, remove(_, _)).Times(0u);

    updater->finishGame("team1Name", "team2Name");
}
