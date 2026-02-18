#ifndef SPOOF_ATTACKER_HPP
#define SPOOF_ATTACKER_HPP

#include "cadmium/modeling/devs/atomic.hpp"
#include "../constants.hpp"

using namespace cadmium;

struct SpoofAttackerState {
    enum Phase phase;
    double idleTime;
    double prepTime;
    double attackTime;

    explicit SpoofAttackerState(): phase(kIdle), attackTime(0) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const SpoofAttackerState& state) {
    return out;
}
#endif

class SpoofAttacker : public Atomic<SpoofAttackerState> {
public:
    Port<double> spoofOut;

    SpoofAttacker(const std::string id, double idleTime = kInfinity, double prepTime = 1.0): 
                  Atomic<SpoofAttackerState>(id, SpoofAttackerState()) {
        spoofOut = addOutPort<double>("spoofOut");

        state.idleTime = idleTime;
        state.prepTime = prepTime; 
    }

    void internalTransition(SpoofAttackerState& state) const override {
        if (state.phase == kAttacking) {
            state.phase = kIdle;
        } else if (state.phase == kIdle) {
            state.phase = kPreparing;
        } else if (state.phase == kPreparing) {
            state.phase = kAttacking;
        }
    }

	void externalTransition(SpoofAttackerState& state, double e) const override {
        // Do nothing
    }
    
    void output(const SpoofAttackerState& state) const override {
        if (state.phase == kAttacking) {
            spoofOut->addMessage(8.0); // Value less than PLC's ( safety limit - tolerance )
        }
    }

    [[nodiscard]] double timeAdvance(const SpoofAttackerState& state) const override {     
        if (state.phase == kIdle) {
            return state.idleTime;
        } else if (state.phase == kPreparing) {
            return state.prepTime;
        } else {
            return state.attackTime;
        }
    }
};

#endif // SPOOF_ATTACKER_HPP
