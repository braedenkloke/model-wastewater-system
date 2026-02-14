#ifndef TOP_HPP
#define TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"

#include "../atomic_models/chemical_feed_pump.hpp"
#include "../atomic_models/wastewater.hpp"
#include "../atomic_models/chemical_analyzer.hpp"
#include "vulnerable_plc.hpp"

using namespace cadmium;

struct TopCoupled : public Coupled {

    TopCoupled(const std::string& id): Coupled(id) {

        auto pump = addComponent<ChemicalFeedPump>("ChemicalFeedPump");
        auto wastewater = addComponent<Wastewater>("Wastewater");
        auto analyzer = addComponent<ChemicalAnalyzer>("ChemicalAnalyzer");
        auto plc = addComponent<VulnerablePLCCoupled>("VulnerablePLC");

        addCoupling(pump->chemicalOut, wastewater->chemicalIn);
        addCoupling(wastewater->sampleOut, analyzer->sampleIn);
        addCoupling(analyzer->analysisOut, plc->analysisIn);
        addCoupling(plc->commandOut, pump->commandIn);
    }
};
#endif // TOP_HPP
