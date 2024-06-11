#include <string>

class ScoreUpdater
{
    void startNewGame(std::string homeTeam, std::string awayTeam) = 0;
    void updateScore(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore) = 0;
    void finishGame(std::string homeTeam, std::string awayTeam) = 0;
    virtual ~ScoreUpdater() {}
}