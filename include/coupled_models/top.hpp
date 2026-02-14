#ifndef TOP_HPP
#define TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"

using namespace cadmium;

struct TopCoupled : public Coupled {

    TopCoupled(const std::string& id): Coupled(id) {
    }
};
#endif // TOP_HPP
