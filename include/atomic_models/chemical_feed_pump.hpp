#ifndef CHEMICAL_FEED_PUMP_HPP
#define CHEMICAL_FEED_PUMP_HPP

#include "cadmium/modeling/devs/atomic.hpp"
#include "../constants.hpp"

using namespace cadmium;

struct ChemicalFeedPumpState {
    enum Phase phase;
    double chemicalFeedRate;

    explicit ChemicalFeedPumpState(): phase(kOff), chemicalFeedRate(0.1) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const ChemicalFeedPumpState& state) {
    return out;
}
#endif

class ChemicalFeedPump : public Atomic<ChemicalFeedPumpState> {
public:
    Port<int> commandIn;
    Port<double> chemicalOut;

    ChemicalFeedPump(const std::string id): Atomic<ChemicalFeedPumpState>(id, ChemicalFeedPumpState()) {
        commandIn = addInPort<int>("commandIn");
        chemicalOut = addOutPort<double>("chemicalOut");
    }

    void internalTransition(ChemicalFeedPumpState& state) const override {
        // Do nothing
    }

	void externalTransition(ChemicalFeedPumpState& state, double e) const override {
        int command = commandIn->getBag().back();
        if (command == 1) {
            state.phase = kOn;
        } else {
            state.phase = kOff;
        }
    }
    
    void output(const ChemicalFeedPumpState& state) const override {
        if (state.phase == kOn) {
            chemicalOut->addMessage(state.chemicalFeedRate);
        }
    }

    [[nodiscard]] double timeAdvance(const ChemicalFeedPumpState& state) const override {     
        if (state.phase == kOn) {
            return 1;
        } else {
            return kInfinity;
        }
    }
};

#endif // CHEMICAL_FEED_PUMP_HPP
