
#include <iostream>
#include <vector>
#include "MonteCarlopricer.h"

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        std::cerr << "Usage: ./main asset strike rfRate vol years steps sims\n";
        return 1;
    }

    float asset = std::stof(argv[1]);
    float strike = std::stof(argv[2]);
    float rfRate = std::stof(argv[3]);
    float volatility = std::stof(argv[4]);
    float years = std::stof(argv[5]);
    long steps = std::stol(argv[6]);
    long simulations = std::stol(argv[7]);

    MonteCarlopricer bsm(asset, strike, rfRate, volatility, years, steps, simulations);

    bsm.simulate();
    bsm.calcGreeks();

    std::cout << "\nCall Option Price: " << bsm.getCallPrice() << '\n';
    std::cout << "Put Option Price:  " << bsm.getPutPrice() << '\n';
    std::cout << "Call Delta:  " << bsm.getCallDelta() << '\n';
    std::cout << "Put Delta:  " << bsm.getPutDelta() << '\n';
    std::cout << "Vega:  " << bsm.getVega() << '\n';

    return 0;
}
