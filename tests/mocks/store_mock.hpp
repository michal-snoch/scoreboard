#include <gmock/gmock.h>
#include <store.hpp>

struct StoreMock : Store
{
    MOCK_METHOD(void, createOrUpdate, (std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore), (override));
    MOCK_METHOD(void, remove, (std::string homeTeam, std::string awayTeam), (override));
    MOCK_METHOD(std::list<Store::Entry>&, getAll, (), (const, override));

    virtual ~StoreMock() = default;
};