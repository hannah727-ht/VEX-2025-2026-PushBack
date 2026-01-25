#include "haws/auto.h"

// 写下一下三句后, 自动程序函数内可不写 "chassis::", "arm::", "roller::"
// 即可以直接写 moveGyro(), setGear(), setDropColor()
// 但建议写上冒号前面的内容, 方便区分该函数控制的机构, 增加代码可读性
// using namespace chassis;
// // using namespace arm;
// using namespace roller;

void autoTemplate() {
    // // 底盘编码器重置
    // chassis::reset();
    // // 陀螺仪重置
    // gyro.tare_rotation();
    // gyro.tare_pitch();
    
    // // 前进函数, 默认满功率
    // chassis::moveGyro(450, 0);
    // // 前进函数, 以最大80功率移动
    // chassis::moveGyro(450, 0, 80);
    // // 转向函数
    // chassis::turnGyro(90);

    // // 抬起摇臂至 “可以把环存在夹子中” 档位
    // // P.S. 具体档位可以通过 Ctrl＋左键点击 "ARM_GEAR_CATCH" 查看
    // arm::setGear(ARM_GEAR_CATCH);
    // // 摇臂抬升, 功率100 (负值为下降)
    // arm::lift(100);
    // // 摇臂停止, 使用HOLD刹车
    // arm::lift(0);
    // // 摇臂停止, 使用指定的COAST刹车方式刹车
    // arm::lift(0, E_MOTOR_BRAKE_COAST);

    // // 设置自动分环的颜色为蓝色 (扔掉的颜色)
    // roller::setDropColor(SORT_COLOR_BLUE);
    // // 开始自动分环 (函数内会自动转动吸轮, 不需要重复写)
    // roller::setEnable(true);
    // // 停止自动分环
    // roller::setEnable(false);
    // // 吸轮吸入, 功率100 (负值为吐出)
    // roller::roll(100);
    // // 吸轮停止, 使用COAST刹车
    // roller::roll(0);
    // // 吸轮停止, 使用指定的HOLD刹车方式刹车
    // roller::roll(0, E_MOTOR_BRAKE_HOLD);
}