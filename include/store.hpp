#pragma once

#include <string>
#include <list>

struct Store
{
    struct Entry
    {
        std::string homeTeam;
        std::string awayTeam;
        uint16_t homeScore;
        uint16_t awayScore;
    };

    virtual void createOrUpdate(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore) = 0;
    virtual void remove(std::string homeTeam, std::string awayTeam) = 0;
    virtual const std::list<Entry>& getAll() const = 0;

    virtual ~Store() = default;
};
