#include <gtest/gtest.h>
#include <memory_store.hpp>

struct MemoryStoreTestSuite : ::testing::Test
{
    MemoryStore store;

    void assertEntry(const Store::Entry& entry, const Store::Entry& compare)
    {
        EXPECT_EQ(compare.homeTeam, entry.homeTeam);
        EXPECT_EQ(compare.homeScore, entry.homeScore);
        EXPECT_EQ(compare.awayTeam, entry.awayTeam);
        EXPECT_EQ(compare.awayScore, entry.awayScore);
    }

    Store::Entry sampleEntry1 {
        "home team 1",
        "away team 1",
        2u,
        3u
    };

    Store::Entry sampleEntry2 {
        "home team 2",
        "away team 2",
        22u,
        13u
    };
};

TEST_F(MemoryStoreTestSuite, successfulCreationOfNewRecord)
{
    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, sampleEntry1.homeScore, sampleEntry1.awayScore);

    const auto& entries = store.getAll();
    EXPECT_EQ(1u, entries.size());

    assertEntry(sampleEntry1, *entries.begin());
}

TEST_F(MemoryStoreTestSuite, successfulUpdateOfExistingRecord)
{
    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, sampleEntry1.homeScore, sampleEntry1.awayScore);
    store.createOrUpdate(sampleEntry2.homeTeam, sampleEntry2.awayTeam, sampleEntry2.homeScore, sampleEntry2.awayScore);

    const auto& entries = store.getAll();
    EXPECT_EQ(2u, entries.size());

    const auto& entry = *entries.begin();
    assertEntry(sampleEntry1, *entries.begin());

    uint16_t homeTeamNewScore = 7u;
    uint16_t awayTeamNewScore = 8u;

    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, homeTeamNewScore, awayTeamNewScore);

    EXPECT_EQ(2u, entries.size());

    Store::Entry updatedEntry {
        sampleEntry1.homeTeam,
        sampleEntry1.awayTeam,
        homeTeamNewScore,
        awayTeamNewScore
    };

    assertEntry(*entries.begin(), updatedEntry);
}

TEST_F(MemoryStoreTestSuite, successfulCreationOfTwoRecords)
{
    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, sampleEntry1.homeScore, sampleEntry1.awayScore);
    store.createOrUpdate(sampleEntry2.homeTeam, sampleEntry2.awayTeam, sampleEntry2.homeScore, sampleEntry2.awayScore);

    const auto& entries = store.getAll();
    EXPECT_EQ(2u, entries.size());

    auto it = entries.cbegin();
    assertEntry(*it, sampleEntry1);
    it++;
    assertEntry(*it, sampleEntry2);
}

TEST_F(MemoryStoreTestSuite, singleRecordUpdatedWhenMultipleAvailable)
{
    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, sampleEntry1.homeScore, sampleEntry1.awayScore);
    store.createOrUpdate(sampleEntry2.homeTeam, sampleEntry2.awayTeam, sampleEntry2.homeScore, sampleEntry2.awayScore);

    const auto& entries = store.getAll();
    EXPECT_EQ(2u, entries.size());

    uint16_t homeTeamNewScore = 7u;
    uint16_t awayTeamNewScore = 8u;

    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, homeTeamNewScore, awayTeamNewScore);

    EXPECT_EQ(2u, entries.size());

    Store::Entry updatedEntry {
        sampleEntry1.homeTeam,
        sampleEntry1.awayTeam,
        homeTeamNewScore,
        awayTeamNewScore
    };

    assertEntry(*entries.begin(), updatedEntry);
}

TEST_F(MemoryStoreTestSuite, successfulRemovalOfOneRecord)
{
    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, sampleEntry1.homeScore, sampleEntry1.awayScore);
    store.createOrUpdate(sampleEntry2.homeTeam, sampleEntry2.awayTeam, sampleEntry2.homeScore, sampleEntry2.awayScore);
    store.remove(sampleEntry1.homeTeam, sampleEntry1.awayTeam);

    const auto& entries = store.getAll();
    EXPECT_EQ(1u, entries.size());

    auto it = entries.cbegin();
    assertEntry(*it, sampleEntry2);
}

TEST_F(MemoryStoreTestSuite, removalOfNotExistingRecordHaveNoEffect)
{
    store.createOrUpdate(sampleEntry1.homeTeam, sampleEntry1.awayTeam, sampleEntry1.homeScore, sampleEntry1.awayScore);
    store.createOrUpdate(sampleEntry2.homeTeam, sampleEntry2.awayTeam, sampleEntry2.homeScore, sampleEntry2.awayScore);
    store.remove(sampleEntry1.homeTeam, sampleEntry2.awayTeam);

    const auto& entries = store.getAll();
    EXPECT_EQ(2u, entries.size());

    auto it = entries.cbegin();
    assertEntry(*it, sampleEntry1);
    it++;
    assertEntry(*it, sampleEntry2);
}