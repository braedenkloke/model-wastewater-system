#ifndef VULNERABLE_PLC_HPP
#define VULNERABLE_PLC_HPP

#include "cadmium/modeling/devs/coupled.hpp"

#include "../atomic_models/plc.hpp"

using namespace cadmium;

struct VulnerablePLCCoupled : public Coupled {

    Port<double> analysisIn;
    Port<int> commandOut;

    VulnerablePLCCoupled(const std::string& id): Coupled(id) {
        analysisIn = addInPort<double>("analysisIn");
        commandOut = addOutPort<int>("commandOut");

        auto plc = addComponent<PLC>("PLC");
        
        addCoupling(analysisIn, plc->analysisIn);
        addCoupling(plc->commandOut, commandOut);
    }
};
#endif // VULNERABLE_PLC_HPP
