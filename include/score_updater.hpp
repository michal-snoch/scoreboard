#pragma once

#include <string>

struct ScoreUpdater
{
    virtual void startNewGame(std::string homeTeam, std::string awayTeam) = 0;
    virtual void updateScore(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore) = 0;
    virtual void finishGame(std::string homeTeam, std::string awayTeam) = 0;
    virtual ~ScoreUpdater() = default;
};