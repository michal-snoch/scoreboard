#include <memory_store.hpp>
#include <exception>

void MemoryStore::createOrUpdate(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore)
{
    entries.insert({homeTeam, awayTeam, homeScore, awayScore });
}
    
void MemoryStore::remove(std::string homeTeam, std::string awayTeam)
{
    auto it = std::find_if(entries.begin(), entries.end(), [=](const auto& e){
        return e.homeTeam == homeTeam && e.awayTeam == awayTeam;
    });

    if (it != entries.end()) entries.erase(it);
}
    
const std::set<Store::Entry>& MemoryStore::getAll() const
{
    return entries;
}