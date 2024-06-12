#pragma once

#include "score_reader.hpp"
#include "score_updater.hpp"
#include "store.hpp"

class ScoreBoard : public ScoreReader, public ScoreUpdater
{
public:
    ScoreBoard(Store& store);
    
    virtual std::list<std::string> getGamesSummary() const;
    
    virtual void startNewGame(std::string homeTeam, std::string awayTeam);
    virtual void updateScore(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore);
    virtual void finishGame(std::string homeTeam, std::string awayTeam);

    virtual ~ScoreBoard() = default;

private:
    Store& store;
};
