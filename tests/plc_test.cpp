#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"

#include "../include/atomic_models/plc.hpp"

using namespace cadmium;

struct PLCTest: public Coupled {

  PLCTest(const std::string& id): Coupled(id) {
        auto plc = addComponent<PLC>("PLC");
        auto testFile = addComponent<lib::IEStream<double>>("Test File", "input_data/plc_test.csv");

        addCoupling(testFile->out, plc->analysisIn);
  }

};

int main(int argc, char* argv[]) {
    auto model = std::make_shared<PLCTest>("PLC Test");
    auto rootCoordinator = cadmium::RootCoordinator(model);

    rootCoordinator.setLogger<STDOUTLogger>(",");
    rootCoordinator.start();
    rootCoordinator.simulate(10000.0);
    rootCoordinator.stop();	
}
