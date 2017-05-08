
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


// robot direction functions

void backwards() {
  motor_standby(false);
  motor_speed2(motor_A,100);
  motor_speed2(motor_B,100);
  delay(1000);
  motor_standby(true);
}

void forward() {
  motor_standby(false);
  motor_speed2(motor_A,-100);
  motor_speed2(motor_B,-100);
  delay(1000);
  motor_standby(true);
}

void right() {
  motor_standby(false);
  motor_speed2(motor_A,-100);
  motor_speed2(motor_B,100);
  delay(100);
  motor_standby(true);
}

void left() {
  motor_standby(false);
  motor_speed2(motor_A,100);
  motor_speed2(motor_B,-100);
  delay(100);
  motor_standby(true);
}

// motor functions
void motor_speed2(boolean motor, char speed) { //speed from -100 to 100
  byte PWMvalue=0;
  PWMvalue = map(abs(speed),0,100,50,255); //anything below 50 is very weak
  if (speed > 0)
    motor_speed(motor,0,PWMvalue);
  else if (speed < 0)
    motor_speed(motor,1,PWMvalue);
  else {
    motor_coast(motor);
  }
}
void motor_speed(boolean motor, boolean direction, byte speed) { //speed from 0 to 255
  if (motor == motor_A) {
    if (direction == 0) {
      digitalWrite(out_A_IN1,HIGH);
      digitalWrite(out_A_IN2,LOW);
    } else {
      digitalWrite(out_A_IN1,LOW);
      digitalWrite(out_A_IN2,HIGH);
    }
    analogWrite(out_A_PWM,speed);
  } else {
    if (direction == 0) {
      digitalWrite(out_B_IN1,HIGH);
      digitalWrite(out_B_IN2,LOW);
    } else {
      digitalWrite(out_B_IN1,LOW);
      digitalWrite(out_B_IN2,HIGH);
    }
    analogWrite(out_B_PWM,speed);
  }
}
void motor_standby(boolean state) { //low power mode
  if (state == true)
    digitalWrite(out_STBY,LOW);
  else
    digitalWrite(out_STBY,HIGH);
}

void motor_brake(boolean motor) {
  if (motor == motor_A) {
    digitalWrite(out_A_IN1,HIGH);
    digitalWrite(out_A_IN2,HIGH);
  } else {
    digitalWrite(out_B_IN1,HIGH);
    digitalWrite(out_B_IN2,HIGH);
  }
}

void motor_coast(boolean motor) {
  if (motor == motor_A) {
    digitalWrite(out_A_IN1,LOW);
    digitalWrite(out_A_IN2,LOW);
    digitalWrite(out_A_PWM,HIGH);
  } else {
    digitalWrite(out_B_IN1,LOW);
    digitalWrite(out_B_IN2,LOW);
    digitalWrite(out_B_PWM,HIGH);
  }
}
