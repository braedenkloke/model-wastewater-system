#ifndef WASTEWATER_HPP
#define WASTEWATER_HPP

#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct WastewaterState {
    double sigma;
    double pH_Level;
    double pH_IncreaseRate;

    explicit WastewaterState(): sigma(1), pH_Level(9), pH_IncreaseRate(0.1) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const WastewaterState& state) {
    return out;
}
#endif

class Wastewater : public Atomic<WastewaterState> {
public:
    Port<double> chemicalIn, sampleOut;

    Wastewater(const std::string id): Atomic<WastewaterState>(id, WastewaterState()) {
        chemicalIn = addInPort<double>("chemicalIn");
        sampleOut = addOutPort<double>("sampleOut");
    }

    void internalTransition(WastewaterState& state) const override {
        state.pH_Level += state.pH_IncreaseRate;
    }

	void externalTransition(WastewaterState& state, double e) const override {
        state.pH_Level -= chemicalIn->getBag().back();
        state.sigma -= e;
    }
    
    void output(const WastewaterState& state) const override {
        sampleOut->addMessage(state.pH_Level);
    }

    [[nodiscard]] double timeAdvance(const WastewaterState& state) const override {     
        return state.sigma;
    }
};

#endif // WASTEWATER_HPP
