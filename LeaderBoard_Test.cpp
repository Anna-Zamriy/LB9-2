#include "../include/Driver.h"
#include "../include/IRankingStrategy.h"
#include "../include/LeaderBoard.h"
#include "../include/Race.h"
#include "../include/SelfDrivingCar.h"

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace
{
    void printStandings(std::string const& title, std::vector<CompetitorStanding> const& items)
    {
        std::cout << "\n=== " << title << " ===\n";
        std::size_t rank = 1;
        for (auto const& item : items)
        {
            std::cout << rank++ << ". " << item.name
                << " | points: " << item.totalPoints
                << " | bestPos: " << item.bestPosition << "\n";
        }
    }
} // namespace

int main()
{
    auto nico = std::make_shared<Driver>("Nico Rosberg", "DE");
    auto lewis = std::make_shared<Driver>("Lewis Hamilton", "UK");
    auto sebastian = std::make_shared<Driver>("Sebastian Vettel", "DE");
    auto car = std::make_shared<SelfDrivingCar>("1.3", "XYZ");

    Race race1("Australian Grand Prix", { nico, lewis, sebastian });
    Race race2("Malaysian Grand Prix", { lewis, car, nico });

    Leaderboard board({ race1, race2 });
    std::map<std::string, int> const results = board.driverResults();

    std::cout << "=== Driver Results ===\n";
    for (auto const& [name, pts] : results)
    {
        std::cout << "  " << name << ": " << pts << "\n";
    }

    assert(results.at("Nico Rosberg") == 40);
    assert(results.at("Lewis Hamilton") == 43);
    assert(results.at("Sebastian Vettel") == 15);
    assert(results.at("Self Driving Car - XYZ (1.3)") == 18);

    std::list<std::string> const ranking = board.driverRankings();
    assert(!ranking.empty());
    assert(ranking.front() == "Lewis Hamilton");

    // Сценарій тай-брейку: Driver A і Driver B мають по 0 балів,
    // але Driver A має кращу позицію (pos = 3, тобто 4-те місце у Race 1),
    // тоді як найкраща позиція Driver B — pos = 4 (5-те місце у Race 1 та 4-те у Race 2).
    // Для наочності дамо Driver B у Race 2 позицію pos = 4, а Driver A — pos = 5:
    auto dA = std::make_shared<Driver>("Driver A", "UA");
    auto dB = std::make_shared<Driver>("Driver B", "UA");
    auto filler = std::make_shared<Driver>("Filler Driver", "UA");

    Race r1("Race 1", { nico, lewis, sebastian, dA, dB });         // dA: pos 3, dB: pos 4
    Race r2("Race 2", { lewis, nico, sebastian, filler, dB, dA }); // dB: pos 4, dA: pos 5

    Leaderboard tieBoard({ r1, r2 });

    DefaultRankingStrategy defaultStrategy;
    BestPositionTieBreakStrategy bestPosStrategy;

    auto const defaultStandings = tieBoard.standings(defaultStrategy);
    auto const tieBreakStandings = tieBoard.standings(bestPosStrategy);

    printStandings("DefaultRankingStrategy (points -> name)", defaultStandings);
    printStandings("BestPositionTieBreakStrategy (points -> bestPosition -> name)", tieBreakStandings);

    // За стандартною стратегією при 0 балів перемагає алфавітний порядок ("Driver A" перед "Driver B")
    assert(tieBreakStandings.size() >= 2);

    // Перевіримо окремий кейс, де за алфавітом "Zed Driver" мав би бути після "Amy Driver",
    // але "Zed Driver" має кращу позицію (pos 3 проти pos 4) за однакових 0 балів.
    auto amy = std::make_shared<Driver>("Amy Driver", "UA");
    auto zed = std::make_shared<Driver>("Zed Driver", "UA");

    Race t1("Tie 1", { nico, lewis, sebastian, zed, amy });         // zed: pos 3, amy: pos 4
    Race t2("Tie 2", { lewis, nico, sebastian, filler, amy, zed }); // amy: pos 4, zed: pos 5

    Leaderboard tieCaseBoard({ t1, t2 });
    auto const tieDefaultOrder = tieCaseBoard.driverRankings(defaultStrategy);
    auto const tieBestPosOrder = tieCaseBoard.driverRankings(bestPosStrategy);

    std::cout << "\nTie-break check (Amy vs Zed, both 0 pts; Zed bestPos=3, Amy bestPos=4):\n";
    std::cout << "  Default strategy first of two: ";
    for (auto const& n : tieDefaultOrder)
    {
        if (n == "Amy Driver" || n == "Zed Driver")
        {
            std::cout << n << " ";
        }
    }
    std::cout << "\n";

    std::cout << "  BestPosition tie-break first of two: ";
    for (auto const& n : tieBestPosOrder)
    {
        if (n == "Amy Driver" || n == "Zed Driver")
        {
            std::cout << n << " ";
        }
    }
    std::cout << "\n";

    // Знайдемо позиції Amy та Zed у списку після BestPositionTieBreakStrategy
    int amyIdx = -1;
    int zedIdx = -1;
    int idx = 0;
    for (auto const& n : tieBestPosOrder)
    {
        if (n == "Amy Driver") amyIdx = idx;
        if (n == "Zed Driver") zedIdx = idx;
        ++idx;
    }
    assert(amyIdx != -1 && zedIdx != -1);
    assert(zedIdx < amyIdx);

    std::cout << "\nAll LeaderBoard tests passed!\n";
    return 0;
}