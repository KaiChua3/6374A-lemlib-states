#pragma once

#include "pros/adi.hpp"

class Wings {
    private:
        pros::ADIDigitalOut wings1;
        pros::ADIDigitalOut wings2;
        pros::ADIDigitalOut hang;
        pros::ADIDigitalOut hang2;

    public:
        Wings(uint8_t const wingsPort1, uint8_t const wingsPort2, uint8_t const hangPort, uint8_t const hangPort2);
        void activateWings(bool wingsActive);
        void activateHang(bool hangActive);
};