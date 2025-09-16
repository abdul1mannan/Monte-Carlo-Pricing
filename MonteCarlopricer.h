#ifndef MonteCarlopricer_H
#define MonteCarlopricer_H

#include <random>

class MonteCarlopricer
{
public:
    MonteCarlopricer(float asset, float strike, float rfRate, float vol, float years,
        long steps, long sims);

    void simulate();
    void calcGreeks();
    void simulateCustom(double customAsset, double customVol, double &finalPrice);

    double getCallPrice() const;
    double getPutPrice() const;
    double getCallDelta();
    double getPutDelta();
    double getVega();

private:
    float asset;
    float strike;
    float rfRate;
    float volatility;
    float years;
    long steps;
    long simulations;

    double callPrice = 0.0;
    double putPrice = 0.0;
    double delta = 0.0;
    double vega = 0.0;

    //mt engine for generating random numbers
    std::mt19937 gen;
    //convert random numbers into normally distributed random numbers
    std::normal_distribution<> dist;

    double getNormalSample();
};

#endif
