#include "haws/roller.h"
#include "haws/config.hpp"

namespace roller {

color_sort_t sorterState = SORT_COLOR_NORMAL;

void roll(int power, motor_brake_mode_e brakeMode) {
    if (power == 0) {
        motor_roller.set_brake_mode(brakeMode);
        motor_upperSorter.set_brake_mode(brakeMode);
        motor_lowerSorter.set_brake_mode(brakeMode);
        motor_roller.brake();
        motor_upperSorter.brake();
        motor_lowerSorter.brake();
    } else {
        motor_roller.move(power * -1.27);
        motor_upperSorter.move(power * 1.27);
        motor_lowerSorter.move(power * 1.27);
    }
}

void sort() {
    if (sensor_color.get_proximity() > 50) {
        logger::log("detect object, color: " + std::to_string(sensor_color.get_hue()));
        if (sensor_color.get_hue() < 90) {
            sorterState = SORT_COLOR_DETECTED;
            motor_lowerSorter.tare_position();
        }
    }

    if (sorterState == SORT_COLOR_NORMAL) {
        motor_roller.move(127);
        motor_lowerSorter.move(127);
        motor_upperSorter.move(127);

    }

    if (sorterState == SORT_COLOR_DETECTED) {
        if (motor_lowerSorter.get_position() < 150) {
            motor_roller.move(127);
            motor_lowerSorter.move(127);
            motor_upperSorter.move(-127);

        } else {
            sorterState = SORT_COLOR_NORMAL;
        }
    }
}

void save() {
    motor_roller.move(127);
    motor_lowerSorter.move(127);
    motor_upperSorter.move(127);
}

void scoreMiddle() {
    motor_roller.move(-127);
    motor_upperSorter.move(-127);
    motor_lowerSorter.move(127);
}

void AutoMiddle() {
    motor_roller.move(-80);
    motor_upperSorter.move(-60);
    motor_lowerSorter.move(60);
}

void scoreHigh() {
    motor_roller.move(-127);
    motor_upperSorter.move(127);
    motor_lowerSorter.move(127);
}
}