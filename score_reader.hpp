#include <list>
#include <string>

class ScoreReader
{
    virtual std::list<std::string> getGamesSummary() const = 0
    virtual ~ScoreReader() {}
}