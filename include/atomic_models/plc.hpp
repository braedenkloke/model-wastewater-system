#ifndef PLC_HPP
#define PLC_HPP

#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct PLCState {
    explicit PLCState() {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const PLCState& state) {
    return out;
}
#endif

// Atomic DEVS model of a ...
class PLC : public Atomic<PLCState> {
public:
    Port<double> in, out;

    // ARGUMENTS
    // id - Model name.
    PLC(const std::string id): 
    }

    void internalTransition(PLCState& state) const override {
    }

	void externalTransition(PLCState& state, double e) const override {
    }
    
    void output(const PLCState& state) const override {
    }

    [[nodiscard]] double timeAdvance(const PLCState& state) const override {     
    }
};

#endif // PLC_HPP
