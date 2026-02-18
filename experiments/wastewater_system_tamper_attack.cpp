#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"

#include "../include/coupled_models/top.hpp"
#include "../include/constants.hpp"

using namespace cadmium;

int main(int argc, char* argv[]) {
    double spoofAttackerIdleTime = kInfinity;
    double tamperBias = 0.6;

    auto model = std::make_shared<TopCoupled>("Wastewater System Under Tamper Attack", spoofAttackerIdleTime, tamperBias);
    auto rootCoordinator = cadmium::RootCoordinator(model);

    rootCoordinator.setLogger<STDOUTLogger>(",");
    rootCoordinator.start();
    rootCoordinator.simulate(100.0);
    rootCoordinator.stop();	
}
