#pragma once

#include "IRankingStrategy.h"
#include "Race.h"

#include <list>
#include <map>
#include <string>
#include <vector>

class Leaderboard
{
    std::vector<Race> m_races;

public:
    explicit Leaderboard(std::vector<Race> races);

    std::map<std::string, int> driverResults() const;
    std::vector<CompetitorStanding> standings(IRankingStrategy const& strategy) const;
    std::list<std::string> driverRankings() const;
    std::list<std::string> driverRankings(IRankingStrategy const& strategy) const;
};