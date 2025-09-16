# Monte Carlo Option Pricer

This project is a C++ implementation of a Monte Carlo simulation-based option pricer, using Object‑Oriented Programming (OOP) principles. It calculates European call and put option prices under the Geometric Brownian model and estimates Greeks (Delta and Vega). 

## Table of Contents

* [Features](#features)
* [Geomteric Brownian Motion](#geometric-brownian-motion)
* [Project Structure](#project-structure)
* [How to run](#how-to-run)
* [Output](#output)
* [Assumptions & Limitations](#assumptions--limitations)
* [License](#license)


## Features

* Monte Carlo simulation for pricing European call and put options
* Discounting back payoff to present value under a constant risk‑free rate
* Estimation of option Greeks (Delta and Vega) via finite difference bumps
* Progress indicators during long simulations
* Clean separation of concerns using classes and encapsulation

## Geometric Brownian Motion

In this project, the evolution of the asset price $S$ over time is modeled using the discrete-time form of the Geometric Brownian Motion (GBM) equation used in simulation:

$S_{t+1} = S_t \times \exp\left(\left(r - \frac{1}{2} \sigma^2\right) \Delta t + \sigma \sqrt{\Delta t} Z \right)$

Where:

* $S_t$: Asset price at time $t$
* $r$: Risk-free interest rate
* $\sigma$: Volatility of the asset
* $\Delta t$: Time increment ($\text{years} / \text{steps}$)
* $Z$: Standard normal random variable (sampled from $N(0, 1)$)

This formula is applied iteratively to simulate asset paths in the Monte Carlo engine.

## Project Structure

```
.
├── main.cpp             # Application entry point
├── MonteCarlopricer.h   # Class interface for pricer
├── MonteCarlopricer.cpp # Implementation of Monte Carlo simulation and Greeks
└── README.md            # README file
```

## How to run

### Using g++ directly

```bash
# Compile
g++ main.cpp MonteCarlopricer.cpp -o MonteCarloPricer

# Run
./MonteCarloPricer <asset> <strike> <rfRate> <volatility> <years> <steps> <simulations>
```

### Example

```bash
./MonteCarloPricer 100 100 0.05 0.2 1 252 1000000
```

This runs a 1-year simulation (`years=1`) with daily steps (`steps=252`) and 1,000,000 sample paths.

| Argument      | Description                                   |
| ------------- | --------------------------------------------- |
| `asset`       | Initial underlying asset price (e.g., 100)    |
| `strike`      | Option strike price (e.g., 100)               |
| `rfRate`      | Risk‑free interest rate (e.g., 0.05 for 5%)   |
| `volatility`  | Annualized volatility (e.g., 0.2 for 20%)     |
| `years`       | Time to maturity in years (e.g., 1)           |
| `steps`       | Number of time steps per path (e.g., 252)     |
| `simulations` | Number of Monte Carlo paths (e.g., 1,000,000) |

## Output

![Screenshot 2025-05-11 154534](https://github.com/user-attachments/assets/5ed15467-b44a-4541-90e5-c22ba01df1ce)

## Assumptions & Limitations

* **Simplified Financial Model:** This implementation uses the Geometric  framework at a high level; detailed financial derivations are omitted.
* **Greeks via Bump-and-Revalue:** Finite differences rather than analytic formulas.
* **Performance:** For very large simulations, consider parallelization or more efficient sampling techniques.

## License

This project is released under the MIT License. Feel free to use and modify for educational purposes.

