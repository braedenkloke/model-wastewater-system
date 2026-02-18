#ifndef TAMPER_ATTACKER_HPP
#define TAMPER_ATTACKER_HPP

#include "cadmium/modeling/devs/atomic.hpp"
#include "../constants.hpp"

using namespace cadmium;

struct TamperAttackerState {
    enum Phase phase;
    double idleTime;
    double attackTime;
    double interceptedMessage;
    double bias;

    explicit TamperAttackerState(): phase(kIdle), idleTime(kInfinity), attackTime(0) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const TamperAttackerState& state) {
    return out;
}
#endif

class TamperAttacker : public Atomic<TamperAttackerState> {
public:
    Port<double> interceptIn, tamperOut;

    TamperAttacker(const std::string id, double bias = 0.0): 
                  Atomic<TamperAttackerState>(id, TamperAttackerState()) {
        interceptIn = addInPort<double>("interceptIn");
        tamperOut = addOutPort<double>("tamperOut");

        state.bias = bias;
    }

    void internalTransition(TamperAttackerState& state) const override {
        if (state.phase == kIdle) {
            state.phase = kAttacking;
        } else {
            state.phase = kIdle;
        }
    }

	void externalTransition(TamperAttackerState& state, double e) const override {
        if (state.phase == kIdle) {
            state.interceptedMessage = interceptIn->getBag().back();
            state.phase = kAttacking;
        }
    }
    
    void output(const TamperAttackerState& state) const override {
        if (state.phase == kAttacking) {
            tamperOut->addMessage(state.interceptedMessage - state.bias);
        } 
    }

    [[nodiscard]] double timeAdvance(const TamperAttackerState& state) const override {     
        if (state.phase == kIdle) {
            return state.idleTime;
        } else {
            return state.attackTime;
        }
    }
};

#endif // TAMPER_ATTACKER_HPP
