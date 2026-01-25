#include "haws/logger.h"
#include "haws/config.hpp"

using namespace pros;

namespace logger {

std::vector<std::string> logList;
Mutex logMutex; // 互斥锁
int current = 0;
// void display() {
//     for (int i = 0; i < logList.size(); i++) {
//         pros::lcd::print(i, logList.at(i).c_str());
//     }
// }

void init() {
    // nothing to do
    // TODO: 文件存储初始化
}

// TODO: 显示有问题, arm::Task会先于init函数
void display() {
    logMutex.take(200);
    int size = logList.size();
    if (size < 6) {
        for (int i = 0; i < size; i++) {
            pros::lcd::print(i, logList.at(i).c_str());
        }
    } else {
        for (int i = 0; i < 6; i++) {
            pros::lcd::print(i, logList.at(i + current).c_str());
        }
    }
    logMutex.give();
}

void pageUp() {
    current = CONSTRAIN(current - 1, 0, current);
    pros::delay(20);
    display();
}

void pageDown() {
    current = CONSTRAIN(current + 1, current, logList.size() - 6);
    pros::delay(20);
    display();
}

void log(std::string content) {
    // if (logList.size() == 6) {
    //     logList.erase(logList.begin());
    // }
    logMutex.take(500);
    logList.push_back(content);
    pros::delay(20);
    int size = logList.size();
    logMutex.give();
    current = size - 6;
    display();
}

}
