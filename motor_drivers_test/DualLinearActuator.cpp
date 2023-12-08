//// DualLinearActuator.cpp
//#include "DualLinearActuator.h"
//
//DualLinearActuator::DualLinearActuator(int pin1, int potPin1, int pin2, int potPin2, unsigned long timeout, int offset)
//  : actuator1(pin1, potPin1, timeout), actuator2(pin2, potPin2, timeout), offset(offset) {
//}
//
//void DualLinearActuator::setup() {
// actuator1.setup();
// actuator2.setup();
//}
//
//void DualLinearActuator::update() {
// actuator1.update();
// actuator2.update();
//
// int pos1 = actuator1.get_position();
// int pos2 = actuator2.get_position();
//
// if (abs(pos1 - pos2) > offset) {
//  // Handle the case where the positions are not within the acceptable offset
// }
//}
