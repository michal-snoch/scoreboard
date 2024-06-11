#pragma once

#include "store.hpp"

class MemoryStore : public Store
{
public:
    virtual void createOrUpdate(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore);
    virtual void remove(std::string homeTeam, std::string awayTeam);
    virtual std::set<Store::Entry> getAll() const;

    virtual ~MemoryStore() = default;
};