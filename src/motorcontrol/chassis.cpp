#include "haws/chassis.h"
#include "haws/config.hpp"

namespace chassis
{

void reset() {
    motor_left1.tare_position();
    motor_left2.tare_position();
    motor_left3.tare_position();
    motor_right1.tare_position();
    motor_right2.tare_position();
    motor_right3.tare_position();
}

void move(int lPower, int rPower, float ratio) {
    motor_left1.move(lPower * 1.27 * ratio);
    motor_left2.move(lPower * 1.27 * ratio);
    motor_left3.move(lPower * 1.27 * ratio);
    motor_right1.move(rPower * 1.27 * ratio);
    motor_right2.move(rPower * 1.27 * ratio);
    motor_right3.move(rPower * 1.27 * ratio);
}

void brake(motor_brake_mode_e brakeMode) {
    motor_left1.set_brake_mode(brakeMode);
    motor_left2.set_brake_mode(brakeMode);
    motor_left3.set_brake_mode(brakeMode);
    motor_right1.set_brake_mode(brakeMode);
    motor_right2.set_brake_mode(brakeMode);
    motor_right3.set_brake_mode(brakeMode);
    motor_left1.brake();
    motor_left2.brake();
    motor_left3.brake();
    motor_right1.brake();
    motor_right2.brake();
    motor_right3.brake();
}

void moveTime(int lPower, int rPower, int time) {
    move(lPower, rPower);
    pros::delay(time);
    move(0, 0);
}

void moveEnc(int distance, int maxPower, motor_brake_mode_e brakeMode, std::function<void()> func, int funcStart) {
    float err = 0.0, lastErr = 0.0, totalErr = 0.0, deltaErr = 0.0; // 用于计算直行pid
    float power = 0.0; // 输出功率

    float kp = 0.7, ki = 0.004, kd = 3.8; // 直行pid值
    if (distance > 1000) { kp = 0.6; kd = 4.2; }

    err = distance - motor_right1.get_position();
    int timer = 0; // 用于超时退出循环，未使用计时器计时，timer每次循环+15
    int timeout = fabs(err) < 500 ? 1200 : fabs(err) * 3; // 超时时间
    timeout = timeout / maxPower * 100;
    
    chassis::reset();
    while (true) {
        // 分段函数执行
        if (funcStart != 0 &&
            ((funcStart > 0 && motor_right1.get_position() > funcStart) || 
            (funcStart < 0 && motor_right1.get_position() < funcStart))) {
            Task execFunc(func);
        }
        // 计算直行pid
        err = distance - motor_right1.get_position();
        totalErr += err;
        deltaErr = err - lastErr;
        lastErr = err;
        power = kp * err + ki * totalErr + kd * deltaErr;
        // 退出条件
        if (fabs(err) < 10 || timer > timeout) {
            break;
        }
        // TODO: 确认是否需要在超限时再累计一个power_gyro
        chassis::move(CONSTRAIN(power, -maxPower, maxPower),
                      CONSTRAIN(power, -maxPower, maxPower));
        // 分段积分
        if (fabs(err) > abs(distance) * 0.2 || fabs(err) < 1) {
            totalErr = 0;
        }
        // 延时
        pros::delay(15);
        timer += 15;
    }
    chassis::move(0, 0);
    chassis::brake(brakeMode);
    logger::log("moveEnc: tar=" + std::to_string(distance) + ",dis=" + std::to_string(motor_right1.get_position()));
}

void turnGyro (int target) {
    float err = 0.0, lastErr = 0.0, totalErr = 0.0, deltaErr = 0.0; // 用于计算pid
    float power = 0.0; // 输出功率
    // pid值
    err = target - sensor_gyro.get_rotation();
    float kp = fabs(err) > 30 && fabs(err) < 120
               ? 3.9
               : (fabs(err) < 30 ? 5.85 : 3.15);
    float ki = 35;
    float kd = fabs(err) > 30 && fabs(err) < 120
               ? 33.5
               : (fabs(err) < 30 ? 55 : 31.2);
    // 计时器
    int timer = 0;
    int timeout = fabs(err) < 20 ? 700 : fabs(err) * 20;
    
    chassis::reset();
    while (true) {
        err = target - sensor_gyro.get_rotation();
        deltaErr = err - lastErr;
        lastErr = err;
        // 控制积分值在1以下，且分段积分
        if (fabs(totalErr) < 1 && fabs(err) < 60) {
            totalErr += err / fabs(err) * 0.01;
        }
        // 判据为转向超过目标值，需要反转的情况
        if (err * lastErr <= 0) {
            totalErr = 0;
        }
        power = kp * err + kd * deltaErr + ki * totalErr;
        // 退出条件
        if ((fabs(err) < 3 && motor_right1.get_actual_velocity() < 5) ||
            (fabs(err) < 1 && fabs(deltaErr) <= 0.1) ||
            timer > timeout) {
            break;
        }
        // 控制转向
        chassis::move(CONSTRAIN(power, -100, 100),
                      CONSTRAIN(-power, -100, 100));
        // 延时
        pros::delay(10);
        timer += 10;
    }
    chassis::move(0, 0);
    chassis::brake();
    logger::log("turnGyro: tar=" + std::to_string(target) + ",cur=" + std::to_string(sensor_gyro.get_rotation()));
}

}