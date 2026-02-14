#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct TemplateState {
    explicit TemplateState() {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const TemplateState& state) {
    return out;
}
#endif

// Atomic DEVS model of a ...
class TEMPLATE : public Atomic<TemplateState> {
public:
    Port<double> in, out;

    // ARGUMENTS
    // id - Model name.
    Template(const std::string id): 
    }

    void internalTransition(TemplateState& state) const override {
    }

	void externalTransition(TemplateState& state, double e) const override {
    }
    
    void output(const TemplateState& state) const override {
    }

    [[nodiscard]] double timeAdvance(const TemplateState& state) const override {     
    }
};

#endif // TEMPLATE_HPP
