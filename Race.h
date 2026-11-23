#pragma once

#include "Driver.h"

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Race
{
    static constexpr std::array<int, 3> POINTS = { 25, 18, 15 };

    std::string m_name;
    std::vector<std::shared_ptr<Driver const>> m_results;
    std::unordered_map<std::string, std::string> m_driverNames;

public:
    Race(std::string name, std::vector<std::shared_ptr<Driver const>> drivers);

    int position(Driver const& driver) const noexcept;
    int getPoints(Driver const& driver) const noexcept;
    std::vector<std::shared_ptr<Driver const>> const& getResults() const noexcept;
    std::string getDriverName(Driver const& driver) const;
    std::string const& toString() const noexcept;
};