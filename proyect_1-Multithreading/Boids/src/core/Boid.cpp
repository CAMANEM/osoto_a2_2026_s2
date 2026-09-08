#include "core/Boid.hpp"

#include <cmath>

namespace {

/**
 * @brief Envuelve un valor dentro del rango [0, limit), simulando un mundo
 *        toroidal (lo que sale por un borde reaparece por el opuesto).
 */
double wrapCoordinate(double value, double limit) {
    double wrapped = std::fmod(value, limit);
    if (wrapped < 0.0) {
        wrapped += limit;
    }
    return wrapped;
}

} // namespace

Boid::Boid(const Vector2D& position, const Vector2D& velocity)
    : position_(position), velocity_(velocity) {
}

const Vector2D& Boid::getPosition() const {
    return position_;
}

const Vector2D& Boid::getVelocity() const {
    return velocity_;
}

void Boid::integrate(const Vector2D& steeringForce, const FlockingConfig& config) {
    velocity_ = (velocity_ + steeringForce).limited(config.getMaxSpeed());
    position_ = position_ + velocity_ * config.getDeltaTime();
    position_ = Vector2D(wrapCoordinate(position_.getX(), config.getWorldWidth()),
                          wrapCoordinate(position_.getY(), config.getWorldHeight()));
}
