#include "../include/Driver.h"

#include <utility>

Driver::Driver(std::string name, std::string country)
    : m_name(std::move(name)), m_country(std::move(country))
{
}

std::string const& Driver::getName() const noexcept
{
    return m_name;
}

std::string const& Driver::getCountry() const noexcept
{
    return m_country;
}

std::string Driver::getDisplayName() const
{
    return m_name;
}

bool Driver::operator==(Driver const& other) const noexcept
{
    return m_name == other.m_name;
}

bool Driver::operator!=(Driver const& other) const noexcept
{
    return !(*this == other);
}