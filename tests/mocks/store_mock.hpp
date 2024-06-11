#include <gmock/gmock.h>
#include <store.hpp>

struct StoreMock : Store
{
    MOCK_METHOD(void, remove, (std::string homeTeam, std::string awayTeam), (override));

    virtual ~StoreMock() = default;
};