#include "main.h"
#include "haws/config.hpp"
#include "haws/chassis.h"
#include "haws/roller.h"
#include "haws/auto.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    // 底盘初始化
    chassis::reset();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    chassis::move(0, 0);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
int autoSelection = 1;
const char *autoTitles[] = {
    "技能",
    "红六球",
    "红2",
    "红3",
    "红4",
    "蓝1",
    "蓝2",
    "蓝3",
    "蓝4"};
void autonomous() {logger::log("auto selection = " + std::to_string(autoSelection));
    switch (autoSelection) {
    case 0:
        skill();
        break;
    case 1:
        redLeft1();
        break;
    case 2:
        redLeft2();
        break;
    case 3:
        redRight1();
        break;
    case 4:
        redRight2();
        break;
    case 5:
        blueLeft1();
        break;
    case 6:
        blueLeft2();
        break;
    case 7:
        blueRight1();
        break;
    case 8:
        blueRight2();
        break;
    }
}
// 是否进入选自动程序
bool isSelectAuto = true;
// select auto
void autoSelector() {
    master.print(2, 0, "[ ]%s", autoTitles[autoSelection]);
    while (isSelectAuto) {
    //     // TODO: 显示陀螺仪传感器的值
    //     // master.print(2, 20, "gyro:%.3f", gyro.get_rotation());
        if (master.get_digital_new_press(DIGITAL_LEFT)) {
            autoSelection = CONSTRAIN(autoSelection - 1, 0, 8);
            master.clear_line(2);
            pros::delay(50);
            master.print(2, 0, "[ ]%s", autoTitles[autoSelection]);
        }
        if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            autoSelection = CONSTRAIN(autoSelection + 1, 0, 8);
            master.clear_line(2);
            pros::delay(50);
            master.print(2, 0, "[ ]%s", autoTitles[autoSelection]);
        }
        if (master.get_digital_new_press(DIGITAL_B)) {
            master.print(2, 1, "x");
            pros::delay(800);
            master.clear_line(2);
            break;
        }
        pros::delay(50);
    }
    pros::delay(50);
    isSelectAuto = false;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

    int trackSiwtchState = 0;
    int carryLiftState = 0;
    int GangState= 0;
    int loaderArm= 0;
    int L1=0;
    int l=0;
    int sw=0;
    autoSelector();
    logger::log("display test");
    while (true) {
        int ch1 = master.get_analog(ANALOG_RIGHT_X);
        int ch2 = master.get_analog(ANALOG_RIGHT_Y);
        int ch3 = master.get_analog(ANALOG_LEFT_Y);
        int ch4 = master.get_analog(ANALOG_LEFT_X);
        bool l1 = master.get_digital(DIGITAL_L1);
        bool l2 = master.get_digital(DIGITAL_L2);
        bool r1 = master.get_digital_new_press(DIGITAL_R1);
        bool r2 = master.get_digital(DIGITAL_R2);
        bool btnA = master.get_digital(DIGITAL_A);
        bool btnB = master.get_digital(DIGITAL_B);
        bool btnX = master.get_digital_new_press(DIGITAL_X);
        bool btnY = master.get_digital(DIGITAL_Y);
        bool btnU = master.get_digital_new_press(DIGITAL_UP);
        bool btnD = master.get_digital_new_press(DIGITAL_DOWN);
        bool btnL = master.get_digital_new_press(DIGITAL_LEFT);
        bool btnR = master.get_digital(DIGITAL_RIGHT);


        // Arcade control scheme
        chassis::move(ch3 + ch1, ch3 - ch1);
        
        if (l1) {
            roller::save();
        } else if (l2) {
            roller::roll(-100);
        } else if (btnA) {
            roller::scoreMiddle();
        } else if(btnB){
            roller::scoreHigh();
        }
        /*else if (btnX) {
            if (!trackSiwtchState) {
                trackSiwtchState = 1 - trackSiwtchState;
                digit_trackSwitch.set_value(trackSiwtchState);
            }
        } */else if (btnY) {
            roller::sort();
        } else {
            roller::roll(0);
        }

        if (btnX) {
            sw-=1;
            sw=abs(sw);
        }
        if (sw) {
            digit_trackSwitch.set_value(1);
        }else{
            digit_trackSwitch.set_value(0);
    
        }
        if (r1) {
            carryLiftState = 1 - carryLiftState;
            digit_carryLift.set_value(carryLiftState);
        }

        if(btnL){
            l-=1;
            l=abs(l);
        }
        if (l) {
            digit_Gang.set_value(1);
        } else {
            digit_Gang.set_value(0);
        }
        /*if(l1){
            L1-=1;
            L1=abs(L1);
        }
        if (L1) {
            digit_loaderArm.set_value(1);
        }else{
            digit_loaderArm.set_value(0);
        }*/
       if (btnD) {
            loaderArm = 1 - loaderArm;
            digit_loaderArm.set_value(loaderArm);
        }
        

        pros::delay(20);
    }
}