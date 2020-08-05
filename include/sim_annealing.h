#pragma once

#include <iostream>
#include <functional>
#include <cmath>

#include <chrono>



namespace smeta {

    double temp_default(const double T0, const int k) {
        return T0 * std::pow(0.95, k);
    }

    double temp_fast(const double T0, const int k) {
        return T0 / k;
    }

    double temp_boltzmann(const double T0, const int k) {
        return T0 / std::log(k);
    }

    double acceptance(const double delta, const double T) {
        return 1. / (1. + std::exp(delta / T));
    }

    double approx_acceptance(const double delta, const double T) {
        return std::exp(-delta / T);
    }


    template<typename State>
    void sim_annealing(State &s, std::function<double(const State&)> E,
            std::function<State(const State&, const double T)> N, const int k_max = 10, const double T0 = 1e8) {
        for (int k = 0; k < k_max; k++) {
            double T = temp_default(T0, k);
            State s_new = N(s, T);
            if (acceptance(E(s_new) - E(s), T) > drand48())
                s = s_new;
        }
    }
}
