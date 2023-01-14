#include "config.h"
#include "command.h"
#include "byj_gripper.h"
#include <Arduino.h>

BYJ_Gripper::BYJ_Gripper(int pin0, int pin1, int pin2, int pin3, int steps){
  grip_steps = steps;
  byj_pin_0 = pin0;
  byj_pin_1 = pin1;
  byj_pin_2 = pin2;
  byj_pin_3 = pin3;
  step_cycle = 0;
  currentangle = SERVO_UNGRIP_DEGREE;
  pinMode(byj_pin_0, OUTPUT);
  pinMode(byj_pin_1, OUTPUT);
  pinMode(byj_pin_2, OUTPUT);
  pinMode(byj_pin_3, OUTPUT);
}

void BYJ_Gripper::cmdOn(Cmd (&cmd)) {
  // close
  direction = true;
  int angle = int(cmd.valueT);
  int relangle = angle - currentangle;
  currentangle = angle;
  int relsteps = trunc(relangle * BYJ_STEPS_PER_DEGREE);
  relsteps = abs(relsteps);
  for (int i = 1; i <= relsteps; i++) {
    moveSteps();
    delay(1);
  }
}

void BYJ_Gripper::cmdOff(Cmd (&cmd)) {
  direction = false;
  int angle = int(cmd.valueT);
  int relangle = angle - currentangle;
  currentangle = angle;
  int relsteps = trunc(relangle * BYJ_STEPS_PER_DEGREE);
  relsteps = abs(relsteps);
  for (int i = 1; i <= relsteps; i++) {
    moveSteps();
    delay(1);
  }
}

void BYJ_Gripper::setDirection(){
  if (direction == true) {
    step_cycle++;
  }
  if (direction == false) {
    step_cycle--;
  }
  if (step_cycle > 7) {
    step_cycle = 0;
  }
  if (step_cycle < 0) {
    step_cycle = 7;
  }
}

void BYJ_Gripper::moveSteps() {
  switch (step_cycle) {
  case 0:
    digitalWrite(byj_pin_0, LOW);
    digitalWrite(byj_pin_1, LOW);
    digitalWrite(byj_pin_2, LOW);
    digitalWrite(byj_pin_3, HIGH);
    break;
  case 1:
    digitalWrite(byj_pin_0, LOW);
    digitalWrite(byj_pin_1, LOW);
    digitalWrite(byj_pin_2, HIGH);
    digitalWrite(byj_pin_3, HIGH);
    break;
  case 2:
    digitalWrite(byj_pin_0, LOW);
    digitalWrite(byj_pin_1, LOW);
    digitalWrite(byj_pin_2, HIGH);
    digitalWrite(byj_pin_3, LOW);
    break;
  case 3:
    digitalWrite(byj_pin_0, LOW);
    digitalWrite(byj_pin_1, HIGH);
    digitalWrite(byj_pin_2, HIGH);
    digitalWrite(byj_pin_3, LOW);
    break;
  case 4:
    digitalWrite(byj_pin_0, LOW);
    digitalWrite(byj_pin_1, HIGH);
    digitalWrite(byj_pin_2, LOW);
    digitalWrite(byj_pin_3, LOW);
    break;
  case 5:
    digitalWrite(byj_pin_0, HIGH);
    digitalWrite(byj_pin_1, HIGH);
    digitalWrite(byj_pin_2, LOW);
    digitalWrite(byj_pin_3, LOW);
    break;
  case 6:
    digitalWrite(byj_pin_0, HIGH);
    digitalWrite(byj_pin_1, LOW);
    digitalWrite(byj_pin_2, LOW);
    digitalWrite(byj_pin_3, LOW);
    break;
  case 7:
    digitalWrite(byj_pin_0, HIGH);
    digitalWrite(byj_pin_1, LOW);
    digitalWrite(byj_pin_2, LOW);
    digitalWrite(byj_pin_3, HIGH);
    break;
  default:
    digitalWrite(byj_pin_0, LOW);
    digitalWrite(byj_pin_1, LOW);
    digitalWrite(byj_pin_2, LOW);
    digitalWrite(byj_pin_3, LOW);
    break;
  }
  setDirection();
}
