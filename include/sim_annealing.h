#pragma once

#include <iostream>
#include <functional>
#include <cmath>

#include <chrono>



namespace smeta {

    double temp_default(const double T0, const int k) {
        return T0 * std::pow(0.995, k);
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
        if (delta <= 0) return 1.0;
        return std::exp(-delta / T);
    }


    template<typename State>
    void sim_annealing(State &s, std::function<double(const State&)> E,
            std::function<State(const State&, const double T)> N, const int k_max = 10, const double T0 = 1e8, bool verbose = false) {


        if (verbose) {
            std::cout << "Minimizing f with simulated annealing " << std::endl;
        }

        State best_overall = s;
        double best_val_overall = E(s);
        double started_at = best_val_overall;

        for (int k = 0; k < k_max; k++) {
            double T = temp_default(T0, k);
            State s_new = N(s, T);
            double new_val = E(s_new);
            // check if we have a new best overall
            if (new_val < best_val_overall) {
                best_overall = s_new;
                best_val_overall = new_val;
            }

            if (approx_acceptance(new_val - E(s), T) > (double)rand()/RAND_MAX) {
                s = s_new;
                if (verbose) {
                    std::cout << "iter: " << k << "/" << k_max << " | new_best: " << new_val << " temperature: " << T <<  std::endl;
                }
            }

        }
      if (verbose) {
          std::cout << "Simulated annealing improved from: " << started_at << " to: " << best_val_overall << std::endl;
         // std::cout << "and state: " << best_overall << std::endl;
      }
      s = best_overall;
    }
}
