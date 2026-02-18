#ifndef VULNERABLE_PLC_HPP
#define VULNERABLE_PLC_HPP

#include "cadmium/modeling/devs/coupled.hpp"

#include "../atomic_models/plc.hpp"
#include "../atomic_models/spoof_attacker.hpp"
#include "../atomic_models/tamper_attacker.hpp"
#include "../constants.hpp"


using namespace cadmium;

struct VulnerablePLCCoupled : public Coupled {

    Port<double> analysisIn;
    Port<int> commandOut;

    VulnerablePLCCoupled(const std::string& id, double spoofAttackerIdleTime = kInfinity, 
                         double tamperBias = 0.0): Coupled(id) {
        analysisIn = addInPort<double>("analysisIn");
        commandOut = addOutPort<int>("commandOut");

        auto plc = addComponent<PLC>("PLC");
        auto spoofAttacker = addComponent<SpoofAttacker>("Spoof Attacker", spoofAttackerIdleTime);
        auto tamperAttacker = addComponent<TamperAttacker>("Tamper Attacker", tamperBias);
        
        addCoupling(analysisIn, tamperAttacker->interceptIn);
        addCoupling(tamperAttacker->tamperOut, plc->analysisIn);
        addCoupling(spoofAttacker->spoofOut, plc->analysisIn);
        addCoupling(plc->commandOut, commandOut);
    }
};
#endif // VULNERABLE_PLC_HPP
