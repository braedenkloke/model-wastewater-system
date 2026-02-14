#ifndef PLC_HPP
#define PLC_HPP

#include "cadmium/modeling/devs/atomic.hpp"

#include "../constants.hpp"

using namespace cadmium;

enum PLCPhase {
    kIdle,
    kBusy
};

struct PLCState {
    enum PLCPhase phase;
    double analysis;
    double safetyLimit;
    double tolerance;

    explicit PLCState(): phase(kIdle), analysis(0), safetyLimit(10), tolerance(1) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const PLCState& state) {
    return out;
}
#endif

class PLC : public Atomic<PLCState> {
public:
    Port<double> analysisIn;
    Port<int> commandOut;

    PLC(const std::string id): Atomic<PLCState>(id, PLCState()) {
        analysisIn = addInPort<double>("analysisIn");
        commandOut = addOutPort<int>("commandOut");
    }

    void internalTransition(PLCState& state) const override {
        if (state.phase = kBusy) {
            state.phase = kIdle;
        }
    }

	void externalTransition(PLCState& state, double e) const override {
        if (state.phase == kIdle) {
            state.analysis = analysisIn->getBag().back();
            state.phase = kBusy;
        }
    }
    
    void output(const PLCState& state) const override {
        if (state.analysis > state.safetyLimit - state.tolerance) {
            commandOut->addMessage(1); // Pump on
        } else {
            commandOut->addMessage(0); // Pump off
        }
    }

    [[nodiscard]] double timeAdvance(const PLCState& state) const override {     
        if (state.phase == kBusy) {
            return 0;
        } else {
            return kInfinity;
        }
    }
};

#endif // PLC_HPP
