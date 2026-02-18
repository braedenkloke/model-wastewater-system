#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"

#include "../include/atomic_models/tamper_attacker.hpp"

using namespace cadmium;

struct TamperAttackerTest: public Coupled {

  TamperAttackerTest(const std::string& id): Coupled(id) {
        auto tamperAttacker = addComponent<TamperAttacker>("Tamper Attacker", 1.0);
        auto testFile = addComponent<lib::IEStream<double>>("Test File", "input_data/tamper_attacker_test.csv");

        addCoupling(testFile->out, tamperAttacker->interceptIn);
  }

};

int main(int argc, char* argv[]) {
    auto model = std::make_shared<TamperAttackerTest>("Tamper Attacker Test");
    auto rootCoordinator = cadmium::RootCoordinator(model);

    rootCoordinator.setLogger<STDOUTLogger>(",");
    rootCoordinator.start();
    rootCoordinator.simulate(10000.0);
    rootCoordinator.stop();	
}
