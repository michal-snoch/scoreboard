#include <memory_store.hpp>
#include <exception>

void MemoryStore::createOrUpdate(std::string homeTeam, std::string awayTeam, uint16_t homeScore, uint16_t awayScore)
{
    throw std::logic_error("Not implemented");
}
    
void MemoryStore::remove(std::string homeTeam, std::string awayTeam)
{
    throw std::logic_error("Not implemented");
}
    
std::set<Store::Entry> MemoryStore::getAll() const
{
    throw std::logic_error("Not implemented");
}