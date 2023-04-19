#include "normal_force_magnitude.hpp"

#include <ipc/barrier/barrier.hpp>

namespace ipc {

double compute_normal_force_magnitude(
    const Barrier& barrier,
    const double distance_squared,
    const double dhat,
    const double barrier_stiffness,
    const double dmin)
{
    double grad_b = barrier.first_derivative(
        distance_squared - dmin * dmin, 2 * dmin * dhat + dhat * dhat);
    return -barrier_stiffness * grad_b * 2 * sqrt(distance_squared);
}

VectorMax12d compute_normal_force_magnitude_gradient(
    const Barrier& barrier,
    const double distance_squared,
    const Eigen::VectorXd& distance_squared_gradient,
    const double dhat,
    const double barrier_stiffness,
    const double dmin)
{
    double arg_d = distance_squared - dmin * dmin;
    double arg_dhat = 2 * dmin * dhat + dhat * dhat;
    double distance = sqrt(distance_squared);
    assert(distance > 0);

    // ∇ₓ -κ * b'(d²(x)) * 2 * d(x)
    //  = -κ * ∇ₓb'(d²(x)) * 2 * d(x) - κ * b'(d²(x)) * 2 * ∇ₓd(x)
    //  = -κ * (b"(d²(x)) * 2 * d(x) + b'(d²(x)) / d(x)) * ∇ₓd(x)
    return -barrier_stiffness
        * (barrier.second_derivative(arg_d, arg_dhat) * 2 * distance
           + barrier.first_derivative(arg_d, arg_dhat) / distance)
        * distance_squared_gradient;
}

} // namespace ipc
