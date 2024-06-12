#include <gtest/gtest.h>
#include <score_board.hpp>
#include "mocks/store_mock.hpp"

struct ScoreReaderTestSuite : ::testing::Test
{
    StoreMock storeMock;
    std::unique_ptr<ScoreReader> reader = std::make_unique<ScoreBoard>(storeMock);
};

TEST_F(ScoreReaderTestSuite, noGamesInProgress)
{
    std::list<Store::Entry> emptyStore;

    EXPECT_CALL(storeMock, getAll).WillRepeatedly(::testing::ReturnRef(emptyStore));
    auto summary = reader->getGamesSummary();
    EXPECT_EQ(0u, summary.size());
}

TEST_F(ScoreReaderTestSuite, gamesOrderedByTotalScore)
{
    std::list<Store::Entry> storage = {
        { "T1", "T2", 3u, 4u},
        { "T3", "T4", 1u, 1u},
        { "T5", "T6", 0u, 0u},
        { "T7", "T8", 5u, 3u}
    };

    std::list<std::string> expectedResult = {
        "T7 5 - T8 3",
        "T1 3 - T2 4",
        "T3 1 - T4 1",
        "T5 0 - T6 0"
    };

    EXPECT_CALL(storeMock, getAll).WillRepeatedly(::testing::ReturnRef(storage));
    EXPECT_EQ(expectedResult, reader->getGamesSummary());
}

TEST_F(ScoreReaderTestSuite, storeOrderPreservedIfResultsSummaryEqual)
{
    std::list<Store::Entry> storage = {
        { "T1", "T2", 3u, 4u},
        { "T3", "T4", 2u, 1u},
        { "T5", "T6", 0u, 0u},
        { "T7", "T8", 1u, 2u}
    };

    std::list<std::string> expectedResult = {
        "T1 3 - T2 4",
        "T3 2 - T4 1",
        "T7 1 - T8 2",
        "T5 0 - T6 0"
    };

    EXPECT_CALL(storeMock, getAll).WillRepeatedly(::testing::ReturnRef(storage));
    EXPECT_EQ(expectedResult, reader->getGamesSummary());
}
