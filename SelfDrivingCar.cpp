#include "../include/SelfDrivingCar.h"

#include <utility>

SelfDrivingCar::SelfDrivingCar(std::string algorithmVersion, std::string company)
    : Driver("Self Driving Car - " + company + " (" + algorithmVersion + ")", company),
    m_algorithmVersion(std::move(algorithmVersion)),
    m_company(std::move(company))
{
}

std::string const& SelfDrivingCar::getAlgorithmVersion() const noexcept
{
    return m_algorithmVersion;
}

std::string const& SelfDrivingCar::getCompany() const noexcept
{
    return m_company;
}

void SelfDrivingCar::setAlgorithmVersion(std::string algorithmVersion)
{
    m_algorithmVersion = std::move(algorithmVersion);
}

std::string SelfDrivingCar::getDisplayName() const
{
    return "Self Driving Car - " + m_company + " (" + m_algorithmVersion + ")";
}