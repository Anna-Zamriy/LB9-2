#pragma once

#include "Driver.h"

#include <string>

class SelfDrivingCar : public Driver
{
    std::string m_algorithmVersion;
    std::string m_company;

public:
    SelfDrivingCar(std::string algorithmVersion, std::string company);

    std::string const& getAlgorithmVersion() const noexcept;
    std::string const& getCompany() const noexcept;
    void setAlgorithmVersion(std::string algorithmVersion);

    std::string getDisplayName() const override;
};