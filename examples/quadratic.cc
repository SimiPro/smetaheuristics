#include <iostream>

#include <sim_annealing.h>
#include <Eigen/Core>
#include <random_opt.h>

typedef Eigen::Vector2d State;

// rsenbrock = (a - x)^2 + b(y - x^2)^2
double E(const State &x) {
    return 100*std::pow((x[1] - x[0]*x[0]), 2) - (1 - x[0]);
}

// rosenbrock 4d
//

// complicated step function depending on T
State N(const State &x, const double T) {
    State new_x = x;
    for (int i = 0; i < x.rows(); i++) {
        new_x[i] += drand48();
    }
    return new_x;
}


int num_in_range(const int min, const int max) {
    return min + (rand() % static_cast<int>(max - min));
}

// complicated step function depending on T
State N_rand(const State &x, const double T) {
    State new_x = x;
    new_x[num_in_range(0, x.rows())] += drand48();

    return new_x;
}



int main() {

    State x;
    x[0] = -1;
    x[1]= 1;

    State x_sim = x;
    smeta::sim_annealing<State>(x_sim, E, N, 100000);

    State x_rand = x;
    smeta::randopt<State>(x_rand, E, N, 10000000);

    std::cout << "Rosenbruck function looking for value 1.36*10^-10" << std::endl;
    std::cout << "Init: " << E(x) << std::endl;
    std::cout << x << std::endl;

    std::cout << "Simulated Annealing: " << E(x_sim) << std::endl;
    std::cout << x_sim << std::endl;

    std::cout << "Random Opt: " << E(x_rand) <<  std::endl;
    std::cout << x_rand << std::endl;




}