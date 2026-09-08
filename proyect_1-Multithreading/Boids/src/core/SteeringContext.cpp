#include "core/SteeringContext.hpp"
#include "core/FlockingRules.hpp"

SteeringContext::SteeringContext(int boidIndex, const Flock& flock, const FlockingConfig& config)
    : boidIndex_(boidIndex),
      flock_(&flock),
      config_(&config),
      candidateCursor_(0),
      neighborCount_(0),
      finished_(flock.getBoidCount() <= 1) {
    skipSelfIndex();
}

void SteeringContext::skipSelfIndex() {
    if (candidateCursor_ == boidIndex_) {
        ++candidateCursor_;
    }
    if (candidateCursor_ >= flock_->getBoidCount()) {
        finished_ = true;
    }
}

bool SteeringContext::stepOnce() {
    if (finished_) {
        return false;
    }

    const Boid& self = flock_->getBoid(boidIndex_);
    const Boid& candidate = flock_->getBoid(candidateCursor_);
    const Vector2D offset = self.getPosition() - candidate.getPosition();
    const double distance = offset.magnitude();

    if (distance > 0.0 && distance < config_->getPerceptionRadius()) {
        velocitySum_ += candidate.getVelocity();
        positionSum_ += candidate.getPosition();
        ++neighborCount_;

        if (distance < config_->getSeparationRadius()) {
            separationSum_ += offset * (1.0 / (distance * distance));
        }
    }

    ++candidateCursor_;
    skipSelfIndex();

    if (candidateCursor_ >= flock_->getBoidCount()) {
        finished_ = true;
        return false;
    }
    return true;
}

bool SteeringContext::isFinished() const {
    return finished_;
}

Vector2D SteeringContext::computeFinalSteering() const {
    const Boid& self = flock_->getBoid(boidIndex_);
    return FlockingRules::combineForces(self.getPosition(), self.getVelocity(), separationSum_,
                                         velocitySum_, positionSum_, neighborCount_, *config_);
}

int SteeringContext::getBoidIndex() const {
    return boidIndex_;
}
