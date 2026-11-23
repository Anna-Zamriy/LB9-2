#include "../include/Race.h"

#include <limits>
#include <utility>

Race::Race(std::string name, std::vector<std::shared_ptr<Driver const>> drivers)
    : m_name(std::move(name)), m_results(std::move(drivers))
{
    for (auto const& driverPtr : m_results)
    {
        if (driverPtr)
        {
            m_driverNames[driverPtr->getName()] = driverPtr->getDisplayName();
        }
    }
}

int Race::position(Driver const& driver) const noexcept
{
    int index = 0;
    for (auto const& entry : m_results)
    {
        if (entry && *entry == driver)
        {
            return index;
        }
        ++index;
    }
    return -1;
}

int Race::getPoints(Driver const& driver) const noexcept
{
    int const pos = position(driver);
    if (pos >= 0 && static_cast<std::size_t>(pos) < POINTS.size())
    {
        return POINTS[static_cast<std::size_t>(pos)];
    }
    return 0;
}

std::vector<std::shared_ptr<Driver const>> const& Race::getResults() const noexcept
{
    return m_results;
}

std::string Race::getDriverName(Driver const& driver) const
{
    auto const it = m_driverNames.find(driver.getName());
    if (it != m_driverNames.end())
    {
        return it->second;
    }
    return driver.getDisplayName();
}

std::string const& Race::toString() const noexcept
{
    return m_name;
}