#pragma once

#include <string>

class Driver
{
    std::string m_name;
    std::string m_country;

public:
    Driver(std::string name, std::string country);
    virtual ~Driver() = default;

    std::string const& getName() const noexcept;
    std::string const& getCountry() const noexcept;
    virtual std::string getDisplayName() const;

    bool operator==(Driver const& other) const noexcept;
    bool operator!=(Driver const& other) const noexcept;
};