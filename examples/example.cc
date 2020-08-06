#include <iostream>

#include <sim_annealing.h>
#include <Eigen/Core>

constexpr double PI = 3.14;

// schwefel function
double E(const Eigen::VectorXd &x) {
    double sum = 0;
    for (int i = 0; i < x.rows(); i++)
        sum += 500*x[i]*std::sin(std::sqrt(std::fabs(500 * x[i])));
    return 418.9829 * x.rows() - sum;
}

// complicated step function depending on T
Eigen::VectorXd N(const Eigen::VectorXd &x, const double T) {
    Eigen::VectorXd x_new(x.rows());
    for (int i = 0; i < x.rows(); i++) {
        x_new[i] = std::fmod(x[i] + T*std::tan( * ((double)rand()/RAND_MAX - 0.5)), 1.);
    }
    return x_new;
}



int main() {

    Eigen::VectorXd x(5);
    x.setRandom();
    x *= 500; // range of [-500, 500]

    smeta::sim_annealing<Eigen::VectorXd>(x, E, N, 100000);

    std::cout << "Schwefel solution  (should be around 420)" << std::endl;
    std::cout << x << std::endl;
}