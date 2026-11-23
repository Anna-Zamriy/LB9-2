#include "../include/LeaderBoard.h"

#include <algorithm>
#include <utility>

Leaderboard::Leaderboard(std::vector<Race> races)
    : m_races(std::move(races))
{
}

std::map<std::string, int> Leaderboard::driverResults() const
{
    std::map<std::string, int> results;
    for (Race const& race : m_races)
    {
        for (auto const& competitor : race.getResults())
        {
            if (!competitor)
            {
                continue;
            }
            std::string const driverName = race.getDriverName(*competitor);
            results[driverName] += race.getPoints(*competitor);
        }
    }
    return results;
}

std::vector<CompetitorStanding> Leaderboard::standings(IRankingStrategy const& strategy) const
{
    std::map<std::string, CompetitorStanding> table;

    for (Race const& race : m_races)
    {
        for (auto const& competitor : race.getResults())
        {
            if (!competitor)
            {
                continue;
            }
            std::string const name = race.getDriverName(*competitor);
            auto& entry = table[name];
            entry.name = name;
            entry.totalPoints += race.getPoints(*competitor);

            int const pos = race.position(*competitor);
            if (pos >= 0 && pos < entry.bestPosition)
            {
                entry.bestPosition = pos;
            }
        }
    }

    std::vector<CompetitorStanding> ordered;
    ordered.reserve(table.size());
    for (auto const& [_, entry] : table)
    {
        ordered.push_back(entry);
    }

    std::sort(ordered.begin(), ordered.end(),
        [&strategy](CompetitorStanding const& a, CompetitorStanding const& b) {
            return strategy.comesBefore(a, b);
        });

    return ordered;
}

std::list<std::string> Leaderboard::driverRankings() const
{
    DefaultRankingStrategy defaultStrategy;
    return driverRankings(defaultStrategy);
}

std::list<std::string> Leaderboard::driverRankings(IRankingStrategy const& strategy) const
{
    auto const ordered = standings(strategy);
    std::list<std::string> names;
    for (auto const& entry : ordered)
    {
        names.push_back(entry.name);
    }
    return names;
}