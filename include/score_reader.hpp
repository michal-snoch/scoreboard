#pragma once

#include <list>
#include <string>

struct ScoreReader
{
    virtual std::list<std::string> getGamesSummary() const = 0;
    virtual ~ScoreReader() {}
};
