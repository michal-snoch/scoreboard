#include <score_board.hpp>
#include <exception>

ScoreBoard::ScoreBoard(Store& store) {}

std::list<std::string> ScoreBoard::getGamesSummary() const
{
    throw std::logic_error("Not implemented");
}