
void resetServos() {
  //set all servos
  for (int i = 0; i < 6; i++) {
      // Drive each servo one at a time
    Serial.print(i); Serial.print(" - "); Serial.println(servoReset[i]);
    pwm.setPWM(i, 0, servoReset[i]);
  }
}

// set arm servo
void setArmServo(int n, int pulse) {
  pwm.setPWM(n, 0, pulse);
}
