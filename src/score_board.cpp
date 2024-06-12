#include <score_board.hpp>
#include <algorithm>
#include <format>

ScoreBoard::ScoreBoard(Store& store) : store(store)
{
}

std::list<std::string> ScoreBoard::getGamesSummary() const
{
    const auto& storedEntries = store.getAll();

    std::vector<Store::Entry> entries(storedEntries.begin(), storedEntries.end());
    std::stable_sort(entries.begin(), entries.end(), [](const auto& e1, const auto& e2) {
        return (e1.homeScore + e1.awayScore) > (e2.homeScore + e2.awayScore);
    });

    std::list<std::string> result;
    for (auto& e : entries) {
        result.emplace_back(std::format("{} {} - {} {}", e.homeTeam, e.homeScore, e.awayTeam, e.awayScore));
    }

    return result;
}