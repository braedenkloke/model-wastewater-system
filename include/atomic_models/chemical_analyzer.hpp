#ifndef CHEMICAL_ANALYZER_HPP
#define CHEMICAL_ANALYZER_HPP

#include "cadmium/modeling/devs/atomic.hpp"
#include "../constants.hpp"

using namespace cadmium;

enum ChemicalAnalyzerPhase {
    kIdle,
    kAnalyzing
}

struct ChemicalAnalyzerState {
    double sigma;
    enum ChemicalAnalyzerPhase phase;
    double analysisTime;
    double sample;

    explicit ChemicalAnalyzerState(): sigma(kInfinity), phase(kIdle), analysisTime(2), sample(0) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const ChemicalAnalyzerState& state) {
    return out;
}
#endif

class ChemicalAnalyzer : public Atomic<ChemicalAnalyzerState> {
public:
    Port<double> sampleIn, analysisOut;

    ChemicalAnalyzer(const std::string id): 
        sampleIn = addInPort<double>("sampleIn");
        analysisOut = addOutPort<double>("analysisOut");
    }

    void internalTransition(ChemicalAnalyzerState& state) const override {
        if (state.phase = kAnalyzing) {
            state.phase = kIdle;
            state.sigma = kInfinity;
        } else {

        }
    }

	void externalTransition(ChemicalAnalyzerState& state, double e) const override {
        if (state.phase == kIdle) {
            state.phase = kAnalyzing;
            state.sample = sampleIn->getBag().back();
            state.sigma = state.analysisTime;
        } else {
            state.sigma -= e;

        }
    }
    
    void output(const ChemicalAnalyzerState& state) const override {
        if (state.phase == kAnalyzing) {
            analysisOut->addMessage(state.sample);
        }
    }

    [[nodiscard]] double timeAdvance(const ChemicalAnalyzerState& state) const override {     
        return state.sigma;
        if (state.phase == kAnalyzing) {
            return state.analysisTime;
        } else {
            return kInfinity;
        }
    }
};

#endif // CHEMICAL_ANALYZER_HPP
