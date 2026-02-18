#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int kInfinity = 2147483647; // Maximum value for an integer, i.e., infinity

enum Phase {
    kIdle,
    kBusy,
    kAnalyzing,
    kOn,
    kOff,
    kPreparing,
    kAttacking
};

#endif // CONSTANTS_HPP
