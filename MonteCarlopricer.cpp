
#include "MonteCarlopricer.h"
#include <cmath>
#include <iostream>
using namespace std;

//member initializer list
MonteCarlopricer::MonteCarlopricer(float asset, float strike, float rfRate, float vol, float years,
         long steps, long sims)
    : asset(asset), strike(strike), rfRate(rfRate), volatility(vol),
      years(years), steps(steps), simulations(sims),
      gen(std::random_device{}()), dist(0.0, 1.0) {}

//RNG
double MonteCarlopricer::getNormalSample()
{
    return dist(gen);
}

//For loop to perform Monte Carlo simulations
void MonteCarlopricer::simulate()
{
    double callSum = 0.0;
    double putSum = 0.0;
    double dt = years / static_cast<double>(steps);
    double sqrtDt = std::sqrt(dt);

    for (long i = 0; i < simulations; ++i)
    {
        double price = asset;

        for (long j = 0; j < steps; ++j)
        {
            double Z = getNormalSample();
            price *= exp(((rfRate - 0.5 * (volatility * volatility)) * dt) + volatility * sqrtDt * Z);
        }

        callSum += std::max(price - strike, 0.0);
        putSum += std::max(strike - price, 0.0);

        if ((i + 1) % 10000 == 0)
        {
            std::cout << "." << std::flush;
            if ((i + 1) % 100000 == 0)
            {
                std::cout << (i + 1) / 1000 << "k" << std::flush;
            }
        }
    }

    callPrice = (callSum / simulations) * exp(-rfRate * years);
    putPrice = (putSum / simulations) * exp(-rfRate * years);
}

//function to perform simulation with custom inputs for greeks
void MonteCarlopricer::simulateCustom(double customAsset, double customVol, double &finalPrice)
{
    double callSum = 0.0;
    double putSum = 0.0;
    double dt = years / static_cast<double>(steps);
    double sqrtDt = std::sqrt(dt);

    for (long i = 0; i < simulations; ++i)
    {
        double price = customAsset;

        for (long j = 0; j < steps; ++j)
        {
            double Z = getNormalSample();
            price *= exp(((rfRate - 0.5 * (volatility * volatility)) * dt) + volatility * sqrtDt * Z);
        }

        callSum += std::max(price - strike, 0.0);
        putSum += std::max(strike - price, 0.0);
        if ((i + 1) % 10000 == 0)
        {
            std::cout << "." << std::flush;
            if ((i + 1) % 100000 == 0)
            {
                std::cout << (i + 1) / 1000 << "k" << std::flush;
            }
        }
    }
    finalPrice = (callSum / simulations) * exp(-rfRate * years);
}

void MonteCarlopricer::calcGreeks()
{
    double deltaBump = asset * 0.01;
    double plusPrice = 0.0;
    double minusPrice = 0.0;
    std::cout << "\nCalculating delta+";
    simulateCustom(asset + deltaBump, volatility, plusPrice);
    std::cout << "\nCalculating delta-";
    simulateCustom(asset - deltaBump, volatility, minusPrice);
    delta = (plusPrice - minusPrice) / (2 * deltaBump);
    double vegaBump = 0.01;
    plusPrice = minusPrice = 0.0;
    std::cout << "\nCalculating vega+";
    simulateCustom(asset, volatility + vegaBump, plusPrice);
    std::cout << "\nCalculating vega+";
    simulateCustom(asset, volatility - vegaBump, minusPrice);
    vega = (plusPrice - minusPrice) / (2 * vegaBump);
}

double MonteCarlopricer::getCallPrice() const
{
    return callPrice;
}

double MonteCarlopricer::getPutPrice() const
{
    return putPrice;
}

double MonteCarlopricer::getCallDelta()
{
    return delta;
}

double MonteCarlopricer::getPutDelta()
{
    return (delta-1.0);
}
double MonteCarlopricer::getVega()
{
    return vega;
}