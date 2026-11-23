#pragma once

#include <limits>
#include <string>

struct CompetitorStanding
{
    std::string name;
    int totalPoints = 0;
    int bestPosition = std::numeric_limits<int>::max();
};

class IRankingStrategy
{
public:
    virtual ~IRankingStrategy() = default;
    virtual bool comesBefore(CompetitorStanding const& a, CompetitorStanding const& b) const = 0;
};

class DefaultRankingStrategy final : public IRankingStrategy
{
public:
    bool comesBefore(CompetitorStanding const& a, CompetitorStanding const& b) const override
    {
        if (a.totalPoints != b.totalPoints)
        {
            return a.totalPoints > b.totalPoints;
        }
        return a.name < b.name;
    }
};

class BestPositionTieBreakStrategy final : public IRankingStrategy
{
public:
    bool comesBefore(CompetitorStanding const& a, CompetitorStanding const& b) const override
    {
        if (a.totalPoints != b.totalPoints)
        {
            return a.totalPoints > b.totalPoints;
        }
        if (a.bestPosition != b.bestPosition)
        {
            return a.bestPosition < b.bestPosition;
        }
        return a.name < b.name;
    }
};