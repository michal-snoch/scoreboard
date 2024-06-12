#pragma once

#include "score_reader.hpp"
#include <store.hpp>

class ScoreBoard : public ScoreReader
{
public:
    ScoreBoard(Store& store);
    virtual std::list<std::string> getGamesSummary() const;
    virtual ~ScoreBoard() = default;

private:
    Store& store;
};
