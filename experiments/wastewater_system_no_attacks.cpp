#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"

#include "../include/coupled_models/top.hpp"

using namespace cadmium;

int main(int argc, char* argv[]) {
    auto model = std::make_shared<TopCoupled>("Wastewater System No Attacks");
    auto rootCoordinator = cadmium::RootCoordinator(model);

    rootCoordinator.setLogger<STDOUTLogger>(",");
    rootCoordinator.start();
    rootCoordinator.simulate(100.0);
    rootCoordinator.stop();	
}
