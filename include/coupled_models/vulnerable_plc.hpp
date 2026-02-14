#ifndef VULNERABLE_PLC_HPP
#define VULNERABLE_PLC_HPP

#include "cadmium/modeling/devs/coupled.hpp"

using namespace cadmium;

struct VulnerablePLCCoupled : public Coupled {

    VulnerablePLCCoupled(const std::string& id): Coupled(id) {
    }
};
#endif // VULNERABLE_PLC_HPP
