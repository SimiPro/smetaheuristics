#pragma once

#include <functional>

namespace smeta {
    template<typename State>
    void randopt(State &s, std::function<double(const State&)> E, std::function<State(const State&, const double T)> N, const int max_steps = 100, bool verbose = false) {

        if (verbose) {
            std::cout << "Minimizing f with random optimization " << std::endl;
        }

        double curr_best = E(s);
        for (int i = 0; i < max_steps; i++) {
            State new_state = N(s, 0);
            double new_val = E(new_state);
            if (new_val < curr_best) {
                curr_best = new_val;
                s = new_state;

                if (verbose) {
                    std::cout << "iter: " << i << "/" << max_steps << " | new_best: " << curr_best << std::endl;
                }
            }
        }
    }
}

