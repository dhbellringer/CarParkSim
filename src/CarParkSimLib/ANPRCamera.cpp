#include "ANPRCamera.h"

ANPRCamera::ANPRCamera(double reliability) : dist_(reliability) {}

ANPRReading ANPRCamera::readRegistrationMark(const Car& car) {
    if (dist_(rng_)) {
        const std::string& registrationMark = car.registrationMark();
        return ANPRReading(ANPRResult::Success, registrationMark);
    }
    else {
        return ANPRReading(ANPRResult::Failure, "");
    }
}