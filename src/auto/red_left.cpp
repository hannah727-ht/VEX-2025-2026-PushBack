#include "haws/auto.h"
using namespace chassis;
void redLeft1() {
  sensor_gyro.tare_rotation();
  sensor_gyro.tare_pitch();
  
  roller::save();
  turnGyro(-28);
  moveEnc(580,60);
  pros::delay(100);
  moveEnc(120,30);
  pros::delay(100);
  turnGyro(-32);
  pros::delay(100);
  moveEnc(290,40);
  /*
  moveEnc(155,90);
  turnGyro(61);
  roller::roll(0);
  pros::delay(100);
  digit_carryLift.set_value(1);
  moveEnc(392,30);
//对准中塔
  roller::AutoMiddle();
  pros::delay(800);//700
  roller::roll(0);
  //打中塔
  moveEnc(-1200,70);
  pros::delay(100);
  turnGyro(106);
  pros::delay(100);
  moveEnc(-435);
  pros::delay(100);
  turnGyro(196);
  //对准填装
  digit_loaderArm.set_value(1);
  roller::save();
  moveEnc(120,50);
  pros::delay(100);
  moveTime(50,50,710);
  pros::delay(500);
  digit_loaderArm.set_value(0);
  moveEnc(-300);
  pros::delay(100);
  turnGyro(106);
  pros::delay(100);
  moveEnc(-60,50);
  pros::delay(100);
  turnGyro(12);

  //填装取球*/

}

void redLeft2() {
  
}