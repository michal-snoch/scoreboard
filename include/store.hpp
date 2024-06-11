#pragma once

#include <string>
#include <set>

struct Store
{
    struct Entry
    {
        std::string homeTeam;
        std::string awayTeam;
        uint16_t homeScore;
        uint16_t awayScore;

        bool operator<(const Entry& other) const {
            return (homeTeam + "-" + awayTeam) < (other.homeTeam + "-" + other.awayTeam); 
        }
    };

    virtual void createOrUpdate(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore) = 0;
    virtual void remove(std::string homeTeam, std::string awayTeam) = 0;
    virtual const std::set<Entry>& getAll() const = 0;

    virtual ~Store() = default;
};
