#include <score_board.hpp>
#include <algorithm>
#include <format>

ScoreBoard::ScoreBoard(Store& store) : store(store)
{
}

std::list<std::string> ScoreBoard::getGamesSummary() const
{
    const auto& storedEntries = store.getAll();

    std::vector<Store::Entry> entries(storedEntries.rbegin(), storedEntries.rend());
    std::stable_sort(entries.begin(), entries.end(), [](const auto& e1, const auto& e2) {
        return (e1.homeScore + e1.awayScore) > (e2.homeScore + e2.awayScore);
    });

    std::list<std::string> result;
    for (auto& e : entries) {
        result.emplace_back(std::format("{} {} - {} {}", e.homeTeam, e.homeScore, e.awayTeam, e.awayScore));
    }

    return result;
}

void ScoreBoard::startNewGame(std::string homeTeam, std::string awayTeam)
{
    const auto& storedEntries = store.getAll();
    
    if (std::find_if(storedEntries.begin(), storedEntries.end(), 
        [&](const auto& e) { return e.homeTeam == homeTeam && e.awayTeam == awayTeam; }
    ) != storedEntries.end()) 
    {
        // game already exists
        return;
    }

    store.createOrUpdate(homeTeam, awayTeam, 0u, 0u);
}

void ScoreBoard::updateScore(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore)
{
    const auto& storedEntries = store.getAll();
    
    if (std::find_if(storedEntries.begin(), storedEntries.end(), 
        [&](const auto& e) { return e.homeTeam == homeTeam && e.awayTeam == awayTeam; }
    ) != storedEntries.end()) 
    {
        store.createOrUpdate(homeTeam, awayTeam, homeScore, awayScore);
        return;
    }

    // no game found
}

void ScoreBoard::finishGame(std::string homeTeam, std::string awayTeam)
{
    const auto& storedEntries = store.getAll();
    
    if (std::find_if(storedEntries.begin(), storedEntries.end(), 
        [&](const auto& e) { return e.homeTeam == homeTeam && e.awayTeam == awayTeam; }
    ) != storedEntries.end()) 
    {
        store.remove(homeTeam, awayTeam);
        return;
    }

    // no game found
}
